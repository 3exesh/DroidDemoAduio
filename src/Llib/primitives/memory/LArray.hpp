/**
  ******************************************************************************
  * @file           : LArray.hpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           : 04.15.2023 12:07
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef LARRAY_HPP_
#define LARRAY_HPP_
#include "Llib/common/interfaces/MemoryArray.hpp"


template<typename T> class LArray : public MemoryArray<T>{
public:
         LArray    (                         ){};
         LArray    (T* arr_p, size_t arrSize );
    bool setArr    (T* arr_p, size_t arrSize );
private:
    using MemoryArray<T>::_arr_p;
    using MemoryArray<T>::_size;
    using MemoryArray<T>::_capacity;
};

template <typename T> bool LArray<T>::setArr(T* arr_p, size_t arrSize ){
    if((_capacity > 0) || (arr_p == NULL)) return false;// object re-creation rejection.
    _arr_p    = arr_p;
    _capacity = arrSize; //used only for memory boundaries control.
    return true;
}

template <typename T> LArray<T>::LArray(T* arr_p, size_t arrSize ){
    __ASSERT_NO_MSG(setArr(arr_p,arrSize));
#ifndef __ASSERT_ON
    setArr(arr_p,arrSize);
#endif
}
#endif //LARRAY_HPP_