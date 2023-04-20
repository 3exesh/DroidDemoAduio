/**
  ******************************************************************************
  * @file           : Bluetooth.cpp
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

#ifndef BLUETOOTH_HPP_
#define BLUETOOTH_HPP_
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include "Llib/primitives/memory/LArray.hpp"
#include "Llib/common/interfaces/BluetoothService.hpp"

class Bluetooth{
public:
    static int  init             (                                                 );
    static int  enable           (                                                 );
    static int  startAdvertising (                                                 );
    static int  stopAdvertising  (                                                 );
    static void connect          (BluetoothService& btService                      );
    static void set              (BluetoothService** btAdvMemory_p,  size_t memSize);
    static void set              (bt_data* btServMemory_p,           size_t memSize);
private:
    static inline bt_le_adv_param           _ad_param                 = {0};
    static inline bt_conn_cb                _conn_callbacks           = {0};
    static inline bt_conn_auth_cb           _auth_cb_display          = {0};
    static inline bt_conn_auth_info_cb      _conn_auth_info_callbacks = {0};
    static inline bt_gatt_cb                _gatt_callbacks           = {0};
    static inline LArray<BluetoothService*> _bt_service_arr;
    static inline LArray<bt_data>           _bt_ad_arr;
private:
    static void cb_devConnected         (bt_conn *conn, uint8_t err);
    static void cb_devDisconnected      (bt_conn *conn, uint8_t reason);
    static void cb_authenticationCancel (bt_conn *conn);
    static void cb_pairingComplete      (bt_conn *conn, bool bonded);
    static void cb_pairingFailed        (bt_conn *conn, bt_security_err reason);
    static void cb_pairingConfirm       (bt_conn *conn);
    static void cb_mtuUpdated           (bt_conn *conn, uint16_t tx, uint16_t rx);
};
#endif //BLUETOOTH_HPP_