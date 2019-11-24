#pragma once

#include <cmath>

#define ARITHMETIC(OP, C)                                         \
    C##<T>& operator OP##= (C<T> const& o){                       \
        for (size_t i = 0; i < sizeof(raw) / sizeof(raw[0]); ++i) \
            raw[i] OP##= o[i];                                    \
        return *this;                                             \
    }

namespace geo {
    namespace {
        constexpr const static size_t _x = 0;
        constexpr const static size_t _y = 1;
        constexpr const static size_t _z = 2;

        constexpr const static size_t _w = 3;
        constexpr const static size_t _o = 3;

        template <typename Out, typename In, size_t... Idx>
        Out swizzle(In const& v) {
            return Out{ v[Idx]... };
        }
    }

    template <typename T>
    struct C2Vector {
        union {
            struct {
                T x;
                T y;
            };
            T raw[2];
        };

        constexpr C2Vector(T x, T y) : x(x), y(y) { }

        T length() const {
            return std::sqrt(lengthSquared());
        }

        T lengthSquared() const {
            return x * x + y * y;
        }

        inline T& operator [] (size_t idx) {
            return raw[idx];
        }

        inline T const& operator [] (size_t idx) const {
            return raw[idx];
        }

        ARITHMETIC(+, C2Vector);
        ARITHMETIC(-, C2Vector);
        ARITHMETIC(*, C2Vector);
        ARITHMETIC(/, C2Vector);

        C2Vector<T> norm() const {
            T l = length();
            return { x / l, y / l };
        }

        C2Vector<T> yx() const {
            return swizzle<C2Vector<T>, C2Vector<T>, _y, _x>(*this);
        }
    };

    static_assert(sizeof(C2Vector<float>) == sizeof(float[2]), "");

    template <typename T> 
    struct C3Vector {
        union {
            struct {
                T x;
                T y;
                T z;
            };
            struct {
                T a;
                T b;
                T c;
            };
            T raw[3];
        };

        constexpr C3Vector() : C3Vector(0.0f, 0.0f, 0.0f) {}
        constexpr C3Vector(T x, T y, T z) : x(x), y(y), z(z) { }
        constexpr C3Vector(C2Vector<T> const& v, T z) : x(v.x), y(v.y), z(z) { }

        inline operator C2Vector<T>() const {
            return C2Vector<T> { x, y };
        }

        T length() const {
            return std::sqrt(lengthSquared());
        }

        T lengthSquared() const {
            return x * x + y * y + z * z;
        }

        inline T& operator [] (size_t idx) {
            return raw[idx];
        }

        inline T const& operator [] (size_t idx) const {
            return raw[idx];
        }

        ARITHMETIC(+, C3Vector);
        ARITHMETIC(-, C3Vector);
        ARITHMETIC(*, C3Vector);
        ARITHMETIC(/, C3Vector);

        /// Performs cross product.
        C3Vector<T> cross(C3Vector<T> const& o) const {
            T x_ = y * o.z - o.y * z;
            T y_ = z * o.x - o.z * x;
            T z_ = x * o.y - o.x * y;
            return C4Vector<T> {x_, y_, z_};
        }

        /// Returns a normalized instance of the current vector.
        C3Vector<T> norm() const {
            T l = length();
            return C3Vector<T>{ x / l, y / l, z / l };
        }

#define MAKE_SWIZZLE(_1, _2, _3)                                                  \
        C3Vector<T> _1##_2##_3() const {                                          \
            return swizzle<C3Vector<T>, C3Vector<T>, _##_1, _##_2, _##_3>(*this); \
        }

        MAKE_SWIZZLE(x, y, z);
        MAKE_SWIZZLE(x, z, y);
        MAKE_SWIZZLE(y, x, z);
        MAKE_SWIZZLE(y, z, x);
        MAKE_SWIZZLE(z, x, y);
        MAKE_SWIZZLE(z, y, x);
#undef MAKE_SWIZZLE


#define MAKE_SWIZZLE(_1, _2)                                               \
        C2Vector<T> _1##_2() const {                                       \
            return swizzle<C2Vector<T>, C3Vector<T>, _##_1, _##_2>(*this); \
        }

        MAKE_SWIZZLE(x, y);
        MAKE_SWIZZLE(x, z);
        MAKE_SWIZZLE(y, x);
        MAKE_SWIZZLE(y, z);
        MAKE_SWIZZLE(z, x);
        MAKE_SWIZZLE(z, y);
#undef MAKE_SWIZZLE

    };

    static_assert(sizeof(C3Vector<float>) == sizeof(float[3]), "");

    template <typename T>
    struct C4Vector {
        union {
            struct {
                T x;
                T y;
                T z;
                union {
                    T w;
                    T o;
                };
            };
            T raw[4];
        };

        constexpr C4Vector() : C4Vector(T{}, T{}, T{}, T{}) { }
        constexpr C4Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
        constexpr C4Vector(C3Vector<T> const& v, T w) : x(v.x), y(v.y), z(v.z), w(w) { }

        inline operator C3Vector<T>() const {
            return C3Vector<T> { x, y, z };
        }

        T length() const {
            return std::sqrt(lengthSquared());
        }

        T lengthSquared() const {
            return x * x + y * y + z * z + w * w;
        }

        inline T& operator [] (size_t idx) {
            return raw[idx];
        }

        inline T const& operator [] (size_t idx) const {
            return raw[idx];
        }

        ARITHMETIC(+, C4Vector);
        ARITHMETIC(-, C4Vector);
        ARITHMETIC(*, C4Vector);
        ARITHMETIC(/, C4Vector);

        C4Vector<T> norm() const {
            T l = length();
            return { x / l, y / l, z / l, o / l };
        }

#define MAKE_SWIZZLE(_1, _2, _3, _4)                                                     \
        C4Vector<T> _1##_2##_3##_4() const {                                             \
            return swizzle<C4Vector<T>, C4Vector<T>, _##_1, _##_2, _##_3, _##_4>(*this); \
        }

        MAKE_SWIZZLE(x, y, z, o); MAKE_SWIZZLE(x, y, z, w);
        MAKE_SWIZZLE(x, y, o, z); MAKE_SWIZZLE(x, y, w, z);
        MAKE_SWIZZLE(x, z, o, y); MAKE_SWIZZLE(x, z, w, y);
        MAKE_SWIZZLE(x, z, y, o); MAKE_SWIZZLE(x, z, y, w);
        MAKE_SWIZZLE(x, o, y, z); MAKE_SWIZZLE(x, w, y, z);
        MAKE_SWIZZLE(x, o, z, y); MAKE_SWIZZLE(x, w, z, y);

        MAKE_SWIZZLE(y, x, z, o); MAKE_SWIZZLE(y, x, z, w);
        MAKE_SWIZZLE(y, x, o, z); MAKE_SWIZZLE(y, x, w, z);
        MAKE_SWIZZLE(y, z, o, x); MAKE_SWIZZLE(y, z, w, x);
        MAKE_SWIZZLE(y, z, x, o); MAKE_SWIZZLE(y, z, x, w);
        MAKE_SWIZZLE(y, o, x, z); MAKE_SWIZZLE(y, w, x, z);
        MAKE_SWIZZLE(y, o, z, x); MAKE_SWIZZLE(y, w, z, x);

        MAKE_SWIZZLE(z, y, x, o); MAKE_SWIZZLE(z, y, x, w);
        MAKE_SWIZZLE(z, y, o, x); MAKE_SWIZZLE(z, y, w, x);
        MAKE_SWIZZLE(z, x, o, y); MAKE_SWIZZLE(z, x, w, y);
        MAKE_SWIZZLE(z, x, y, o); MAKE_SWIZZLE(z, x, y, w);
        MAKE_SWIZZLE(z, o, y, x); MAKE_SWIZZLE(z, w, y, x);
        MAKE_SWIZZLE(z, o, x, y); MAKE_SWIZZLE(z, w, x, y);

        MAKE_SWIZZLE(o, y, x, z); MAKE_SWIZZLE(w, y, x, z);
        MAKE_SWIZZLE(o, y, z, x); MAKE_SWIZZLE(w, y, z, x);
        MAKE_SWIZZLE(o, x, z, y); MAKE_SWIZZLE(w, x, z, y);
        MAKE_SWIZZLE(o, x, y, z); MAKE_SWIZZLE(w, x, y, z);
        MAKE_SWIZZLE(o, z, y, x); MAKE_SWIZZLE(w, z, y, x);
        MAKE_SWIZZLE(o, z, x, y); MAKE_SWIZZLE(w, z, x, y);

#undef MAKE_SWIZZLE

#define MAKE_SWIZZLE(_1, _2, _3)                                     \
        C3Vector<T> _1##_2##_3() const {                             \
            return swizzle<C3Vector<T>, C4Vector<T>, _##_1, _##_2, _##_3>(*this); \
        }

        MAKE_SWIZZLE(x, y, z);
        MAKE_SWIZZLE(x, z, y);
        MAKE_SWIZZLE(y, z, x);
        MAKE_SWIZZLE(y, x, z);
        MAKE_SWIZZLE(z, x, y);
        MAKE_SWIZZLE(z, y, x);

        MAKE_SWIZZLE(x, y, o); MAKE_SWIZZLE(x, y, w);
        MAKE_SWIZZLE(x, o, y); MAKE_SWIZZLE(x, w, y);
        MAKE_SWIZZLE(x, z, o); MAKE_SWIZZLE(x, z, w);
        MAKE_SWIZZLE(x, o, z); MAKE_SWIZZLE(x, w, z);

        MAKE_SWIZZLE(y, x, o); MAKE_SWIZZLE(y, x, w);
        MAKE_SWIZZLE(y, o, x); MAKE_SWIZZLE(y, w, x);
        MAKE_SWIZZLE(y, z, o); MAKE_SWIZZLE(y, z, w);
        MAKE_SWIZZLE(y, o, z); MAKE_SWIZZLE(y, w, z);

        MAKE_SWIZZLE(z, x, o); MAKE_SWIZZLE(z, x, w);
        MAKE_SWIZZLE(z, o, x); MAKE_SWIZZLE(z, w, x);
        MAKE_SWIZZLE(z, y, o); MAKE_SWIZZLE(z, y, w);
        MAKE_SWIZZLE(z, o, y); MAKE_SWIZZLE(z, w, y);

#undef MAKE_SWIZZLE

#define MAKE_SWIZZLE(_1, _2)                                               \
        C3Vector<T> _1##_2() const {                                       \
            return swizzle<C3Vector<T>, C4Vector<T>, _##_1, _##_2>(*this); \
        }

#define MAKE_SWIZZLES(R, _1, _2, _3, _4) MAKE_SWIZZLE(R, _1); MAKE_SWIZZLE(R, _2); MAKE_SWIZZLE(R, _3); MAKE_SWIZZLE(R, _4)
#define MAKE_SWIZZLES2(R, _1, _2, _3) MAKE_SWIZZLE(R, _1); MAKE_SWIZZLE(R, _2); MAKE_SWIZZLE(R, _3);
        MAKE_SWIZZLES(x, y, z, o, w);
        MAKE_SWIZZLES(y, x, z, o, w);
        MAKE_SWIZZLES(z, x, y, o, w);
        MAKE_SWIZZLES2(o, x, y, z); MAKE_SWIZZLES2(w, x, y, z);
#undef MAKE_SWIZZLES2
#undef MAKE_SWIZZLES
#undef MAKE_SWIZZLE

    };
    
    static_assert(sizeof(C4Vector<float>) == sizeof(float[4]), "");
}
