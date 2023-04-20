/**
  ******************************************************************************
  * @file           : audio.cpp
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

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <zephyr/types.h>
#include <zephyr/toolchain/common.h>
#include "Llib/common/params.hpp"

typedef struct
{
    const uint16_t*     data_p;
          size_t        length;
    const char*         name;
          audio_param_t params;
}rawSound_t;



#endif //AUDIO_HPP_