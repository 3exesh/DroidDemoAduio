/**
  ******************************************************************************
  * @file           : LArrayFixed.hpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           : 04.16.2023 12:07
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef LARRAY_FIXED_HPP_
#define LARRAY_FIXED_HPP_
#include "Llib/common/interfaces/MemoryArray.hpp"


template<typename T, size_t capacity> class LArrayFixed : public MemoryArray<T>{
public: 
    LArrayFixed(){};
private:
    using MemoryArray<T>::_size;
           T      _arr_p[capacity];
           size_t _capacity = capacity;
};
#endif //LARRAY_FIXED_HPP_