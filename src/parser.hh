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

struct EnvConfig
{
    std::string name;
    int phase;
    int start_time;
    float volume;

    EnvConfig() = default;
    EnvConfig(std::string n, int p, int st, float v)
        : name(n)
        , phase(p)
        , start_time(st)
        , volume(v)
    {
    }
};

struct EnvDecl
{
    std::string name;
    std::string source;

    EnvDecl() = default;
    EnvDecl(std::string n, std::string s)
        : name(n)
        , source(s)
    {
    }
};

struct EnvReset
{
    std::string name;

    EnvReset() = default;
    EnvReset(std::string n)
        : name(n)
    {
    }
};

struct MergeDecl
{
    std::string name;
    std::vector<std::string> inputs;

    MergeDecl() = default;
    MergeDecl(std::string n, std::vector<std::string> is)
        : name(n)
        , inputs(is)
    {
    }
};

using Command = boost::variant<DeclareOsc, SetNote, Play, EnvDecl, EnvConfig,
                               EnvReset, MergeDecl>;

template <class P>
auto Tok(P p)
{
    return skip_while(parser_pred(parse_char(), isblank)) >> p;
}

auto ParseId()
{
    return parse_while1(
        parser_pred(parse_char(),
                    [](auto c) { return isalnum(c) | (c == '_'); }),
        std::string(), [](std::string res, char c) {
            res.push_back(c);
            return res;
        });
}

auto OscilloDeclParser()
{
    auto sin = parse_word("sinus", OscilloSelect::Sinus);
    auto squ = parse_word("square", OscilloSelect::Square);
    auto saw = parse_word("saw", OscilloSelect::Saw);
    auto tri = parse_word("triangle", OscilloSelect::Triangle);
    return ((sin | squ | saw | tri) & Tok(ParseId())) %
           [](auto x) { return DeclareOsc(x.first, x.second); };
}

auto NoteParser()
{
    auto note_name =
        parser_pred(parse_char(), [](char c) { return 'A' <= c && c <= 'G'; });

    auto octave = parser_pred(parse_uint(), [](int o) { return o <= 8; });

    auto note_to_code = [](auto x) {
        constexpr std::array<int, 7> notes_val{
            {-3, -1, 0, 2, 4, 5, 7},
        };
        int note = notes_val[std::get<0>(x) - 'A'];
        if (std::get<1>(x))
            note += (*std::get<1>(x) == '#') ? 1 : -1;

        return note + std::get<2>(x) * 12;
    };

    return (note_name & !(parse_char('#') | parse_char('b')) & octave) %
           note_to_code;
}

auto AdsrParser()
{
    auto decl = (parse_word("adsr") >> Tok(ParseId()) & Tok(ParseId())) %
                [](auto x) { return EnvDecl(x.first, x.second); };
    auto reset = (parse_word("reset") >> Tok(ParseId())) %
                 [](auto x) { return EnvReset(x); };
    auto atk = parse_word("set_attack", 1);
    auto dky = parse_word("set_decay", 2);
    auto sus = parse_word("set_sustain", 3);
    auto rlz = parse_word("set_release", 4);
    auto config = ((atk | dky | sus | rlz) & Tok(ParseId()) &
                   Tok(parse_uint()) & Tok(parse_uint())) %
                  [](auto x) {
                      return EnvConfig(std::get<1>(x), std::get<0>(x),
                                       std::get<2>(x), std::get<3>(x) / 100.f);
                  };

    return (decl % [](auto x) { return Command(x); }) |
           (reset % [](auto x) { return Command(x); }) |
           (config % [](auto x) { return Command(x); });
}

auto GenerateParser()
{

    auto set_freq =
        (parse_word("set_note") >> (Tok(ParseId()) & Tok(NoteParser()))) %
        [](auto x) { return SetNote(x.first, x.second); };

    auto play =
        ((parse_word("play") >> Tok(parse_uint())) & list_of(Tok(ParseId()))) %
        [](auto&& x) { return Play(x.first, x.second); };

    auto merge =
        (parse_word("merge") >> Tok(ParseId()) & list_of(Tok(ParseId()))) %
        [](auto x) { return MergeDecl(x.first, x.second); };

    auto command = (OscilloDeclParser() % [](auto&& x) { return Command(x); }) |
                   (play % [](auto&& x) { return Command(x); }) |
                   (set_freq % [](auto&& x) { return Command(x); }) |
                   (merge % [](auto&& x) { return Command(x); }) | AdsrParser();

    return list_of(Tok(command) << !skip_while(Tok(parse_char('\n'))));
}
