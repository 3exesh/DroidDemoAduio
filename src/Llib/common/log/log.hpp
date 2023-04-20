/**
  ******************************************************************************
  * @file           : log.hpp
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
#ifndef LOG_HPP_ 
#define LOG_HPP_

#include <zephyr/kernel.h>
#include <zephyr/types.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>
#include <string.h>

#define PRINTX_ERROR_PRINTK
#define PRINTX_INFO_PRINTK

static const char* moduleNameTitle_n_str  = "[%s]%s %s : %d\n";
static const char* moduleNameTitle_s_str  = "[%s]%s %s : \"%s\"\n";
static const char* moduleNameTitle_str    = "[%s]%s %s\n";
static const char* moduleErrorTitle_str = "<ERROR>";
static const char* moduleInfoTitle_str = "<info>";

//#if defined(PRINTX_ERROR_ZELOG) || defined(PRINTX_INFO_ZELOG)
//    #define LOG_MODULE_NAME log
//    LOG_MODULE_REGISTER(LOG_MODULE_NAME)
//    LOG_MODULE_DECLARE();(IS_ENABLED(L_DEBUG))?:
//#endif

#if defined(PRINTX_ERROR_PRINTK) && defined(L_PRINTKX_DEBUG)
    #define PRINTKN_ERROR(...) printk(moduleNameTitle_n_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
    #define PRINTKS_ERROR(...) printk(moduleNameTitle_s_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
    #define PRINTK_ERROR(...)  printk(moduleNameTitle_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
#elif defined(PRINTX_ERROR_ZELOG)
    #define PRINTKN_ERROR(...) LOG_ERR(moduleNameTitle_n_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
    #define PRINTKS_ERROR(...) LOG_ERR(moduleNameTitle_s_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
    #define PRINTK_ERROR(...)  LOG_ERR(moduleNameTitle_str,printkx_title_str,moduleErrorTitle_str, __VA_ARGS__)
#else
    #define PRINTKN_ERROR(...)
    #define PRINTKS_ERROR(...)
    #define PRINTK_ERROR(...)
#endif

#if defined(PRINTX_INFO_PRINTK) && defined(L_PRINTKX_DEBUG)
    #define PRINTKN_INFO(...)  printk(moduleNameTitle_n_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
    #define PRINTKS_INFO(...)  printk(moduleNameTitle_s_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
    #define PRINTK_INFO(...)   printk(moduleNameTitle_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
#elif defined(PRINTX_INFO_ZELOG)
    #define PRINTKN_INFO(...)  LOG_INF(moduleNameTitle_n_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
    #define PRINTKS_INFO(...)  LOG_INF(moduleNameTitle_s_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
    #define PRINTK_INFO(...)  LOG_INF(moduleNameTitle_str,printkx_title_str,moduleInfoTitle_str, __VA_ARGS__)
#else
    #define PRINTKN_INFO(...)
    #define PRINTKS_INFO(...)
    #define PRINTK_INFO(...)
#endif


#endif //LOG_HPP_