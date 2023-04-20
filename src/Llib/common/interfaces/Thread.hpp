/**
  ******************************************************************************
  * @file           : Thread.cpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           : 04.11.2023 08:23
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef THREAD_HPP_
#define THREAD_HPP_
#include "Llib/common/log/log.hpp"


#define L_THREAD_DEFINE(NAME_threadHandler, stack_size, prio, options, delay) \
K_THREAD_STACK_DEFINE(_k_thread_stack_ ## NAME_threadHandler, stack_size); \
extern _static_thread_data _k_thread_data_ ## NAME_threadHandler; \
ThreadHandler NAME_threadHandler = {.k_thread_data_p = (&_k_thread_data_ ## NAME_threadHandler),}; \
void entry_function_ ## NAME_threadHandler(){if(NAME_threadHandler.thread_p == NULL){PRINTKS_ERROR("THREAD","\"ThreadHandler\" object is not connected to any \"Thread\" obeject", STRINGIFY(NAME_threadHandler)); return;} NAME_threadHandler.thread_p->main();} \
STRUCT_SECTION_ITERABLE(_static_thread_data, _k_thread_data_ ## NAME_threadHandler) = \
Z_THREAD_INITIALIZER(&NAME_threadHandler.thread_data, \
                     _k_thread_stack_ ## NAME_threadHandler, \
                     stack_size, \
                     (entry_function_ ## NAME_threadHandler), \
                     NULL, NULL, NULL, prio, options, delay, NAME_threadHandler);



class Thread;

struct ThreadHandler
{
public:
          _static_thread_data* k_thread_data_p;
          k_thread             thread_data;
    const k_tid_t              tid                = (k_tid_t)&thread_data;
          Thread*              thread_p           = NULL;
};

class Thread{
public:
    virtual void main () = 0;
            void set  (ThreadHandler& th) { _theradHandler_p = &th; th.thread_p = this;}
private:
    ThreadHandler* _theradHandler_p = NULL;
};

#endif //THREAD_HPP_