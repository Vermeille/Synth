#pragma once

#include "osc.hh"
#include "mono_source.hh"

class FM : public MonoSource
{
    public:
        FM(Oscillo* osc, MonoSource* mod);
        virtual float Gen() override;

        float carrier_freq() { return freq_; }
        void carrier_freq(float f) { freq_ = f; }

        float mod_amp() { return mod_amp_; }
        void mod_amp(float a) { mod_amp_ = a; }

    private:
        Oscillo* carrier_;
        MonoSource* modulator_;;
        float freq_;
        float mod_amp_;
};
