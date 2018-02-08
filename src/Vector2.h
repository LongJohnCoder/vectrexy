#pragma once

#include <cmath>

struct Vector2 {
    float x = 0.f;
    float y = 0.f;

    void operator+=(const Vector2& rhs) {
        x += rhs.x;
        y += rhs.y;
    }
};

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Vector2 operator*(const Vector2& lhs, float scalar) {
    return {lhs.x * scalar, lhs.y * scalar};
}

inline Vector2 operator/(const Vector2& lhs, float scalar) {
    return {lhs.x / scalar, lhs.y / scalar};
}

inline float Magnitude(const Vector2& v) {
    return ::sqrt(v.x * v.x + v.y * v.y);
}

inline Vector2 Normalize(const Vector2& v) {
    return v / Magnitude(v);
}

inline bool AlmostEqual(const Vector2& v1, const Vector2& v2, float epsilon = 1e-8) {
    return ::abs(v1.x - v2.x) <= epsilon && ::abs(v1.y - v2.y) <= epsilon;
}
