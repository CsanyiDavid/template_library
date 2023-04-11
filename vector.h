#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include<limits>
#include<algorithm>
#include<initializer_list>

template<typename T>
class Vector{
private:
    size_t m_size{};
    size_t m_capacity{};
    T* m_a;

    size_t get_new_capacity(size_t new_size);
public:
    Vector(size_t size=0, const T& value = T());

    Vector(std::initializer_list<T> init);

    Vector(const Vector& other);

    ~Vector();

    size_t size() const {return m_size;}

    size_t capacity() const {return m_capacity;}

    bool empty() const {return m_size==0;}

    void reserve(size_t new_capacity);

    void resize(size_t new_size, const T& value = T());

    const T& operator[](int index) const {return m_a[index];}

    T& operator[](int index){return m_a[index];}

    void push_back(const T& value);

    Vector& operator=(const Vector& other);
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
Vector<T>::Vector(std::initializer_list<T> init)
    : m_size{0}
    , m_capacity{0}
    , m_a{nullptr}
{
    size_t new_size{init.size()};
    size_t new_capacity{get_new_capacity(new_size)};
    reserve(new_capacity);
    unsigned long long i{0};
    typename std::initializer_list<T>::const_iterator it{init.begin()};
    for(; it!=init.end(); ++it){
        m_a[i] = *it;
        ++i;
    }
    m_size = new_size;
}

template<typename T>
Vector<T>::Vector(const Vector& other)
    : m_size{0}
    , m_capacity{0}
    , m_a{nullptr}
{
    *this = other;
}

template<typename T>
Vector<T>::~Vector(){
    if(m_a){
        delete[] m_a;
    }
}

template<typename T>
void Vector<T>::reserve(size_t new_capacity){
    if(new_capacity > m_capacity){
        T* new_a{new T[new_capacity]{}};
        for(unsigned long long i=0; i<m_size; ++i){
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
        for(unsigned long long i=m_size; i<new_size; ++i){
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

template<typename T>
void Vector<T>::push_back(const T& value){
    if(m_capacity == m_size){
        size_t new_capacity{get_new_capacity(m_size+1)};
        reserve(new_capacity);
    }
    m_a[m_size] = value;
    ++m_size;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other){
    size_t new_capacity{other.capacity()};
    reserve(new_capacity);
    for(unsigned long long i=0; i<other.size(); ++i){
        m_a[i] = other[i];
    }
    m_size = other.size();
    return *this;
}

template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs){
    bool equal{true};
    if(lhs.size() != rhs.size()){
        equal = false;
    } else {
        for(unsigned long long i=0; i<lhs.size(); ++i){
            if(lhs[i] != rhs[i]){
                equal = false;
                break;
            }
        }
    }
    return equal;
}

template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs){
    return !(lhs == rhs);
}

#endif