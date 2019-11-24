#pragma once

#include "vectors.hpp"

#include <cstring>

namespace geo {
    namespace {
        template <typename V>
        struct Matrix {
            constexpr const static size_t width = sizeof(V) / sizeof(float);
            constexpr const static size_t height = sizeof(V) / sizeof(float);

            Matrix() {
                for (int i = 0; i < height; ++i)
                    columns[i][i] = 1.0f;
            }

            template <typename... Ts, typename = std::enable_if_t<(... && std::is_same_v<Ts, V>)>>
            Matrix(Ts&&... cs) {
            }

            inline V& operator[] (size_t idx) {
                return columns[idx];
            }

            inline V const& operator[] (size_t idx) const {
                return columns[idx];
            }

            Matrix<V>& operator *= (Matrix<V> const& o) {
                Matrix<V> tmp = *this * o;
                memcpy(&columns, &tmp, sizeof(Matrix<V>));
                return *this;
            }

            Matrix<V>& translate(V const& v) {
                for (int i = 0; i < height; ++i)
                    columns[width - 1][i] *= v[i];
                return *this;
            }

            Matrix<V>& scale(V const& v) {
                Matrix<V> scaleMat;
                for (int i = 0; i < width; ++i)
                    scaleMat[i][i] = v[i];

                return operator*=(scaleMat);
            }

        private:
            V columns[width];
        };

        template <typename V>
        inline Matrix<V> operator * (Matrix<V> const& left, Matrix<V> const& right) {
            Matrix<V> result;
            for (int y = 0; y < left.height; ++y) {
                for (int x = 0; x < left.width; ++x) {
                    float accum = 0.0f;

                    for (int k = 0; k < left.width; ++k)
                        accum += left[k][y] * right[x][k];

                    result[y][x] = accum;
                }
            }
            return result;
        }
    }

    template <typename T>
    using C33Matrix = Matrix<C3Vector<T>>;
    
    template <typename T>
    using C44Matrix = Matrix<C4Vector<T>>;
}
