#pragma once

#include "Vector2.h"

struct Line {
    Vector2 p0;
    Vector2 p1;
    float brightness = 1.f;

    bool processed = false;
};
