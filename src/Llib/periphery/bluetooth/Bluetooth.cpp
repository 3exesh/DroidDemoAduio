#include "Bluetooth.hpp"
#define L_PRINTKX_DEBUG
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/bas.h>

#include <zephyr/sys/__assert.h>
#include "Llib/periphery/periphery.hpp"

static const char* printkx_title_str = "Bluetooth";

void Bluetooth::connect(BluetoothService& btService){
    _bt_service_arr.push_back(&btService);
}

void Bluetooth::set(BluetoothService **btAdvMemory_p, size_t memSize){
    __ASSERT_NO_MSG(btAdvMemory_p  != NULL); _bt_service_arr.setArr(btAdvMemory_p, memSize);
}

void Bluetooth::set(bt_data *btServMemory_p, size_t memSize){
    __ASSERT_NO_MSG(btServMemory_p != NULL); _bt_ad_arr.setArr(btServMemory_p, memSize);
}

static const bt_data bt_le_ad_header_base = BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR));
int Bluetooth::init(){
    int ret;
    PRINTK_INFO("Initialization started");
    if(_bt_service_arr.size() == 0){ PRINTK_ERROR("No services connected"); return ps_configError; }
    _ad_param                 = (BT_LE_ADV_CONN_NAME[0]);
    _conn_callbacks           = {.connected        = cb_devConnected,         .disconnected    = cb_devDisconnected,};
    _auth_cb_display          = {.cancel           = cb_authenticationCancel, .pairing_confirm = cb_pairingConfirm, };
    _conn_auth_info_callbacks = {.pairing_complete = cb_pairingComplete,      .pairing_failed  = cb_pairingFailed,  };
    _gatt_callbacks           = {.att_mtu_updated  = cb_mtuUpdated                                                  };
    
    bt_conn_cb_register                    (&_conn_callbacks);
    ret = bt_conn_auth_cb_register         (&_auth_cb_display);
    if(ret){ PRINTKN_ERROR("Failed to register authorization callbacks", ret); return ps_enablingError; }
    if(IS_ENABLED(CONFIG_BT_SMP)){
        ret = bt_conn_auth_info_cb_register(&_conn_auth_info_callbacks);
        if(ret){ PRINTKN_ERROR("Failed to register authorization info callbacks", ret); return ps_enablingError; }
    }
    
    _bt_ad_arr.push_back(bt_le_ad_header_base);
    // for(size_t ix=0; ix < _bt_service_arr.size(); ix++){
    //     _bt_ad_arr.push_back(_bt_service_arr.at(ix)->_bt_le_ad_header_service);
    // }
    PRINTK_INFO("Successfully initialized");
    return ps_ok;
}

int Bluetooth::enable(){
    int ret = bt_enable(NULL);
    if(ret){ PRINTKN_ERROR("Failed to enable Bluetooth hardware", ret); return ps_enablingError; }
    return ps_ok;
}

int Bluetooth::startAdvertising(){
      int ret = bt_le_adv_start(&_ad_param, _bt_ad_arr.data(), _bt_ad_arr.size(), NULL, 0);
    if(ret){ PRINTKN_ERROR("Failed to start advertising cycle", ret); return ps_notReady; }
    PRINTK_INFO("Advertising successfully started");
    return ps_ok;
}

int Bluetooth::stopAdvertising(){
    bt_le_adv_stop();
    PRINTK_INFO("Advertising successfully stoped");
    return ps_ok;
}





//<< BLUETOOTH : CALLBACKS : >>
void Bluetooth::cb_devConnected(struct bt_conn *conn, uint8_t err){
    if(err) {PRINTKN_INFO("New device connection failed", err);} 
    else{
        PRINTKN_INFO("New device connection", 0);
        bt_conn_info info_tmp;
        bt_conn_get_info(conn, &info_tmp);
        //printk("pconn->state: %d\n",(uint8_t)info_tmp.state);
        if((uint8_t)info_tmp.state == 2){
            //stopAdvertising();
        }
    } 
}

void Bluetooth::cb_devDisconnected(struct bt_conn *conn, uint8_t reason){
    PRINTKN_INFO("Device disconnected by reason", reason);
    //startAdvertising();
}

void Bluetooth::cb_authenticationCancel(struct bt_conn *conn){
    char addr[BT_ADDR_LE_STR_LEN];
    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
    PRINTKS_INFO("Pairing cancelled address", addr);
}

void Bluetooth::cb_pairingComplete(bt_conn *conn, bool bonded){
    PRINTK_INFO("Pairing complete");
}

void Bluetooth::cb_pairingFailed(bt_conn *conn, bt_security_err reason){
    PRINTK_INFO("Pairing filed");
}

void Bluetooth::cb_pairingConfirm(bt_conn *conn){
    PRINTK_INFO("Pairing confirmation");
    bt_conn_auth_pairing_confirm(conn);

    // bt_conn_info info_tmp;
    // bt_conn_get_info(conn, &info_tmp);

    // #define INTERVAL_MIN    0x50     /* 80 units,  100 ms */
    // #define INTERVAL_MAX    0x50     /* 80 units,  100 ms */
    // const bt_le_conn_param param = BT_LE_CONN_PARAM(INTERVAL_MIN, INTERVAL_MAX, 0, 400)[0];
    // bt_le_set_auto_conn(info_tmp.le.remote, &param);
}

void Bluetooth::cb_mtuUpdated(bt_conn *conn, uint16_t tx, uint16_t rx){
    printk("Updated MTU: TX: %d RX: %d bytes\n", tx, rx);
}
//<< BLUETOOTH : CALLBACKS / >>