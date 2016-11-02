#pragma once

#include "mono_source.hh"

class FirstOrderFilter : public MonoSource
{
    public:
        FirstOrderFilter(MonoSource* src);

        virtual float Gen() override;

        void MkLowPass(float f);
        void MkHighPass(float f);

    private:
        MonoSource* src_;
        double a_;
        double b_;
        double prev_;
};

