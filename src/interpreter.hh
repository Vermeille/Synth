#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "parser.hh"

#include "saw.hh"
#include "sinus.hh"
#include "square.hh"
#include "triangle.hh"

#include "mono_to_stereo.hh"

class Interpreter
{
  private:
    std::map<std::string, std::unique_ptr<Oscillo>> vars_;

  public:
    void operator()(const DeclareOsc& osc)
    {
        switch (osc.select)
        {
        case OscilloSelect::Sinus:
            vars_[osc.name].reset(new Sinus);
            break;
        case OscilloSelect::Square:
            vars_[osc.name].reset(new Square);
            break;
        case OscilloSelect::Saw:
            vars_[osc.name].reset(new Saw);
            break;
        case OscilloSelect::Triangle:
            vars_[osc.name].reset(new Triangle);
            break;
        }
    }
    void operator()(const SetFreq& f)
    {
        auto osc = vars_.find(f.osc_name);
        if (osc == vars_.end())
        {
            throw std::runtime_error("Can't find Oscillo " + f.osc_name);
        }
        osc->second->freq(f.freq);
    }

    void operator()(const Play& p) const
    {
        if (p.names.size() != 1)
        {
            throw std::runtime_error("play supports only one source");
        }
        auto osc = vars_.find(p.names[0]);
        if (osc == vars_.end())
        {
            throw std::runtime_error("play: can't find an osc named " +
                                     p.names[0]);
        }

        MonoToStereo sm(osc->second.get());
        for (int j = 0; j < (p.ms * 441) / 1000; ++j)
        {
            for (int i = 0; i < 100; ++i)
            {
                auto res = Render<SInt16>(sm.Gen());
                std::cout.write(reinterpret_cast<char*>(&res.first), 2);
                std::cout.write(reinterpret_cast<char*>(&res.second), 2);
            }
            std::cout.flush();
        }
    }
} interp;
