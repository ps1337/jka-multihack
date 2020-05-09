#pragma once

#include "globals.h"
#include "geo.h"

centity_t* entFromClientNum(int clientNum) {
    // invalid client number
    if (clientNum < 0 || clientNum > MAX_CLIENTS) { return nullptr; }

    centity_t* res = nullptr;

    for (int i = 0; i < MAX_GENTITIES; i++) {
        centity_t* cur = pEntities[i];
        if (!cur) { continue; }
        if (cur->playerState->clientNum == clientNum) {
            res = cur;
            break;
        }
    }

    return res;
}

void setEntToLastAttacker(centity_t* ent) {
    int attackerClientNum = ps->persistant[PERS_ATTACKER];
    ent = entFromClientNum(attackerClientNum);
}

bool focusEnt(centity_t* ent) {
    if (!ps || !client_game || !ent) { return false; }

    if (ent->currentState.eFlags & EF_DEAD) { return false; }

    if (Q3worldToScreen(ent, client_game->refdef)) {
        moveMouse(SCREEN);
    }
    return true;
}

// In team based games, we only want to add glow to enemies
// the triggerbot should only attack in case we focus an enemy
bool isEnemy(int clientNum) {
    if (!ps || !client_gameState || clientNum < 0) {
        return false;
    }

    // Not team based - everyone is an enemy
    if (client_gameState->gametype < GT_TEAM) {
        return true;
    }

    int ownTeam = ps->persistant[PERS_TEAM];

    if (ownTeam == TEAM_SPECTATOR) {
        return false;
    }

    if (client_gameState->clientinfo[clientNum].team == ownTeam) {
        return false;
    }

    return true;
}

// An entity gets processed
// --> check if we want to add glow to it
bool playerGlowRequired() {
    // glow turned off via cvar
    if (!GLOW.value) {
        return false;
    }

    // illegal index
    if (idxCurEnt > MAX_GENTITIES) {
        return false;
    }

    auto curEnt = pEntities[idxCurEnt];
    int curEntClientNum = curEnt->currentState.clientNum;

    // illegal index too
    if (curEnt->currentState.clientNum > MAX_CLIENTS) {
        return false;
    }

    // dead player or not a player at all
    if (curEnt->currentState.eType != ET_PLAYER

        || curEnt->currentState.eFlags & EF_DEAD) {
        return false;
    }

    // it's us
    if (curEnt->currentState.clientNum == ps->clientNum) {
        return false;
    }

    // we are in a duel
    if (ps->duelInProgress) {
        // only add glow for duel opponent
        if (!curEnt->currentState.clientNum == ps->duelIndex) {
            return false;
        }
    }

    // only mark enemies
    if (!isEnemy(curEntClientNum)) {
        return false;
    }

    return true;
}