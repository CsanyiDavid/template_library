#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include<limits>
#include<algorithm>

template<typename T>
class Vector{
private:
    size_t m_size{};
    size_t m_capacity{};
    T* m_a;

    size_t get_new_capacity(size_t new_size);
public:
    Vector(size_t size=0, const T& value = T());

    size_t size() const {return m_size;}

    size_t capacity() const {return m_capacity;}

    bool empty() const {return m_size==0;}

    void reserve(size_t new_capacity);

    void resize(size_t new_size, const T& value = T());

    const T& operator[](int index) const {return m_a[index];}

    T& operator[](int index){return m_a[index];}
};

template<typename T>
Vector<T>::Vector(size_t size, const T& value)
    : m_size{0}
    , m_capacity{0}
    , m_a{nullptr}
{
    size_t new_capacity{get_new_capacity(size)};
    reserve(new_capacity);
    resize(size, value);
}

template<typename T>
void Vector<T>::reserve(size_t new_capacity){
    if(new_capacity > m_capacity){
        T* new_a{new T[new_capacity]{}};
        for(unsigned int i=0; i<m_size; ++i){
            new_a[i] = m_a[i];
        }
        if(m_a){
            delete[] m_a;
        }
        m_a = new_a;
        m_capacity = new_capacity;
    }
}

template<typename T>
void Vector<T>::resize(size_t new_size, const T& value){
    if(new_size < m_size){
        m_size = new_size;
    } else if(new_size > m_size){
        if(new_size > m_capacity){
            size_t new_capacity{get_new_capacity(new_size)};
            reserve(new_capacity);
        }
        for(unsigned int i=m_size; i<new_size; ++i){
            m_a[i] = value;
        }
        m_size = new_size;
    }
}

template<typename T>
size_t Vector<T>::get_new_capacity(size_t new_size){
    size_t new_capacity{std::max(m_capacity, static_cast<size_t>(2))};
    while(new_capacity < new_size){
        if(new_capacity > std::numeric_limits<size_t>::max()/2){
            new_capacity = std::numeric_limits<size_t>::max();
            break;
        } else {
            new_capacity *= 2;
        }
    }
    return new_capacity;
}
#endif