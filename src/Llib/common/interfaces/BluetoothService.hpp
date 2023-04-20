/**
  ******************************************************************************
  * @file           : BluetoothService.cpp
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

#ifndef BLUETOOTHSERVICE_HPP_
#define BLUETOOTHSERVICE_HPP_
#include <zephyr/types.h>
#include <zephyr/bluetooth/conn.h>

class Bluetooth;

class BluetoothService{
public:
    friend class Bluetooth;
protected:
    bt_data _bt_le_ad_header_service = {0};
};

#endif //BLUETOTHSERVICE_HPP_