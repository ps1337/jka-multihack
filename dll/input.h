#pragma once

#include <Windows.h>

#include "globals.h"
#include "toolbox.h"

// For the aimbot
void moveMouse(v3_t point)
{
    if (!client_game)
    {
        return;
    }

    // only if game is not minimized
    if (!isJKAForeground())
    {
        return;
    }

    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE;
    Input.mi.dx = point.x - client_game->refdef.width / 2;
    Input.mi.dy = point.y - client_game->refdef.height / 2;

    SendInput(1, &Input, sizeof(INPUT));
}

void moveMouseStatic(v3_t point)
{
    // only if game is not minimized
    if (!isJKAForeground())
    {
        return;
    }

    INPUT Input = {0};
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE;

    Input.mi.dx = point.x;
    Input.mi.dy = point.y;

    SendInput(1, &Input, sizeof(INPUT));
}

void setCameraAngles(float x, float y)
{
    memcpy((JAMP_BASE + ANGLE_X_OFFSET), &x, sizeof(x));
    memcpy((JAMP_BASE + ANGLE_Z_OFFSET), &y, sizeof(y));
}

void setCameraXAngle(float x)
{
    memcpy((JAMP_BASE + ANGLE_X_OFFSET), &x, sizeof(x));
}

void setCameraYAngle(float y)
{
    memcpy((JAMP_BASE + ANGLE_Z_OFFSET), &y, sizeof(y));
}