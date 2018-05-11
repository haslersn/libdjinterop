/*
    This file is part of libengineprime.

    libengineprime is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libengineprime is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libengineprime.  If not, see <http://www.gnu.org/licenses/>.
 */

#if __cplusplus <= 199711L
  #error This library needs at least a C++11 compliant compiler
#endif

#ifndef ENGINEPRIME_ENCODE_DECODE_UTILS_HPP
#define ENGINEPRIME_ENCODE_DECODE_UTILS_HPP

#include <cstdint>

namespace engineprime {

// Extract an int8_t from a raw value at ptr address
inline int8_t decode_int8(const char *ptr)
{
    return static_cast<const unsigned char>(*ptr);
}

// Encode an int8_t as a raw byte to an output pointer
inline void encode_int8(int8_t value, char *ptr)
{
    *ptr = static_cast<char>(value);
}

// Decode an int32_t from a little-endian encoded raw value at ptr address
inline int32_t decode_int32_le(const char *ptr)
{
    int32_t val = 0;
    for (int i = 0; i < 4; ++i)
    {
        val <<= 8;
        val |= static_cast<const unsigned char>(*(ptr + 3 - i));
    }
    return val;
}

// Encode an int32_t as 4 raw bytes to an output pointer with little-endianness
inline void encode_int32_le(int32_t value, char *ptr)
{
    for (int i = 0; i < 4; ++i)
    {
        *ptr = static_cast<char>(value & 0xFF);
        value >>= 8;
        ++ptr;
    }
}

// Decode an int32_t from a big-endian encoded raw value at ptr address
inline int32_t decode_int32_be(const char *ptr)
{
    int32_t val = 0;
    for (int i = 0; i < 4; ++i)
    {
        val <<= 8;
        val |= static_cast<const unsigned char>(*ptr++);
    }
    return val;
}

// Encode an int32_t as 4 raw bytes to an output pointer with big-endianness
inline void encode_int32_be(int32_t value, char *ptr)
{
    ptr += 3;
    for (int i = 0; i < 4; ++i)
    {
        *ptr = static_cast<char>(value & 0xFF);
        value >>= 8;
        --ptr;
    }
}

// Decode an int64_t from a little-endian encoded raw value at ptr address
inline int64_t decode_int64_le(const char *ptr)
{
    int64_t val = 0;
    for (int i = 0; i < 8; ++i)
    {
        val <<= 8;
        val |= static_cast<const unsigned char>(*(ptr + 7 - i));
    }
    return val;
}

// Encode an int64_t as 8 raw bytes to an output pointer with little-endianness
inline void encode_int64_le(int64_t value, char *ptr)
{
    for (int i = 0; i < 8; ++i)
    {
        *ptr = static_cast<char>(value & 0xFF);
        value >>= 8;
        ++ptr;
    }
}

// Decode an int64_t from a big-endian encoded raw value at ptr address
inline int64_t decode_int64_be(const char *ptr)
{
    int64_t val = 0;
    for (int i = 0; i < 8; ++i)
    {
        val <<= 8;
        val |= static_cast<const unsigned char>(*ptr++);
    }
    return val;
}

// Encode an int64_t as 8 raw bytes to an output pointer with big-endianness
inline void encode_int64_be(int64_t value, char *ptr)
{
    ptr += 7;
    for (int i = 0; i < 8; ++i)
    {
        *ptr = static_cast<char>(value & 0xFF);
        value >>= 8;
        --ptr;
    }
}

// Decode a double from a little-endian encoded raw value at ptr address
inline double decode_double_le(const char *ptr)
{
    auto val = decode_int64_le(ptr);
    return *reinterpret_cast<double *>(&val);
}

// Encode a double as 8 raw bytes to an output pointer with little-endianness
inline void encode_double_le(double value, char *ptr)
{
    encode_int64_le(*reinterpret_cast<int64_t *>(&value), ptr);
}

// Decode a double from a big-endian encoded raw value at ptr address
inline double decode_double_be(const char *ptr)
{
    auto val = decode_int64_be(ptr);
    return *reinterpret_cast<double *>(&val);
}

// Encode a double as 8 raw bytes to an output pointer with big-endianness
inline void encode_double_be(double value, char *ptr)
{
    encode_int64_be(*reinterpret_cast<int64_t *>(&value), ptr);
}

} // namespace engineprime

#endif // ENGINEPRIME_ENCODE_DECODE_UTILS_HPP
