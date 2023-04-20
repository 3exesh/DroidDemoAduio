/**
  ******************************************************************************
  * @file           : PlayerControlService.hpp
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

#ifndef PLAYER_CONTROL_SERVICE_HPP_
#define PLAYER_CONTROL_SERVICE_HPP_
#include <zephyr/bluetooth/gatt.h>
#include "Llib/common/interfaces/BluetoothService.hpp"
#include "Llib/primitives/audio/Player.hpp"

#include "sounds/sound_list.hpp"

class PlayerControlService : public BluetoothService{
public:
           int     init();
           void    connect(Player& player) {_player = &player;}
    static ssize_t get_cmd(bt_conn *conn, const  bt_gatt_attr *attr,
                          const void *buf, uint16_t len, 
                    uint16_t offset, uint8_t flags);
private:
                  Player*               _player = NULL;
    static inline PlayerControlService* _tmp_p  = NULL;;
};

#endif // PLAYER_CONTROL_SERVICE_HPP_
