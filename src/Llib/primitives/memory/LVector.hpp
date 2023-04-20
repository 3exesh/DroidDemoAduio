/**
  ******************************************************************************
  * @file           : LVector.hpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           : 04.14.2023 17:41
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef LVECTOR_HPP_
#define LVECTOR_HPP_
#include "Llib/common/interfaces/MemoryArray.hpp"


template<typename T> class LVector : public MemoryArray<T>{
public:
         LVector      (                ){};
         LVector      (size_t vectSize );
         ~LVector     (                );
    bool push_back    (const T& el     ) override;
    bool resize       (size_t reqSize  );
    bool optimaze     (                );
private:
    bool _recapacity  (size_t reqSize  );
private:
    using MemoryArray<T>::_arr_p;
    using MemoryArray<T>::_size;
    using MemoryArray<T>::_capacity;
};

template <typename T> LVector<T>::LVector(size_t vectSize){
    __ASSERT_NO_MSG(_capacity == 0);// object re-creation rejection.
    _arr_p    = k_malloc(sizeof(T)*vectSize);
    __ASSERT_NO_MSG(_arr_p != NULL);
    _capacity = vectSize; //used only for memory boundaries control and memory optimization purposes.
}

template <typename T> LVector<T>::~LVector(){
    if(_arr_p != NULL) k_free(_arr_p);
}


template <typename T> bool LVector<T>::resize(size_t reqSize){
    if(reqSize > _capacity) if(!_recapacity(reqSize)) return false;
    _size = reqSize; 
    return true;
}

template <typename T> bool LVector<T>::optimaze(){
    if(_capacity > _size) if(!_recapacity(_size)) return false;
    return true;
}

template <typename T> bool LVector<T>::push_back(const T& el){
    if(_size == _capacity) if(!_recapacity(_size+1)) return false;
    _arr_p[_size] =  el;
    _size         += 1;
    return true;
}


//PRIVATE:
template <typename T> bool LVector<T>::_recapacity(size_t reqSize){
    __ASSERT_NO_MSG(_arr_p != NULL);
    T* newArr_p               = k_malloc(sizeof(T)*reqSize);
    if(newArr_p == NULL) return false;
    _capacity                 = reqSize;
    if(_size > reqSize) _size = reqSize;
    memcpy(newArr_p, _arr_p, sizeof(T)*_size);
    k_free(_arr_p);
    _arr_p      = newArr_p;
    return true;
}

#endif //LVECTOR_HPP_