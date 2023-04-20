
/**
  ******************************************************************************
  * @file           : MemoryArray.hpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           : 04.14.2023 16:25
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef MemoryArray_HPP_
#define MemoryArray_HPP_
#include <zephyr/kernel.h>
#include <zephyr/sys/__assert.h>

template<typename T> class MemoryArray{
public:
    virtual              T&     operator[]   (size_t ix                );
    virtual        const T&     operator[]   (size_t ix                ) const;
    virtual              bool   at           (size_t ix, const T& el   );
    virtual        const T&     at           (size_t ix                ) const;
    virtual inline       size_t size         (                         ) const;
    virtual inline       size_t capacity     (                         ) const;
    virtual inline const T*     data         (                         );
    virtual              bool   clean        (                         );
    virtual              bool   prepare      (                         );
    virtual              bool   push_back    (const T& el              );
protected:
    T*     _arr_p    = NULL;
    size_t _size     = 0; // used for get information about number valid data in array.
    size_t _capacity = 0; // currently vector capacity can only increase, provided only for downsize implementation.
};

template <typename T> T& MemoryArray<T>::operator[](size_t ix){
    __ASSERT_NO_MSG(_arr_p != NULL);
    return _arr_p[ix];
}

template <typename T> const T& MemoryArray<T>::operator[](size_t ix) const {
    __ASSERT_NO_MSG(_arr_p != NULL);
    __ASSERT_NO_MSG(ix < _size);
    return _arr_p[ix];
}

template <typename T> bool MemoryArray<T>::at(size_t ix, const T& el){
    __ASSERT_NO_MSG(_arr_p != NULL);
    if(!(ix < _size)) return false;
    _arr_p[ix] = el;
    return true;
}

template <typename T> inline const T& MemoryArray<T>::at(size_t ix) const {
    __ASSERT_NO_MSG(_arr_p != NULL);
    __ASSERT_NO_MSG(ix < _size);
    return _arr_p[ix];
}

template <typename T> inline size_t MemoryArray<T>::size() const {
    return _size;
}

template <typename T> inline size_t MemoryArray<T>::capacity() const {
   return _capacity;
}

template <typename T> inline const T* MemoryArray<T>::data(){
    return _arr_p;
}

template <typename T> bool MemoryArray<T>::prepare(){
    __ASSERT_NO_MSG(_arr_p !=  NULL);
    if(_capacity == 0) return false;
    memset(_arr_p, 0, sizeof(T)*_capacity);
    return true;
}


template <typename T> bool MemoryArray<T>::clean(){
    return prepare();
    _size = 0;
}


template <typename T> bool MemoryArray<T>::push_back(const T& el){
     if(_size == _capacity) return false;
     _arr_p[_size] =  el;
     _size         += 1;
     return true;
}
#endif //MemoryArray_HPP_