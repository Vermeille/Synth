#pragma once

struct SFloat
{
    typedef float data_type;
    constexpr static float min = -1.f;
    constexpr static float max = 1.f;
    constexpr static float zero = 0.f;
    constexpr static double amp = (SFloat::max - SFloat::min - 1);
};

struct SInt16
{
    typedef short data_type;
    constexpr static short min = -32768;
    constexpr static short max = 32767;
    constexpr static short zero = 0;
    constexpr static double amp = (SInt16::max - SInt16::min - 1);
};

struct SInt8
{
    typedef char data_type;
    constexpr static char min = -127;
    constexpr static char max = 128;
    constexpr static char zero = 0;
    constexpr static double amp = (SInt8::max - SInt8::min - 1);
};

