#pragma once

#include <Windows.h>

// really good substring function
bool isSubstr(const char* a, const char* b) {
    const char* output = NULL;
    output = strstr(a, b);
    if (output) {
        return true;
    }
    else {
        return false;
    }
}

bool isJKAForeground() {
    char windowName[64];
    GetWindowTextA(GetFocus(), windowName, 64);
    if (!(isSubstr(windowName, "Jedi Academy"))) {
        return false;
    }
    return true;
}