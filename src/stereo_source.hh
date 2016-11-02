#pragma once

struct StereoSource
{
    virtual std::pair<float, float> Gen() = 0;
};
