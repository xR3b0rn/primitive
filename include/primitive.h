/*
MIT License

Copyright (c) 2020 xR3b0rn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>

namespace primitive
{
    namespace detail
    {
        template <class T>
        class primitive
        {
        public:
            using self_t = primitive<T>;
            using type_t = T;
            
            template <class U>
            class proxy
            {
            public:
                explicit inline constexpr proxy(bool result, const U& last) noexcept
                    : _result(result)
                    , _last(last)
                {}
                explicit inline constexpr operator bool() const noexcept { return _result; }
                inline constexpr auto operator<(const U& other) const noexcept { return proxy(_result & (_last._v < other._v), other); }
                inline constexpr auto operator>(const U& other) const noexcept { return proxy(_result & (_last._v > other._v), other); }
                inline constexpr auto operator<=(const U& other) const noexcept { return proxy(_result & (_last._v <= other._v), other); }
                inline constexpr auto operator>=(const U& other) const noexcept { return proxy(_result & (_last._v >= other._v), other); }
                inline constexpr auto operator==(const U& other) const noexcept { return proxy(_result & (_last._v == other._v), other); }
                inline constexpr auto operator!=(const U& other) const noexcept { return proxy(_result & (_last._v != other._v), other); }
                inline constexpr auto operator<(volatile const U& other) volatile const noexcept { return proxy<volatile U>(_result & (_last._v < other._v), other); }
                inline constexpr auto operator>(volatile const U& other) volatile const noexcept { return proxy<volatile U>(_result & (_last._v > other._v), other); }
                inline constexpr auto operator<=(volatile const U& other) volatile const noexcept {  return proxy<volatile U>(_result & (_last._v <= other._v), other); }
                inline constexpr auto operator>=(volatile const U& other) volatile const noexcept { return proxy<volatile U>(_result & (_last._v >= other._v), other); }
                inline constexpr auto operator==(volatile const U& other) volatile const noexcept { return proxy<volatile U>(_result & (_last._v == other._v), other); }
                inline constexpr auto operator!=(volatile const U& other) volatile const noexcept { return proxy<volatile U>(_result & (_last._v != other._v), other); }

            private:
                bool _result;
                const U& _last;
            };

        public:
            inline constexpr primitive()
            {
                static_assert(sizeof(self_t) == sizeof(T));
                static_assert(std::is_fundamental_v<T>);
            }
            explicit inline constexpr primitive(const T& n) noexcept
                : _v(n)
            {
                static_assert(sizeof(self_t) == sizeof(T));
                static_assert(std::is_fundamental_v<T>);
            }
            explicit inline constexpr operator T() noexcept { return _v; }
            explicit inline constexpr operator const T() const noexcept { return _v; }
            explicit inline constexpr operator T() volatile noexcept { return _v; }
            explicit inline constexpr operator const T() volatile const noexcept { return _v; }
            inline constexpr auto& operator=(const T& n) noexcept { _v = n; return *this; }
            inline constexpr auto operator<(const self_t& other) const noexcept { return proxy(_v < other._v, other); }
            inline constexpr auto operator>(const self_t& other) const noexcept { return proxy(_v > other._v, other); }
            inline constexpr auto operator<=(const self_t& other) const noexcept { return proxy(_v <= other._v, other); }
            inline constexpr auto operator>=(const self_t& other) const noexcept { return proxy(_v >= other._v, other); }
            inline constexpr auto operator==(const self_t& other) const noexcept { return proxy(_v == other._v, other); }
            inline constexpr auto operator!=(const self_t& other) const noexcept { return proxy(_v != other._v, other); }
            inline constexpr auto operator++() noexcept { _v++; return *this; }
            inline constexpr auto operator++(int) noexcept { auto old = *this; _v++; return old; }
            inline constexpr auto operator--() noexcept { _v--; return *this; }
            inline constexpr auto operator--(int) noexcept { auto old = *this; _v--; return old; }
            inline constexpr auto operator+(const self_t& other) const noexcept { return self_t(_v + other._v); }
            inline constexpr auto operator-(const self_t& other) const noexcept { return self_t(_v - other._v); }
            inline constexpr auto operator*(const self_t& other) const noexcept { return self_t(_v * other._v); }
            inline constexpr auto operator/(const self_t& other) const { return self_t(_v / other._v); }
            template <class U = void> inline constexpr auto operator%(const self_t other) const { return self_t(_v % other._v); }
            inline constexpr auto operator+=(const self_t& other) noexcept { _v += other.raw(); return *this; }
            inline constexpr auto operator-=(const self_t& other) noexcept { _v -= other.raw(); return *this; }
            inline constexpr auto operator*=(const self_t& other) noexcept { _v *= other.raw(); return *this; }
            inline constexpr auto operator/=(const self_t& other) { _v /= other.raw(); return *this; }
            template <class U = void> inline constexpr auto operator%=(const self_t other) const { _v %= other.raw(); return *this; }
            template <class U = void> inline constexpr auto operator^(const self_t other) const noexcept { return self_t(_v ^ other.raw()); }
            template <class U = void> inline constexpr auto operator&(const self_t other) const noexcept { return self_t(_v & other.raw()); }
            template <class U = void> inline constexpr auto operator|(const self_t other) const noexcept { return self_t(_v | other.raw()); }
            template <class U = void> inline constexpr auto operator~() const noexcept { return self_t(~_v); }
            template <class U = void> inline constexpr auto operator^=(const self_t other) const noexcept { _v ^= other.raw(); return *this; }
            template <class U = void> inline constexpr auto operator&=(const self_t other) const noexcept { _v &= other.raw(); return *this; }
            template <class U = void> inline constexpr auto operator|=(const self_t other) const noexcept { _v |= other.raw(); return *this; }
            template <class U> inline constexpr auto to() const noexcept { return static_cast<U>(_v); }
            template <class U> inline constexpr auto cast() const noexcept { return reinterpret_cast<U>(_v); }
            inline constexpr T& raw() noexcept { return _v; }
            inline constexpr const T& raw() const noexcept { return _v; }
            inline constexpr volatile T& raw() volatile noexcept { return _v; }
            inline constexpr volatile const T& raw() volatile const noexcept { return _v; }
            inline constexpr auto& operator=(volatile const T& n) noexcept { _v = n; return *this; }
            inline constexpr auto operator<(volatile const self_t& other) volatile const noexcept { return proxy(_v < other._v, other); }
            inline constexpr auto operator>(volatile const self_t& other) volatile const noexcept { return proxy(_v > other._v, other); }
            inline constexpr auto operator<=(volatile const self_t& other) volatile const noexcept { return proxy(_v <= other._v, other); }
            inline constexpr auto operator>=(volatile const self_t& other) volatile const noexcept { return proxy(_v >= other._v, other); }
            inline constexpr auto operator==(volatile const self_t& other) volatile const noexcept { return proxy(_v == other._v, other); }
            inline constexpr auto operator!=(volatile const self_t& other) volatile const noexcept { return proxy(_v != other._v, other); }
            inline constexpr auto operator++() volatile noexcept { _v++; return *this; }
            inline constexpr auto operator++(int) volatile noexcept { auto old = *this; _v++; return old; }
            inline constexpr auto operator--() volatile noexcept { _v--; return *this; }
            inline constexpr auto operator--(int) volatile noexcept { auto old = *this; _v--; return old; }
            inline constexpr auto operator+(volatile const self_t& other) volatile const noexcept { return self_t(_v + other.raw()); }
            inline constexpr auto operator-(volatile const self_t& other) volatile const noexcept { return self_t(_v - other.raw()); }
            inline constexpr auto operator*(volatile const self_t& other) volatile const noexcept { return self_t(_v * other.raw()); }
            inline constexpr auto operator/(volatile const self_t& other) volatile const { return self_t(_v / other.raw()); }
            inline constexpr auto operator+=(volatile const self_t& other) volatile noexcept { _v += other.raw(); return *this; }
            inline constexpr auto operator-=(volatile const self_t& other) volatile noexcept { _v -= other.raw(); return *this; }
            inline constexpr auto operator*=(volatile const self_t& other) volatile noexcept { _v *= other.raw(); return *this; }
            inline constexpr auto operator/=(volatile const self_t& other) volatile { _v /= other.raw(); return *this; }
            template <class U> inline constexpr auto to() volatile const noexcept { return static_cast<U>(_v); }
            template <class U> inline constexpr auto cast() volatile const noexcept { return reinterpret_cast<U>(_v); }
            std::string to_s() const noexcept { return std::to_string(_v); }
            std::wstring to_ws() const noexcept { return std::to_wstring(_v); }

        private:
            T _v;

            friend class proxy<T>;
            friend class proxy<volatile T>;
        };
    }

    using i8_t = detail::primitive<int8_t>;
    using ui8_t = detail::primitive<uint8_t>;
    using i16_t = detail::primitive<int16_t>;
    using ui16_t = detail::primitive<uint16_t>;
    using i32_t = detail::primitive<int32_t>;
    using ui32_t = detail::primitive<uint32_t>;
    using i64_t = detail::primitive<int64_t>;
    using ui64_t = detail::primitive<uint64_t>;
    using f_t = detail::primitive<float>;
    using d_t = detail::primitive<double>;
    using siz_t = detail::primitive<std::size_t>;

    namespace literals
    {
        constexpr i8_t operator "" _i8(unsigned long long int v)      { return i8_t(int8_t(v)); }
        constexpr ui8_t operator "" _ui8(unsigned long long int v)    { return ui8_t(int8_t(v)); }
        constexpr i16_t operator "" _i16(unsigned long long int v)    { return i16_t(int16_t(v)); }
        constexpr ui16_t operator "" _ui16(unsigned long long int v)  { return ui16_t(int16_t(v)); }
        constexpr i32_t operator "" _i32(unsigned long long int v)    { return i32_t(int32_t(v)); }
        constexpr ui32_t operator "" _ui32(unsigned long long int v)  { return ui32_t(int32_t(v)); }
        constexpr i64_t operator "" _i64(unsigned long long int v)    { return i64_t(int64_t(v)); }
        constexpr ui64_t operator "" _ui64(unsigned long long int v)  { return ui64_t(int64_t(v)); }
        constexpr f_t operator "" _f(long double v)                   { return f_t(float(v)); }
        constexpr d_t operator "" _d(long double v)                   { return d_t(double(v)); }
        constexpr siz_t operator "" _siz(long double v)               { return siz_t(std::size_t(v)); }
    }
}

std::ostream& operator<<(std::ostream& os, const primitive::i8_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::ui8_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::i16_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::ui16_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::i32_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::ui32_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::i64_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::ui64_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::f_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, const primitive::d_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::i8_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::ui8_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::i16_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::ui16_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::i32_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::ui32_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::i64_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::ui64_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::f_t& v) { os << v.raw(); return os; }
std::ostream& operator<<(std::ostream& os, volatile const primitive::d_t& v) { os << v.raw(); return os; }

std::istream& operator>>(std::istream& is, primitive::i8_t& v) { int8_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::ui8_t& v) { uint8_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::i16_t& v) { int16_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::ui16_t& v) { uint16_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::i32_t& v) { int32_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::ui32_t& v) { uint32_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::i64_t& v) { int64_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::ui64_t& v) { uint64_t iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::f_t& v) { float iv; is >> iv; v = iv; return is; }
std::istream& operator>>(std::istream& is, primitive::d_t& v) { double iv; is >> iv; v = iv; return is; }

namespace std
{
    template <> struct hash<primitive::i8_t> { std::size_t operator()(const primitive::i8_t& v) const noexcept { return std::hash<int8_t>()(v.raw()); } };
    template <> struct hash<primitive::ui8_t> { std::size_t operator()(const primitive::ui8_t& v) const noexcept { return std::hash<uint8_t>()(v.raw()); } };
    template <> struct hash<primitive::i16_t> { std::size_t operator()(const primitive::i16_t& v) const noexcept { return std::hash<int16_t>()(v.raw()); } };
    template <> struct hash<primitive::ui16_t> { std::size_t operator()(const primitive::ui16_t& v) const noexcept { return std::hash<uint16_t>()(v.raw()); } };
    template <> struct hash<primitive::i32_t> { std::size_t operator()(const primitive::i32_t& v) const noexcept { return std::hash<int32_t>()(v.raw()); } };
    template <> struct hash<primitive::ui32_t> { std::size_t operator()(const primitive::ui32_t& v) const noexcept { return std::hash<uint32_t>()(v.raw()); } };
    template <> struct hash<primitive::i64_t> { std::size_t operator()(const primitive::i64_t& v) const noexcept { return std::hash<int64_t>()(v.raw()); } };
    template <> struct hash<primitive::ui64_t> { std::size_t operator()(const primitive::ui64_t& v) const noexcept { return std::hash<uint64_t>()(v.raw()); } };
    template <> struct hash<primitive::f_t> { std::size_t operator()(const primitive::f_t& v) const noexcept { return std::hash<float>()(v.raw()); } };
    template <> struct hash<primitive::d_t> { std::size_t operator()(const primitive::d_t& v) const noexcept { return std::hash<double>()(v.raw()); } };
}
