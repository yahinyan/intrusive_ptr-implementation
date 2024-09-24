#include "intrusive_ptr.hpp"

template <typename T>
intrusive_ptr<T>::intrusive_ptr(T *_new)
    : m_ob(new data<T>{new int(1), _new})
{}

template <typename T>
void intrusive_ptr<T>::add() 
{
    (*m_ob->m_count)++;
}

template <typename T>
void intrusive_ptr<T>::sub()
{
    (*m_ob->m_count)--;
}

template <typename T>
intrusive_ptr<T>::intrusive_ptr(const intrusive_ptr<T> &other)
    : m_ob {other.m_ob}
{
    add();
}

template <typename T>
intrusive_ptr<T>::intrusive_ptr(intrusive_ptr<T> &&other) 
    : m_ob(std::exchange(other.m_ob, nullptr))
{}

template <typename T>
intrusive_ptr<T>::~intrusive_ptr() 
{
    if(*m_ob->m_count == 0) {
        delete m_ob->m_ptr;
        delete m_ob->m_count;
        delete m_ob;
    }
    sub();
}

template <typename T>
intrusive_ptr<T>& intrusive_ptr<T>::operator=(const intrusive_ptr &other) 
{
    if(this != &other) {
        if(--(*m_ob->m_count)-- == 0) {
            delete m_ob-> m_count;
            delete m_ob-> m_ptr;
            delete m_ob;
        }
        m_ob->m_ptr = other.m_ob->m_ptr;
        m_ob->m_count = other.m_ob->m_count;
        ++(*m_ob->m_count);
    }
    return *this;
}

template <typename T>
intrusive_ptr<T>& intrusive_ptr<T>::operator=(intrusive_ptr &&other) {
    if(this != &other) {
        if(--(*m_ob->m_count) == 0) {
            delete m_ob-> m_count;
            delete m_ob-> m_ptr;
            delete m_ob;
        }
        m_ob-> m_ptr = std::exchange(other.m_ob->m_ptr, nullptr);
        m_ob-> m_count = std::exchange(other.m_ob->m_count, nullptr);
    }
    return *this;
}

template <typename T>
void intrusive_ptr<T>::swap(intrusive_ptr &other) {
    std::swap(m_ob, other.m_ob);
}

template <typename T>
T* intrusive_ptr<T>::get() {
    return m_ob->m_ptr;
}

template <typename T>
T intrusive_ptr<T>::operator*() {
    return *m_ob->m_ptr;
}

template <typename T>
T* intrusive_ptr<T>::operator->() {
    return m_ob->m_ptr;
}