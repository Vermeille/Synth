/**
** @file main.cc
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <unistd.h>
#include <vector>

#include "wavetable.hh"

#include "biquad_filter.hh"
#include "butterworth.hh"
#include "envelop.hh"
#include "first_order_filter.hh"
#include "fm.hh"
#include "interpreter.hh"
#include "resonant_filter.hh"
#include "stereo_merge.hh"
#include "wav_export.hh"

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

    Interpreter interp;
    for (auto& cmd : res->first)
    {
        boost::apply_visitor(interp, cmd);
    }

    return 0;
}
