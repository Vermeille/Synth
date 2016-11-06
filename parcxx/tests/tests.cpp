#include "parsec.h"

#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

template <class P>
void expect_false(P p, const std::string& a) {
    std::cout << "expect F " << a << "\n";
    auto res = p(std::begin(a), std::end(a));
    assert(!res);
}

template <class P, class T>
void expect_true(P p, const std::string& a, T x) {
    std::cout << "expect T " << a << "\n";
    auto res = p(std::begin(a), std::end(a));
    assert(res->first == x);
}

auto parse_csv() {
    auto append_str = [](auto ws, std::string str) {
        ws.push_back(str);
        return ws;
    };

    auto append_last = [](auto x) -> std::vector<std::string> {
        if (x.first) {
            x.first->push_back(x.second);
            return *x.first;
        } else {
            return std::vector<std::string>({x.second});
        }
    };

    return (!parse_while(parse_word() << parse_char(','),
                         std::vector<std::string>(),
                         append_str) &
            parse_word()) %
           append_last;
}

int main(int argc, char** argv) {
    expect_true(skipL(ignore_whitespaces(), parse_uint()), "666a", 666);
    expect_true(parse_digit(), "1aa", 1);
    expect_true(parse_digit(), "12", 1);
    auto int_2p = (parse_digit() & parse_digit()) %
                  [](auto a) { return a.first * 10 + a.second; };
    expect_true(int_2p, "12", 12);
    expect_false(int_2p, "a2");
    expect_false(parse_uint(), "a2");
    expect_true(parse_uint(), "666", 666);
    expect_true(parse_uint(), "666a", 666);
    expect_false(parse_uint(), "a666a");
    expect_true(parse_int(), "666a", 666);
    expect_true(ignore_whitespaces() >> parse_uint(), "   666a", 666);
    expect_true(ignore_whitespaces() >> parse_int(), "-666a", -666);
    expect_true(ignore_whitespaces() >> parse_int(), "-666a", -666);
    expect_true(parse_word("yes", 42), "yes", 42);
    expect_false(parse_word("yes"), "ayes");
    expect_false(parse_word("yes"), "yea");
    expect_true(parse_uint() << parse_char('.'), "12.", 12);
    expect_false(parse_uint() << parse_char('.'), "12");
    expect_false(parse_uint() << parse_char('.'), "12-");
    expect_true(
        parse_csv(), "a,b,c", std::vector<std::string>({"a", "b", "c"}));
    expect_false(parse_csv(), ",b,c");
    expect_true(parse_char() & parse_char(), "ab", std::make_pair('a', 'b'));
    expect_true(parse_char() & parse_char() & parse_char(),
                "abc",
                std::make_tuple('a', 'b', 'c'));
    expect_true(
        list_of(parse_char()), "abcd", std::vector<char>({'a', 'b', 'c', 'd'}));

    return 0;
}
