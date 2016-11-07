#pragma once

#include "optional.h"

#include <string>
#include <tuple>
#include <vector>

typedef std::string::const_iterator str_iterator;

template <class F>
class Parser {
    const F fun_;

   public:
    template <class F2>
    Parser(F2 f) : fun_(f) {}

    template <class F2>
    Parser(Parser<F2>&& f) : fun_(f.fun_) {}

    template <class F2>
    Parser(const Parser<F2>& f) : fun_(f.fun_) {}

    auto operator()(str_iterator begin, str_iterator end) const {
        return fun_(begin, end);
    }
};

template <class F>
auto make_parser(F&& f) {
    return Parser<F>(std::forward<F>(f));
}

template <class T>
using ParserRet = optional<std::pair<T, std::string::const_iterator>>;

template <class T>
using parser_ret_type =
    decltype(std::declval<T>()(str_iterator(), str_iterator())->first);

class Empty {};

auto parse_char() {
    return make_parser([](str_iterator begin, str_iterator end) {
        if (begin != end) {
            return make_optional(std::make_pair(*begin, begin + 1));
        }
        return ParserRet<char>();
    });
}

template <class Par, class Pred>
auto parser_pred(Par par, Pred p) {
    return make_parser([par, p](str_iterator begin,
                                str_iterator end) -> decltype(par(begin, end)) {
        auto res = par(begin, end);
        if (!res) {
            return None();
        }
        if (p(res->first)) {
            return res;
        }
        return None();
    });
}

template <class P, class T, class R = Empty>
auto parse_seq(P p, T str, R x = R()) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        ParserRet<decltype(p(end, end)->first)> ret;
        auto iter = begin;
        T str2 = str;
        for (; *str2; ++str2) {
            ret = parser_pred(p, [=](auto c) { return c == *str2; })(iter, end);
            if (!ret) {
                return ParserRet<R>();
            }
            iter = ret->second;
        }
        return make_optional(std::make_pair(x, ret->second));
    });
}

template <class P1, class P2>
auto pthen(P1 p1, P2 p2) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        auto res = p1(begin, end);
        if (res) {
            return p2(res->first)(res->second, end);
        }
        return decltype(p2(res->first)(res->second, end))();
    });
}

template <class P1, class P2>
auto operator>>=(Parser<P1> p1, P2 p2) {
    return pthen(p1, p2);
}

template <class P1>
auto poptional(P1 p1) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        auto res = p1(begin, end);
        if (res) {
            return make_optional(
                std::make_pair(make_optional(res->first), res->second));
        }
        return make_optional(
            std::make_pair(optional<decltype(res->first)>(), begin));
    });
}

template <class P1>
auto operator!(Parser<P1> p1) {
    return poptional(p1);
}

template <class T, class F>
auto apply(T&& x, F&& f) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        return x(begin, end).fmap([=](auto&& a) {
            return std::make_pair(f(a.first), a.second);
        });
    });
}

template <class T, class F>
auto operator%(Parser<T> x, F&& f) {
    return apply(x, f);
}

namespace {
template <class T>
struct to_tuple;

template <class... Ts>
struct to_tuple<std::tuple<Ts...>> {
    template <class U>
    static decltype(auto) do_it(U&& x) {
        return std::forward<U>(x);
    }
};

template <class T, class U>
struct to_tuple<std::pair<T, U>> {
    template <class V>
    static decltype(auto) do_it(V&& x) {
        return std::forward<V>(x);
    }
};

template <class T>
struct to_tuple {
    template <class U>
    static decltype(auto) do_it(U&& x) {
        return std::make_tuple(std::forward<U>(x));
    }
};

template <class T, class U>
decltype(auto) as_pair(std::tuple<T, U>&& tup) {
    return std::make_pair(std::get<0>(tup), std::get<1>(tup));
}

template <class... Ts>
decltype(auto) as_pair(std::tuple<Ts...>&& tup) {
    return std::move(tup);
}
}

template <class T, class U>
auto chain(T a, U b) {
    return a >>= [=](auto&& r) {
        return b % [=](auto&& r2) {
            return as_pair(std::tuple_cat(
                to_tuple<typename std::decay<decltype(r)>::type>::do_it(r),
                to_tuple<typename std::decay<decltype(r2)>::type>::do_it(r2)));
        };
    };
}

template <class P1, class P2>
auto operator&(Parser<P1> p1, Parser<P2> p2) {
    return chain(p1, p2);
}

template <class T, class U>
auto skipL(T a, U b) {
    return a >>= [=](auto) { return b; };
}

template <class T, class U>
auto operator>>(Parser<T> a, Parser<U> b) {
    return skipL(a, b);
}

template <class T, class U>
auto skipR(T a, U b) {
    return a >>= [=](auto&& r) { return b % [r](auto) { return r; }; };
}

template <class T, class U>
auto operator<<(Parser<T> a, Parser<U> b) {
    return skipR(a, b);
}

template <class P, class U, class F>
auto parse_while(P p, U u, F f) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        ParserRet<U> ret(std::make_pair(u, begin));
        while (1) {
            auto res = p(ret->second, end);
            if (!res) {
                return ret;
            }
            ret = ParserRet<U>(
                std::make_pair(f(ret->first, res->first), res->second));
        }
    });
}

template <class P>
auto skip_while(P p) {
    return parse_while(p, Empty(), [](auto, auto) { return Empty(); });
}

template <class P, class U, class F>
auto parse_while1(P p, U u, F f) {
    return p >>= [=](const auto& res) { return parse_while(p, f(u, res), f); };
}

template <class P>
auto skip_while1(P p) {
    return parse_while1(p, Empty(), [](auto, auto) { return Empty(); });
}

template <class... Ts>
auto parse_try(Ts... p1);

template <class T>
auto parse_try(T p) {
    return p;
}

template <class T, class... Ts>
auto parse_try(T p, Ts... ps) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        auto res = p(begin, end);
        if (res) {
            return res;
        }
        return parse_try(ps...)(begin, end);
    });
}

template <class P1, class P2>
auto operator|(Parser<P1> p1, Parser<P2> p2) {
    return parse_try(p1, p2);
}

template <class T>
auto parse_nothing(T x) {
    return make_parser([=](str_iterator begin, str_iterator end) {
        return make_optional(std::make_pair(x, begin));
    });
}

template <class P>
auto list_of(P&& p) {
    return make_parser([=](str_iterator b, str_iterator e) {
        std::vector<decltype(p(str_iterator(), str_iterator())->first)> vec;

        auto res = parse_while1(p, &vec, [](auto&& vecptr, auto&& x) {
            vecptr->push_back(x);
            return vecptr;
        })(b, e);

        if (!res) {
            return ParserRet<decltype(vec)>();
        }
        return make_optional(std::make_pair(std::move(vec), res->second));
    });
};
