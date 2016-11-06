#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "freqs.hh"
#include "merger.hh"
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
    void operator()(const SetNote& f)
    {
        auto osc = vars_.find(f.osc_name);
        if (osc == vars_.end())
        {
            throw std::runtime_error("Can't find Oscillo " + f.osc_name);
        }
        osc->second->freq(GetFreq(f.note));
    }

    void operator()(const Play& p) const
    {
        Merger merge;
        for (auto& name : p.names)
        {
            auto osc = vars_.find(name);
            if (osc == vars_.end())
            {
                throw std::runtime_error("play: can't find an osc named " +
                                         name);
            }
            merge.AddSource(osc->second.get());
        }

        MonoToStereo sm(&merge);
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
};
