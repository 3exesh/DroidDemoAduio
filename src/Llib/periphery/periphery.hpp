/**
  ******************************************************************************
  * @file           : periphery.cpp
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

#ifndef PERIPHERY_HPP_
#define PERIPHERY_HPP_
#include <zephyr/kernel.h>
#include "Llib/common/log/log.hpp"



typedef enum : int
{   ps_ok            =  0,
    ps_error         = -1, // - Common error type.
    ps_noSuchDevice  = -2, // - No such device in deivce tree.
    ps_enablingError = -3, // - Device enabling error occurred.
    ps_notReady      = -4, // - Device internal error occurred.
    ps_configError   = -5, // - Device configaration error.
    ps_memoryError   = -6, // - Memory error occurred.
}periph_status_t;

#endif //PERIPHERY_HPP_