/**
  ******************************************************************************
  * @file           : Player.hpp
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
 
#ifndef PLAYER_HPP_ 
#define PLAYER_HPP_

#include "audio.hpp"
#include "Llib/common/interfaces/Thread.hpp"
#include "Llib/common/interfaces/DataStream.hpp"


typedef enum class Player_fsm_st : int {
    stop     = 0,
    play     = 1,
    finalize = 2,
    error    = 2
} Player_fsm_t;

class Player : public Thread{
public: 
    void init     (                              ) {k_mutex_init(&_next_state_lock_mut); k_sem_init(&_awake_sem, 0, 1);}
    void connect  (      OutDataStream& ostream  ) {_ostream_p = &ostream;}
    void soud     (const rawSound_t&    rawSount );
    void play     ();
    void pause    ();
    void stop     ();
    bool isPlay   ();

    void main     () override;
private:
          OutDataStream* _ostream_p  = NULL;
    const rawSound_t*    _rawSount_p = NULL;
          size_t         _position   = 0;
          Player_fsm_t   _state      = Player_fsm_t::stop;
          Player_fsm_t   _next_state = Player_fsm_t::stop;
          k_sem          _awake_sem;
          k_mutex        _next_state_lock_mut;

};


#endif //PLAYER_HPP_