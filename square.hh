#pragma once

#include "params.hh"
#include "osc.hh"

class Square : public Oscillo
{
    public:
        virtual float Gen() override;
};

