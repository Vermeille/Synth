#pragma once

#include <cassert>
#include <utility>

template <class T>
class optional {
    T val_;
    bool present_;

   public:
    optional(T&& x) : val_(x), present_(true) {}
    optional() : present_(false) {}

    operator bool() const { return present_; }
    T* operator->() {
        assert(present_);
        return &val_;
    }
    const T* operator->() const {
        assert(present_);
        return &val_;
    }

    T& operator*() {
        assert(present_);
        return val_;
    }
    const T& operator*() const {
        assert(present_);
        return val_;
    }

    template <class F>
    auto then(F&& f) {
        if (present_) {
            return f(val_);
        } else {
            return optional<decltype(f(val_))>();
        }
    }
    template <class F>
    auto fmap(F&& f) -> optional<decltype(f(val_))> {
        if (present_) {
            return optional<decltype(f(val_))>(f(val_));
        } else {
            return optional<decltype(f(val_))>();
        }
    }

    optional& operator=(optional&& o) = default;
    optional(optional&&) = default;
    optional(const optional&) = default;
};

struct None {
    template <class T>
    operator optional<T>() const {
        return optional<T>();
    }
};

template <class T, class F>
auto operator>>=(const optional<T>& o, F&& f) -> decltype(f(*o)) {
    if (o) {
        return f(*o);
    } else {
        return decltype(f(*o))();
    }
}

template <class T>
optional<T> make_optional(T x) {
    return optional<T>(std::forward<T>(x));
}

extern const None none;
