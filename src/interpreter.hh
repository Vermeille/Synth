#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "freqs.hh"
#include "merger.hh"
#include "parser.hh"

#include "adsr.hh"
#include "saw.hh"
#include "sinus.hh"
#include "square.hh"
#include "triangle.hh"

#include "mono_to_stereo.hh"

class Interpreter
{
  private:
    enum class Type
    {
        Osc,
        Env,
        Merger,
    };

    std::map<std::string, Type> vars_;
    std::map<std::string, std::unique_ptr<Oscillo>> oscs_;
    std::map<std::string, ADSR> envs_;
    std::map<std::string, Merger> mergers_;

    MonoSource* GetSource(const std::string& var)
    {
        auto found = vars_.find(var);
        if (found == vars_.end())
            throw std::runtime_error(var + " not found");

        switch (found->second)
        {
        case Type::Osc:
            return oscs_.find(var)->second.get();
        case Type::Env:
            return &envs_.find(var)->second;
        case Type::Merger:
            return &mergers_.find(var)->second;
        }
        assert(false);
    }

  public:
    typedef void result_type;

    void operator()(const DeclareOsc& osc)
    {
        auto inserted = vars_.insert(std::make_pair(osc.name, Type::Osc));
        if (!inserted.second)
            throw std::runtime_error(osc.name + " already exists");

        switch (osc.select)
        {
        case OscilloSelect::Sinus:
            oscs_[osc.name].reset(new Sinus);
            break;
        case OscilloSelect::Square:
            oscs_[osc.name].reset(new Square);
            break;
        case OscilloSelect::Saw:
            oscs_[osc.name].reset(new Saw);
            break;
        case OscilloSelect::Triangle:
            oscs_[osc.name].reset(new Triangle);
            break;
        }
    }

    void operator()(const SetNote& f)
    {
        auto osc = oscs_.find(f.osc_name);
        if (osc == oscs_.end())
            throw std::runtime_error("Can't find Oscillo " + f.osc_name);

        osc->second->freq(GetFreq(f.note));
    }

    void operator()(const Play& p)
    {
        Merger merge;
        for (auto& name : p.names)
            merge.AddSource(GetSource(name));

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

    void operator()(const EnvDecl& e)
    {
        envs_.emplace(std::make_pair(e.name, ADSR(GetSource(e.source))));
        vars_.insert(std::make_pair(e.name, Type::Env));
    }

    void operator()(const EnvReset& e)
    {
        auto env = envs_.find(e.name);
        if (env == envs_.end())
            throw std::runtime_error("Can't find Envelop " + e.name);

        env->second.reset();
    }

    void operator()(const EnvConfig& e)
    {
        auto env = envs_.find(e.name);
        if (env == envs_.end())
            throw std::runtime_error("Can't find Envelop " + e.name);

        env->second.adsr(e.phase, e.start_time, e.volume);
    }

    void operator()(const MergeDecl& m)
    {
        auto ptr = mergers_.emplace(std::make_pair(m.name, Merger()));

        for (auto& in : m.inputs)
            ptr.first->second.AddSource(GetSource(in));

        vars_.insert(std::make_pair(m.name, Type::Merger));
    }
};
