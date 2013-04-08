/**
** @file main.cc
*/

#include <iostream>
#include <vector>

#include "triangle.hh"
#include "square.hh"
#include "sinus.hh"
#include "saw.hh"

#include "../canvas/canvas.hh"

int main(int argc, char const *argv[])
{
    Saw<SInt16, 44100> osc;
    Sinus<SFloat, 44100> lfo;
    Square<> sq;
    lfo.freq(3);

    std::vector<float> vs;

    while (true)
    {
        for (int i = 0; i < 100; ++i)
        {
            short s = osc.Gen();
            std::cout.write(reinterpret_cast<char*>(&s), 2);
        }
        std::cout.flush();
    }
    return (0);
}


