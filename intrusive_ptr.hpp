#ifndef INTRUSIVE_PTR_HPP
#define INTRUSIVE_PTR_HPP

#include <iostream>
#include <utility>

template <typename T>
struct data
{
    int* m_count;
    T* m_ptr;
};

template <typename T>
class intrusive_ptr
{
private:
    data<T>* m_ob;

public:
    intrusive_ptr(T *_new);
    void add();
    void sub();
    intrusive_ptr(const intrusive_ptr<T> &other);
    intrusive_ptr(intrusive_ptr<T> &&other);
    ~intrusive_ptr();
    intrusive_ptr &operator=(const intrusive_ptr &other);
    intrusive_ptr &operator=(intrusive_ptr &&other);
    void swap(intrusive_ptr &other);
    T *get();
    T operator*();
    T *operator->();
};

#include "intrusive_ptr.cpp"
#endif // intrusive_ptr.hpp