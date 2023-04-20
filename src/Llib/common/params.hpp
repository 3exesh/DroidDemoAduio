/**
  ******************************************************************************
  * @file           : params.hpp
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
 
#ifndef PARAMS_HPP_ 
#define PARAMS_HPP_
#include <zephyr/types.h>

typedef enum : int
{
  params_st_none  = 0,
  params_st_error = 1, 
  params_st_audio = 2
}params_st_id_t;

typedef struct
{
  params_st_id_t params_st_id;
  void*          params_st_p;
}params_t;

typedef struct
{
    uint8_t  sampleWidth;
    uint8_t  numOfChannels;
    uint16_t sampleRate; 
}audio_param_t;

#endif //PARAMS_HPP_