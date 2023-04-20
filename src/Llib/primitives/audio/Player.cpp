#define L_PRINTKX_DEBUG
#include "Player.hpp"
#include "Llib/common/params.hpp"
#include "Llib/common/log/log.hpp"

static const char* printkx_title_str = "Player";

void Player::main() {
    for(;;){
        PRINTK_INFO("Thread main() called");
        __ASM("NOP");
        k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
        if((_state == Player_fsm_t::stop) && (_next_state == Player_fsm_t::stop)){ //If we don't have a new state
            k_mutex_unlock(&_next_state_lock_mut);
            PRINTK_INFO("Thread go lock");
            k_sem_take(&_awake_sem, K_FOREVER);//Wait until "state" variable will be accessible
            PRINTK_INFO("Thread unlock");
            k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
        }

        if((_state == Player_fsm_t::stop) && (_next_state == Player_fsm_t::play)){
            if(_rawSount_p == NULL){ _next_state = Player_fsm_t::stop; }
            _position                   = 0;
            _state                      = Player_fsm_t::play;
            params_t params = {.params_st_id=(params_st_audio), .params_st_p=((void*)&_rawSount_p->params)};
            _ostream_p->setParams(&params);
        }

        if(_state == Player_fsm_t::play){
            if(_position <= _rawSount_p->length){
                if(_position == 0){//if reading is just started
                    _ostream_p->outOpen();
                }
                size_t left_size    = _rawSount_p->length - _position;
                size_t accepted_size;
                k_mutex_unlock(&_next_state_lock_mut);
                _ostream_p->output(((char*)_rawSount_p->data_p) + _position, &left_size, &accepted_size);
                k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
                _position           += accepted_size;
            }
            if( (_next_state == Player_fsm_t::stop) || (_position >= _rawSount_p->length) ){
                _state               = Player_fsm_t::finalize;
                _ostream_p->outFlush();
            }
        }

        if(_state == Player_fsm_t::finalize){
            if(_ostream_p->outIsBusy()){
                k_mutex_unlock(&_next_state_lock_mut);
                k_msleep(100);
                k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
            }else{
                _state      = Player_fsm_t::stop;
                _next_state = Player_fsm_t::stop;
                _ostream_p->outClose();
            }
        }
        k_mutex_unlock(&_next_state_lock_mut);
    }
}

void Player::soud(const rawSound_t &rawSount){
    k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
    _rawSount_p = &rawSount;
    k_mutex_unlock(&_next_state_lock_mut);
}

void Player::play(){
    k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
    _next_state = Player_fsm_t::play;
    k_mutex_unlock(&_next_state_lock_mut);
    k_sem_give(&_awake_sem);
};

void Player::stop(){
    k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
    _next_state = Player_fsm_t::stop;
    k_mutex_unlock(&_next_state_lock_mut);
};

bool Player::isPlay(){
    k_mutex_lock(&_next_state_lock_mut, K_FOREVER);
    bool tmp = ( (_next_state != Player_fsm_t::stop) || (_state != Player_fsm_t::stop) );
    k_mutex_unlock(&_next_state_lock_mut);
    return tmp;
}