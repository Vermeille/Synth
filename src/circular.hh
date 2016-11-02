#pragma once

template <class T>
class CircularBuffer
{
    public:
        typedef T value_type;
        CircularBuffer(int size, T init);
        ~CircularBuffer();

        const T& operator[](int idx) const;
        T& operator[](int idx);

        void push_front(T val);
        unsigned size() const;

    private:
        T* buf_;
        unsigned size_;
        unsigned idx_;
};

template <class T>
CircularBuffer<T>::CircularBuffer(int size, T init)
    : size_(size),
    idx_(0)
{
    buf_ = new T[size_];
}

template <class T>
CircularBuffer<T>::~CircularBuffer()
{
    delete[] buf_;
}

template <class T>
const T& CircularBuffer<T>::operator[](int idx) const
{
    return buf_[(idx_ + idx) % size_];
}

template <class T>
T& CircularBuffer<T>::operator[](int idx)
{
    return buf_[(idx_ + idx) % size_];
}

template <class T>
void CircularBuffer<T>::push_front(T val)
{
    idx_ = (idx_ - 1 + size_) % size_;
    buf_[idx_] = val;
}

template <class T>
unsigned CircularBuffer<T>::size() const
{
    return size_;
}
