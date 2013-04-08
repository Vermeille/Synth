#include "params.hh"
#include "osc.hh"

template <class Param = SInt16, int SampleRate = 44100>
class Sinus : public Oscillo<Param, SampleRate>
{
    public:
        typedef typename Param::data_type data_type;
        virtual data_type Gen() override;
};

template <class Param, int SR>
typename Param::data_type Sinus<Param, SR>::Gen()
{
    if (this->phase_ >= M_TAU)
        this->phase_ -= M_TAU;

    this->phase_ += this->phase_incr_;

    return ((Param::max - Param::min) / 2) * sin(this->phase_) + Param::zero;
}
