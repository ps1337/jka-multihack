#include <iostream>
#include <tchar.h>
#include <unistd.h>
#include <windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <ostream>
#include <string>

// allows to easily switch between retail and openjk version of the game
int openjk = 1;

// path to the dll to be injected
char dllPath[] = "C:\\Users\\...";

BOOL FileExists(LPCTSTR path)
{
    DWORD dwAttrib = GetFileAttributes(path);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
            !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL checkAlreadyInjected(DWORD PID, std::string moduleName)
{
    // get a snapshot of all processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);

    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Invalid handle value" << std::endl;
        exit(99);
    }

    MODULEENTRY32 ModEntry;
    if (Module32First(hSnapshot, &ModEntry))
    {
        do
        {
            // check if the dll is already present
            if (!strcmp((char *)ModEntry.szModule, moduleName.c_str()))
            {
                CloseHandle(hSnapshot);
                return TRUE;
            }
        } while (Module32Next(hSnapshot, &ModEntry));
    }

    CloseHandle(hSnapshot);
    return FALSE;
}

int main(int argc, char *argv[])
{

    std::string EXE_DIR;
    std::string EXE_NAME;
    if (openjk == 1)
    {
        // openjk version
        EXE_DIR = "C:\\Users\\....";
        EXE_NAME = "openjk.x86.exe";
    }

    else
    {
        // Retail
        EXE_DIR = "C:\\Program Files (x86)\\...";
        EXE_NAME = "jamp.exe";
    }

    std::string EXE_PATH = EXE_DIR + "\\" + EXE_NAME;

    // Launch Process
    // additional information
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    if (!CreateProcess(EXE_PATH.c_str(), // the path
                       argv[1],          // Command line
                       NULL,             // Process handle not inheritable
                       NULL,             // Thread handle not inheritable
                       FALSE,            // Set handle inheritance to FALSE
                       0,                // No creation flags
                       NULL,             // Use parent's environment block
                       EXE_DIR.c_str(),  // Use parent's starting directory
                       &si,              // Pointer to STARTUPINFO structure
                       &pi               // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
                       ))
    {
        std::cerr << "Can't create process" << std::endl;
        exit(88);
    }

    sleep(1);

    // Close process and thread handles
    // this does not stop the game
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    PROCESSENTRY32 entry;
    DWORD PID = -1;
    BOOL found = FALSE;

    // Do Windows things
    entry.dwSize = sizeof(PROCESSENTRY32);
    // Get all processes
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Can't get list of running processes" << std::endl;
        exit(1);
    }

    // Search for the process using the exe file name
    if (Process32First(snapshot, &entry))
    {
        do
        {
            // check if a process with the executable file name is present
            if (strcmp((char *)entry.szExeFile, EXE_NAME.c_str()) == 0)
            {
                found = TRUE;
                PID = entry.th32ProcessID;
                std::cout << "Got process: " << PID << " " << entry.szExeFile << std::endl;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }
    else
    {
        std::cerr << "Can't process list of running processes" << std::endl;
        exit(2);
    }

    if (!found)
    {
        std::cerr << "Can't find process" << std::endl;
        exit(3);
    }

    if (!FileExists((LPCTSTR)dllPath))
    {
        std::cerr << "DLL not found" << std::endl;
        exit(4);
    }

    if (checkAlreadyInjected(PID, dllPath))
    {
        std::cerr << "Already injected" << std::endl;
        exit(5);
    }

    //Get a handle to the process
    HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (!procHandle)
    {
        std::cerr << "Can't open process" << std::endl;
        exit(6);
    }

    // Get the address of LoadLibraryA in kernel32.dll, used to
    // pass it to the remote process in order to load our dll
    LPVOID loadFunctionAddress = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if (!loadFunctionAddress)
    {
        std::cerr << "LoadLibraryA not found" << std::endl;
        exit(7);
    }

    // Allocate space in the target process for our DLL path
    LPVOID allocatedMem = LPVOID(VirtualAllocEx(procHandle, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (!allocatedMem)
    {
        std::cerr << "Can't allocate memory in the target process" << std::endl;
        exit(8);
    }

    // Write the path of our DLL in the allocated memory
    if (!WriteProcessMemory(procHandle, allocatedMem, dllPath, MAX_PATH, nullptr))
    {
        std::cerr << "Can't write memory into the target process" << std::endl;
        exit(9);
    }

    // Load the DLL by causing the remote process to spawn a thread which calls LoadLibraryA
    // which loads the DLL using the path we allocated previously.
    HANDLE threadHandle = CreateRemoteThread(procHandle, nullptr, NULL, LPTHREAD_START_ROUTINE(loadFunctionAddress), allocatedMem, NULL, nullptr);
    if (!threadHandle)
    {
        std::cerr << "Can't start the remote thread" << std::endl;
        exit(10);
    }

    // work is done
    CloseHandle(procHandle);
    //free memory
    VirtualFreeEx(procHandle, LPVOID(allocatedMem), 0, MEM_RELEASE);

    std::cout << "Injected!" << std::endl;
    return 0;
}