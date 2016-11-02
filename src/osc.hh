#pragma once

#include <cmath>

#include "params.hh"
#include "mono_source.hh"

class Oscillo : public MonoSource
{
    public:
        Oscillo();

        virtual float Gen() = 0;
        void freq(float f);
        float freq();

    protected:
        float freq_;
        float phase_;
        float phase_incr_;
};

