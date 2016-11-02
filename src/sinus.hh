#include "osc.hh"
#include "params.hh"

class Sinus : public Oscillo
{
  public:
    virtual float Gen() override;
};
