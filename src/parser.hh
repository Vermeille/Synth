#pragma once

#include <string>
#include <vector>

#include "parsec.h"

#include <boost/variant.hpp>

enum class OscilloSelect
{
    Sinus,
    Square,
    Saw,
    Triangle
};

struct DeclareOsc
{
    OscilloSelect select;
    std::string name;

    DeclareOsc() = default;

    DeclareOsc(OscilloSelect o, std::string a)
        : select(o)
        , name(a)
    {
    }
};

struct SetFreq
{
    std::string osc_name;
    int freq;

    SetFreq() = default;

    SetFreq(std::string n, int f)
        : osc_name(std::move(n))
        , freq(f)
    {
    }
};

struct Play
{
    int ms;
    std::vector<std::string> names;

    Play() = default;

    Play(int ms, std::vector<std::string> names)
        : ms(ms)
        , names(names)
    {
    }
};

auto GenerateParser()
{
    auto tok = [](auto p) {
        return skip_while(parser_pred(parse_char(), isblank)) >> p;
    };
    auto sin = parse_word("sinus", OscilloSelect::Sinus);
    auto squ = parse_word("square", OscilloSelect::Square);
    auto saw = parse_word("saw", OscilloSelect::Saw);
    auto tri = parse_word("triangle", OscilloSelect::Triangle);
    auto osc_decl = ((sin | squ | saw | tri) & tok(parse_word())) %
                    [](auto x) { return DeclareOsc(x.first, x.second); };

    auto set_freq =
        (parse_word("set_freq") >> (tok(parse_word()) & tok(parse_uint()))) %
        [](auto x) { return SetFreq(x.first, x.second); };

    auto play =
        ((parse_word("play") >> tok(parse_uint())) & tok(parse_word())) %
        [](auto&& x) {
            return Play(x.first, std::vector<std::string>({x.second}));
        };

    auto command = (osc_decl %
                    [](auto&& x) {
                        return boost::variant<DeclareOsc, SetFreq, Play>(x);
                    }) |
                   (play %
                    [](auto&& x) {
                        return boost::variant<DeclareOsc, SetFreq, Play>(x);
                    }) |
                   (set_freq % [](auto&& x) {
                       return boost::variant<DeclareOsc, SetFreq, Play>(x);
                   });

    return list_of(tok(command) << tok(!parse_char('\n')));
}
