#pragma once

#include "params.hh"
#include "osc.hh"

class Triangle : public Oscillo
{
    public:
        virtual float Gen() override;
};

