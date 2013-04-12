#pragma once

#include <utility>

#include "envelop.hh"

class ADSR : public Envelop
{
    public:
        ADSR(MonoSource* src);

        void adsr(int index, float time, float val);
        float* adsr(int index);

        virtual float Gen() override;

        void src(MonoSource* src);
        MonoSource* src();

    private:
        float adsr_[5][2];
        int index_;
};

