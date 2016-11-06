/**
** @file main.cc
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "saw.hh"
#include "sinus.hh"
#include "square.hh"
#include "triangle.hh"
#include "wavetable.hh"

#include "biquad_filter.hh"
#include "butterworth.hh"
#include "envelop.hh"
#include "first_order_filter.hh"
#include "fm.hh"
#include "mono_to_stereo.hh"
#include "resonant_filter.hh"
#include "stereo_merge.hh"
#include "wav_export.hh"

#include "parsec.h"

enum class OscilloSelect
{
    Sinus,
    Square,
    Saw
};

auto GenerateParser()
{
    auto tok = [](auto p) { return ignore_whitespaces() >> p; };
    auto sin = parse_word("sinus", OscilloSelect::Sinus);
    auto squ = parse_word("square", OscilloSelect::Square);
    auto saw = parse_word("saw", OscilloSelect::Saw);
    auto mono_sound =
        tok((sin | squ | saw) & tok(parse_uint()) & tok(parse_uint()));

    return list_of(mono_sound << tok(!parse_char('\n')));
}

void PlayTuple(const std::tuple<OscilloSelect, int, int>& t)
{
    std::unique_ptr<Oscillo> osc;
    switch (std::get<0>(t))
    {
    case OscilloSelect::Sinus:
        osc.reset(new Sinus);
        break;
    case OscilloSelect::Square:
        osc.reset(new Square);
        break;
    case OscilloSelect::Saw:
        osc.reset(new Saw);
        break;
    }
    osc->freq(std::get<1>(t));
    MonoToStereo sm(osc.get());
    for (int j = 0; j < (std::get<2>(t) * 441) / 1000; ++j)
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

std::string ReadAllFile(const std::string& filename)
{
    if (filename == "-" || filename.empty())
    {
        std::cerr << "Enter all of your commands then ^D\n";
        std::stringstream buffer;
        buffer << std::cin.rdbuf();
        return buffer.str();
    }
    else
    {
        std::ifstream t(filename.c_str());
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
}

int main(int argc, char const* argv[])
{
    std::string input = ReadAllFile(argc >= 2 ? argv[1] : "");
    auto res = GenerateParser()(input.begin(), input.end());
    if (!res)
    {
        std::cerr << "parse error\n";
        return 1;
    }

    for (auto& sound : res->first)
    {
        PlayTuple(sound);
    }

    return 0;
}
