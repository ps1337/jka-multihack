#pragma once

#include <Windows.h>
#include "globals.h"
#include "toolbox.h"
#include "gamehelper.h"

// ----
// Defs
// ----
// The real GetProcAddress
pGetProcAddress originalGetProcAddress = (pGetProcAddress)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetProcAddress");

// Type used to hook Q3 VM system calls
int(QDECL *syscall)(int arg, ...) = (int(QDECL *)(int, ...)) - 1;

// -------------------
// -------------------

// this is a proxy call to the real system calls processing method of the Q3 engine
// to dynamically modify/hook all syscalls
int syscall_hook(int cmd, ...)
{
    // this is a variadic function, so this gets all parameters
    // using va_arg
    int arg[14];
    va_list arglist;
    int count;
    va_start(arglist, cmd);
    for (count = 0; count < 14; count++)
    {
        arg[count] = va_arg(arglist, int);
    }
    va_end(arglist);

    // check which syscall has been requested
    switch (cmd)
    {

    // syscall to add an entity to a rendered scene
    // --> this also adds players to the scene
    // --> check if the entity is a player and display it
    // over walls
    case CG_R_ADDREFENTITYTOSCENE:
    {
        if (WALLHACK.value)
        {
            // get the passed parameter (an entity)
            refEntity_t *ref = (refEntity_t *)arg[0];

            // add the RF_DEPTHHACK flag to display the entity
            // over walls, effectively disabling depth for players
            // --> wallhack
            ref->renderfx |= RF_DEPTHHACK | RDF_NOFOG;

            if (playerGlowRequired())
            {
                // add a glowing shader for a better view
                ref->customShader = client_gameState->media.disruptorShader;
            }
        }
        break;
    }

    // syscall to update the position of an entity
    // this gets called before `CG_R_ADDREFENTITYTOSCENE`, so this allows us
    // to determine the currently processed entity using the passed index in this function
    case CG_S_UPDATEENTITYPOSITION:
    {
        idxCurEnt = (int)arg[0];
        break;
    }

    // Gets information on an entity using an engine struct
    case CG_GETDEFAULTSTATE:
    {
        centity_t *cur = (centity_t *)arg[1];
        pEntities[arg[0]] = cur;

        // if it's our local player entity, save the pointer
        if (ps && cur->currentState.clientNum == ps->clientNum)
        {
            pPlayerEnt = cur;
        }
        break;
    }

    // the VM processed the current game state
    // --> steal the parameters
    case CG_GETGAMESTATE:
    {
        gameState = (gameState_t *)arg[0];
        // the gameState_t* element is wrapped by a cgs_t struct, so
        // using pointer arithmetic it's possible to get the "parent" element
        // --> the cgs_t struct
        cgs_t *_tmp = 0;
        client_gameState = (cgs_t *)((int)gameState - (int)&_tmp->gameState);
        break;
    }

    // get own playerstate
    case CG_GETSNAPSHOT:
    {
        // call the real syscall first so the struct will be prepared for the following calls
        auto result = syscall(cmd, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9], arg[10], arg[11], arg[12], arg[13]);
        snapshot_t *snap = (snapshot_t *)arg[1];
        // get the current player state
        ps = &(snap->ps);

        cg_t *tmp = 0;
        // we have an `activeSnapshots` object, so let's subtract its offset in `cg_t` and get the parent element
        client_game = (cg_t *)((int)arg[1] - (int)&tmp->activeSnapshots);

        if (ANTITRICK.value)
        {
            snap->ps.fd.forcePowersActive |= (1 << FP_SEE);
        }

        // know all force powers
        snap->ps.fd.forcePowersKnown |= (1 << NUM_FORCE_POWERS);

        return result;
        break;
    }

    default:
        break;
    }
    // call the original syscall using the passed parameters
    return syscall(cmd, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9], arg[10], arg[11], arg[12], arg[13]);
}

// to allow enabling and disabling things using the in-game console
void makeCvars()
{
    syscall_hook(CG_CVAR_REGISTER, &WALLHACK, "hax_wallhack", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &GLOW, "hax_glow", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &CHEATS, "hax_cheats", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &TRIGGERBOT, "hax_trigger", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &ANTIGRIP, "hax_antigrip", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &ANTITRICK, "hax_antitrick", "1", 0);
    syscall_hook(CG_CVAR_REGISTER, &AIM, "hax_aim", "1", 0);
}

// read current cvar values and act accordingly
void updateCvars()
{
    syscall_hook(CG_CVAR_UPDATE, &WALLHACK);
    syscall_hook(CG_CVAR_UPDATE, &GLOW);
    syscall_hook(CG_CVAR_UPDATE, &CHEATS);
    syscall_hook(CG_CVAR_UPDATE, &TRIGGERBOT);
    syscall_hook(CG_CVAR_UPDATE, &ANTIGRIP);
    syscall_hook(CG_CVAR_UPDATE, &ANTITRICK);
    syscall_hook(CG_CVAR_UPDATE, &AIM);
}

void log(std::string text)
{
    syscall_hook(CG_PRINT, ("\n\n\n\n" + text).c_str());
}

// this will be called instead of the original `dllEntry`
// the result type and parameters result from the original
// engine code
void hookDLLEntry(int(QDECL *syscallptr)(int arg, ...))
{
    syscall = syscallptr;
    originalDLLEntry(syscall_hook);
}

// Hook for the q3 VM main method
int hookVMMain(int cmd, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l)
{
    switch (cmd)
    {

    // initializing the game vm (game startup)
    case CG_INIT:
    {
        // register our cvars
        makeCvars();

        // delete data from previous game VMs
        pPlayerEnt = nullptr;
        pCurPushTarget = nullptr;
        idxCurEnt = 0;

        // call the real method
        int result = originalVMMain(cmd, a, b, c, d, e, f, g, h, i, j, k, l);

        // Initialize custom shaders which will be used to make enemy players glow
        client_gameState->media.electricBody2Shader = trap_R_RegisterShader("gfx/misc/fullbodyelectric2");
        client_gameState->media.enlightenmentShader = trap_R_RegisterShader("powerups/enlightenmentshell");
        client_gameState->media.disruptorShader = trap_R_RegisterShader("gfx/effects/burn");
        return result;
    }

    // this gets called each time a frame will be drawn
    case CG_DRAW_ACTIVE_FRAME:
    {
        int result = originalVMMain(cmd, a, b, c, d, e, f, g, h, i, j, k, l);

        // read the (maybe) updated cvar values
        updateCvars();

        // enable cheat protected cvars
        if (CHEATS.value)
        {
            // unlock blocked and cheat protected cvars
            // by overriding the server provided cvar
            // prevent overwriting it by setting it each frame
            syscall_hook(CG_CVAR_SET, "sv_cheats", "1");
        }

        if (TRIGGERBOT.value && client_game)
        {
            // only trigger with a shootable weapon
            if (ps->weapon > WP_SABER && ps->weapon != WP_THERMAL && ps->weapon != WP_TRIP_MINE && ps->weapon != WP_DET_PACK)
            {
                int crosshairClientNum = client_game->crosshairClientNum;
                if (crosshairClientNum >= 0 && crosshairClientNum <= MAX_CLIENTS)
                {
                    // only shoot at enemies
                    if (isEnemy(crosshairClientNum))
                    {
                        // attack
                        syscall_hook(CG_SENDCONSOLECOMMAND, "+attack; -attack;");
                    }
                }
            }
        }

        if (ANTIGRIP.value && client_game)
        {
            // If we are currently being gripped
            if (ps && (ps->fd.forceGripBeingGripped || ps->fd.forceGripCripple))
            {
                setEntToLastAttacker(pCurPushTarget);
                focusEnt(pCurPushTarget);
                syscall_hook(CG_SENDCONSOLECOMMAND, "force_throw;");
                syscall_hook(CG_SENDCONSOLECOMMAND, "force_throw;");
                syscall_hook(CG_SENDCONSOLECOMMAND, "force_throw;");
                syscall_hook(CG_SENDCONSOLECOMMAND, "force_throw;");
            }
        }

        if (AIM.value && client_game)
        {
            if (GetAsyncKeyState(AIM_KEY))
            {
                // no target, get it first
                if (!pCurAimTarget)
                {
                    int crosshairClientNum = client_game->crosshairClientNum;
                    auto ent = entFromClientNum(crosshairClientNum);
                    if (ent)
                    {
                        pCurAimTarget = ent;

                        // tell the local player who we are aiming on
                        if (client_gameState)
                        {
                            auto tmpTarget = client_gameState->clientinfo[crosshairClientNum];
                            curAimTargetName = tmpTarget.name;
                            std::string txt = " Aiming @ " + curAimTargetName;
                            log(txt);
                        }
                    }
                }
                if (pCurAimTarget)
                {
                    if (!focusEnt(pCurAimTarget))
                    {
                        // enemy dead or not valid
                        pCurAimTarget = nullptr;
                    }
                }
            }
            // reset the target
            else
            {
                pCurAimTarget = nullptr;
            }
        }

        // reset or it's not possible to distinguish between nothing and client 0
        if (client_game)
        {
            client_game->crosshairClientNum = -1;
        }

        return result;
    }

    default:
        break;
    }
    return originalVMMain(cmd, a, b, c, d, e, f, g, h, i, j, k, l);
}

// this gets called instead of `GetProcAddress`
FARPROC WINAPI hookGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    CHAR moduleName[MAX_PATH];

    // check in which dll the call will be executed
    if (!GetModuleFileName(hModule, moduleName, sizeof(moduleName)))
    {
        return (FARPROC)originalGetProcAddress(hModule, lpProcName);
    }

    // are we in the game vm?
    if (isSubstr(moduleName, "cgamex86.dll"))
    {
        if (isSubstr(lpProcName, "dllEntry"))
        {
            // Modify returned function here
            // --> execute modified function instead
            // (modified function calls original function after doing hax using `originalDLLEntry`)
            originalDLLEntry = (DLLENTRY)originalGetProcAddress(hModule, lpProcName);
            return (PROC)hookDLLEntry;
        }

        // Save things as above
        if (isSubstr(lpProcName, "vmMain"))
        {
            originalVMMain = (VMMain)originalGetProcAddress(hModule, lpProcName);
            return (PROC)hookVMMain;
        }
    }
    return (FARPROC)originalGetProcAddress(hModule, lpProcName);
}

// register a custom shader in the game VM
qhandle_t trap_R_RegisterShader(const char *name)
{
    return syscall_hook(CG_R_REGISTERSHADER, name);
}

// draw text on the screen
void trap_R_Font_DrawString(int ox, int oy, const char *text, const float *rgba, const int setIndex, int iCharLimit, const float scale)
{
    syscall_hook(CG_R_FONT_DRAWSTRING, ox, oy, text, rgba, setIndex, iCharLimit, scale);
}