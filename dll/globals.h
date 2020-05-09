#pragma once

// the official JKA SDK headers
#include "SDK\codemp\game\q_shared.h"
#include "SDK\codemp\game\bg_public.h"
#include "SDK\codemp\cgame\cg_public.h"
#include "SDK\codemp\cgame\cg_local.h"
#include "SDK\codemp\cgame\tr_types.h"

#include "geo.h"

//---------------------------
// Base addresses and offsets
//---------------------------

// jamp.exe base address
extern char* JAMP_BASE;

// offset for the camera angles
// only used for spinbot, aimbot works with `SendInput()`
extern unsigned int ANGLE_X_OFFSET;
extern unsigned int ANGLE_Z_OFFSET;
extern unsigned int CROSSHAIR_ENT_OFFSET;

//------------------------
// Engine structs, data and typedefs
//------------------------
// same thing as `DLLENTRY` but for the main method of the q3 VM
typedef int (*VMMain)(int, int, int, int, int, int, int, int, int, int, int, int, int);
extern VMMain originalVMMain;

// type of `pointer to dllEntry` to dynamically hook it
// the parameters and result values can be found in the original
// function prototype of the engine code
typedef int (*DLLENTRY)(int(QDECL*)(int, ...));
extern DLLENTRY originalDLLEntry;

// engine struct (e.g. to add custom shaders)
// will be populated in `CG_Init`
extern cgs_t* client_gameState;

// additional internal engine game state structs
// which will be populated by hooking q3 VM system calls
extern cg_t* client_game;
extern gameState_t* gameState;

// complete information about the current player
extern playerState_t* ps;

// -----
// Cvars to control the hack via the in-game console
// -----
// 
extern vmCvar_t WALLHACK;
extern vmCvar_t CHEATS;
extern vmCvar_t TRIGGERBOT;
extern vmCvar_t GLOW;
extern vmCvar_t ANTIGRIP;
extern vmCvar_t NOD;
extern vmCvar_t SPIN;
extern vmCvar_t ANTITRICK;
extern vmCvar_t AIM;

// -------------------------
// DLL internal structs and data
// -------------------------

extern v3_t SCREEN;
// maps client numbers to team numbers
//extern std::map<int, int> mClientTeams;

// the local player entity
extern centity_t* pPlayerEnt;

extern centity_t* pCurPushTarget;
extern centity_t* pCurAimTarget;
extern std::string curAimTargetName;

// to keep track of all entities in the VM
// this gets filled by hooking the `CG_GETDEFAULTSTATE` syscall in `dllMain`
extern centity_t* pEntities[MAX_GENTITIES];
// the currently processed entity in `cg_entities`
extern int idxCurEnt;

// -------------------------
// Windows specific types
// -------------------------
// define a type of `pointer to GetProcAddress` to dynamically hook it
typedef FARPROC(WINAPI* pGetProcAddress)(HMODULE, LPCSTR);

// --------
// Settings and states
// --------

const int AIM_KEY = VK_LCONTROL;