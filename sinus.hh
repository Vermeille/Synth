#include "params.hh"
#include "osc.hh"

class Sinus : public Oscillo
{
    public:
        virtual float Gen() override;
};

float Sinus::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    return sin(this->phase_);
}
