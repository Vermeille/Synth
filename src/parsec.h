#pragma once

#include "combinators.h"

auto parse_digit() {
    return parser_pred(parse_char(), isdigit) %
               [](char c) -> int { return c - '0'; };
}

auto parse_uint() {
    return parse_while1(
        parse_digit(), 0, [](int a, int b) -> int { return a * 10 + b; });
}

auto ignore_whitespaces() {
    return skip_while(parser_pred(parse_char(), isspace));
}

auto parse_int() {
    return !parser_pred(parse_char(), [](char c) { return c == '-'; }) >>=
           [](auto x) {
               return parse_uint() % [=](int i) { return x ? -i : i; };
           };
}

template <class Str, class T = Empty>
auto parse_word(Str str, T x = T()) {
    return parse_seq(parse_char(), str, x);
}

auto parse_word() {
    return parse_while1(parser_pred(parse_char(), isalpha),
                        std::string(),
                        [](std::string res, char c) {
                            res.push_back(c);
                            return res;
                        });
}

auto parse_char(char c) {
    return parser_pred(parse_char(), [=](char x) { return x == c; });
}

template <class P>
auto recursion(P& p) {
    return make_parser(
        [&](str_iterator begin, str_iterator end) { return p(begin, end); });
}
