#pragma once

#include <cmath>

namespace geo {

    struct C2Vector {
        union {
            struct {
                float x;
                float y;
            };
            float raw[2];
        };

        constexpr C2Vector(float x, float y) : x(x), y(y) { }

        float length() const {
            return std::sqrt(lengthSquared());
        }

        float lengthSquared() const {
            return x * x + y * y;
        }

        inline float& operator [] (size_t idx) {
            return raw[idx];
        }

        inline float const& operator [] (size_t idx) const {
            return raw[idx];
        }
    };

    static_assert(sizeof(C2Vector) == sizeof(float[2]), "");

    struct C3Vector {
        union {
            struct {
                float x;
                float y;
                float z;
            };
            float raw[3];
        };

        constexpr C3Vector() : C3Vector(0.0f, 0.0f, 0.0f) {}
        constexpr C3Vector(float x, float y, float z) : x(x), y(y), z(z) { }
        constexpr C3Vector(C2Vector const& v, float z) : x(v.x), y(v.y), z(z) { }

        inline operator C2Vector() const {
            return C2Vector { x, y };
        }

        float length() const {
            return std::sqrt(lengthSquared());
        }

        float lengthSquared() const {
            return x * x + y * y + z * z;
        }

        inline float& operator [] (size_t idx) {
            return raw[idx];
        }

        inline float const& operator [] (size_t idx) const {
            return raw[idx];
        }

        C3Vector normalize() const {
            float l = length();
            return C3Vector{ x / l, y / l, z / l };
        }
    };

    static_assert(sizeof(C3Vector) == sizeof(float[3]), "");

    struct C4Vector {
        union {
            struct {
                float x;
                float y;
                float z;
                float w;
            };
            float raw[4];
        };

        constexpr C4Vector() : C4Vector(0.0f, 0.0f, 0.0f, 0.0f) { }
        constexpr C4Vector(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
        constexpr C4Vector(C3Vector const& v, float w) : x(v.x), y(v.y), z(v.z), w(w) { }

        inline operator C3Vector() const {
            return C3Vector { x, y, z };
        }

        float length() const {
            return std::sqrt(lengthSquared());
        }

        float lengthSquared() const {
            return x * x + y * y + z * z + w * w;
        }

        inline float& operator [] (size_t idx) {
            return raw[idx];
        }

        inline float const& operator [] (size_t idx) const {
            return raw[idx];
        }
    };

    static_assert(sizeof(C4Vector) == sizeof(float[4]), "");
}
