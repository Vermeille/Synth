#pragma once

#include <vector>

#include "osc.hh"

class Wavetable : public Oscillo
{
    public:
        Wavetable(const std::vector<float>& table);
        virtual float Gen() override;
    private:
        std::vector<float> table_;
};
