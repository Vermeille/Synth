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

struct SetNote
{
    std::string osc_name;
    int note;

    SetNote() = default;

    SetNote(std::string n, int note)
        : osc_name(std::move(n))
        , note(note)
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

template <class P>
auto Tok(P p)
{
    return skip_while(parser_pred(parse_char(), isblank)) >> p;
}

auto OscilloDeclParser()
{
    auto sin = parse_word("sinus", OscilloSelect::Sinus);
    auto squ = parse_word("square", OscilloSelect::Square);
    auto saw = parse_word("saw", OscilloSelect::Saw);
    auto tri = parse_word("triangle", OscilloSelect::Triangle);
    return ((sin | squ | saw | tri) & Tok(parse_word())) %
           [](auto x) { return DeclareOsc(x.first, x.second); };
}

auto NoteParser()
{
    auto note_name =
        parser_pred(parse_char(), [](char c) { return 'A' <= c && c <= 'G'; });

    auto octave = parser_pred(parse_uint(), [](int o) { return o <= 8; });

    return (note_name & !(parse_char('#') | parse_char('b')) & octave) %
           [](auto x) {
               constexpr std::array<int, 7> notes_val = {
                   {-3, -1, 0, 2, 4, 5, 7},
               };
               int note = notes_val[std::get<0>(x) - 'A'];
               if (std::get<1>(x))
               {
                   note += (*std::get<1>(x) == '#') ? 1 : -1;
               }
               return note + std::get<2>(x) * 12;
           };
}

auto GenerateParser()
{

    auto set_freq =
        (parse_word("set_note") >> (Tok(parse_word()) & Tok(NoteParser()))) %
        [](auto x) { return SetNote(x.first, x.second); };

    auto play = ((parse_word("play") >> Tok(parse_uint())) &
                 list_of(Tok(parse_word()))) %
                [](auto&& x) { return Play(x.first, x.second); };

    auto command = (OscilloDeclParser() %
                    [](auto&& x) {
                        return boost::variant<DeclareOsc, SetNote, Play>(x);
                    }) |
                   (play %
                    [](auto&& x) {
                        return boost::variant<DeclareOsc, SetNote, Play>(x);
                    }) |
                   (set_freq % [](auto&& x) {
                       return boost::variant<DeclareOsc, SetNote, Play>(x);
                   });

    return list_of(Tok(command) << !skip_while(Tok(parse_char('\n'))));
}
