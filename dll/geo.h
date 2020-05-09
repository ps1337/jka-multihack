#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "globals.h"

// vector and w2s from https://guidedhacking.com/threads/openarena-esp-hack-aimbot-source-code-download.7908/

// I also include the original SDK which already defined vec3_t as float array, so just define a new type here
struct v3_t {
    float x, y, z;

    // Constructors
    v3_t() { x = y = z = 0; }
    v3_t(float a, float b, float c) : x(a), y(b), z(c) {}
    v3_t(float a, float b) : x(a), y(b), z(0) {}
    v3_t(float* v) : x(v[0]), y(v[1]), z(v[2]) {}

    // Operators
    bool operator==(const v3_t& o) const { return x == o.x && y == o.y && z == o.z; }
    bool operator!=(const v3_t& o) const { return x != o.x || y != o.y || z != o.z; }
    v3_t operator-() const { return v3_t(-x, -y, -z); }

    v3_t& mul(float f) { x *= f; y *= f; z *= f; return *this; }
    v3_t& div(float f) { x /= f; y /= f; z /= f; return *this; }
    v3_t& add(float f) { x += f; y += f; z += f; return *this; }
    v3_t& sub(float f) { x -= f; y -= f; z -= f; return *this; }
    v3_t& add(const v3_t& o) { x += o.x; y += o.y; z += o.z; return *this; }
    v3_t& sub(const v3_t& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }

    float dot(const v3_t& o) const { return x * o.x + y * o.y + z * o.z; }
    float dotxy(const v3_t& o) const { return x * o.x + y * o.y; }

    // returns `true` in case `this` is actually on the screen
    // also return the calculated screen information via `screen`, which is used for the aimbot
    bool w2s(float fovx, float fovy, float windowWidth, float windowHeight, v3_t left, v3_t up, v3_t forward, v3_t origin, v3_t& screen)
    {
        v3_t transform;
        float xc = 0, yc = 0;
        float px = 0, py = 0;
        float z = 0;

        px = tan(fovx * M_PI / 360.0);
        py = tan(fovy * M_PI / 360.0);

        transform = this->sub(origin); //this = destination

        xc = windowWidth / 2.0;
        yc = windowHeight / 2.0;

        z = transform.dot(left);
        // entity not on screen
        if (z <= 0.1) { return false; }

        // entity is on screen, calculate mouse offset
        screen.x = xc - transform.dot(up) * xc / (z * px);
        screen.y = yc - transform.dot(forward) * yc / (z * py);

        return true;
    }

};

v3_t SCREEN = { 0, 0, 0 };

// wrapper around v3_t::`w2s` for the Q3 engine
bool Q3worldToScreen(centity_t* ent, refdef_t refdef) {
    v3_t chest = ent->currentState.pos.trBase;
    // enemy head
    chest.z += 30;

    return chest.w2s(refdef.fov_x, refdef.fov_x, refdef.width, refdef.height, refdef.viewaxis[0], refdef.viewaxis[1], refdef.viewaxis[2], refdef.vieworg, SCREEN);
}