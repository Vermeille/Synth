#pragma once

#include <utility>

#define SAMPLE_RATE 44100

#define M_TAU (2 * M_PI)
#define M_TAUOVR2 M_PI

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
    constexpr static char min = -128;
    constexpr static char max = 127;
    constexpr static char zero = 0;
    constexpr static double amp = (SInt8::max - SInt8::min - 1);
};

template <class Param>
typename Param::data_type Render(float f)
{
    return Param::amp / 2 * f + Param::zero;
}

template <class Param>
std::pair<typename Param::data_type, typename Param::data_type>
Render(const std::pair<float, float>& f)
{
    return std::make_pair(Render<Param>(f.first), Render<Param>(f.second));
}
