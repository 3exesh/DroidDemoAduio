/**
  ******************************************************************************
  * @file           : DataStream.cpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           :
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef DATASTREAM_HPP_
#define DATASTREAM_HPP_
#include "Llib/common/params.hpp"
#include <zephyr/types.h>

class OutDataStream{
public:
    virtual void output    (void*     data_p, size_t* size_p, size_t* accepted_size) = 0;
    virtual void setParams (params_t* params_p) {};
    virtual void outOpen   () {};
    virtual void outClose  () {};
    virtual void outFlush  () {};
    virtual void outClean  () {};
    virtual bool outIsBusy () {return false;};
};

class InDataStream{
public:
    virtual void input     (void*     data_p, size_t* size_p, size_t* accepted_size) = 0;
    virtual void getParams (params_t* params_p) {};
    virtual void inOpen    () {};
    virtual void inClose   () {};
    virtual void inFlush   () {};
    virtual void inClean   () {};
    virtual bool inIsBusy  () {return false;};
};

#endif //DATASTREAM_HPP_