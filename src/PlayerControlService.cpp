#include "PlayerControlService.hpp"

#include "sounds/sound_list.hpp"


#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include "Llib/common/log/log.hpp"
#include "Llib/periphery/periphery.hpp"


static const char* printkx_title_str = "PlayerControlService";

//<< BASE STRUCT : DECLARATION : >>
#define BT_UUID_CUSTOM_SERVICE_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0)
#define BT_UUID_ENC_SERVICE_VAL    BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1)
static bt_data     bt_le_ad_header_service    = BT_DATA_BYTES    (BT_DATA_UUID128_ALL, BT_UUID_CUSTOM_SERVICE_VAL);
static bt_uuid_128 bt_lep_prim_service_uuid   = BT_UUID_INIT_128 (BT_UUID_CUSTOM_SERVICE_VAL);
static bt_uuid_128 bt_le_vnd_enc_charact_uuid = BT_UUID_INIT_128 (BT_UUID_ENC_SERVICE_VAL);
//<< BASE STRUCT : DECLARATION / >>


//<< SERVICE : DECLARATION : >>
static bt_gatt_attr playerCtrl_attrs[] = {
        BT_GATT_PRIMARY_SERVICE(&bt_lep_prim_service_uuid),
             BT_GATT_CHARACTERISTIC(&bt_le_vnd_enc_charact_uuid.uuid,
                                   BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                                   BT_GATT_PERM_WRITE, NULL,
                                   NULL, NULL),
};

static bt_gatt_service playerCtrl_svc = BT_GATT_SERVICE(playerCtrl_attrs);
//<< SERVICE : DECLARATION / >>


int PlayerControlService::init(){
    if(_player == NULL){ PRINTKN_ERROR("Player object is not connected", ret); return ps_configError; }
    int ret                                = bt_gatt_service_register(&playerCtrl_svc);
    if(ret){ PRINTKN_ERROR("Failed to create service", ret); return ps_configError; }
    _bt_le_ad_header_service               = bt_le_ad_header_service;
    bt_gatt_attr *vnd_ind_attrvnd_ind_attr = bt_gatt_find_by_uuid(playerCtrl_svc.attrs, playerCtrl_svc.attr_count, &bt_le_vnd_enc_charact_uuid.uuid);
    vnd_ind_attrvnd_ind_attr->write        = get_cmd;
    _tmp_p                                 = this;
    return ps_ok;
}

ssize_t PlayerControlService::get_cmd(bt_conn *conn, const bt_gatt_attr *attr,
                                      const void *buf, uint16_t len, 
                                      uint16_t offset, uint8_t flags){
    if(offset + len > 1) return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);

    printk("[Command] len    : %d\n",len);
    printk("[Command] offset : %d\n",offset);
    printk("[Command] value  : %d\n",*((uint8_t*)buf));

    switch (*((uint8_t*)buf))
    {
        case 1:
            if(_tmp_p->_player->isPlay()) break;
            _tmp_p->_player->soud(sound_OE_Obiymy_8k_st);
            _tmp_p->_player->play();
            break;
        case 2:
            if(_tmp_p->_player->isPlay()) break;
            _tmp_p->_player->soud(sound_HARDKISS_ZHiva_16k_st);
            //_tmp_p->_player->soud(sound_MIW_Masterpice_16k_st);
            _tmp_p->_player->play();
            break;
        case 3:
            _tmp_p->_player->stop();
            break;
        default:
            break;
    }
    return len;
}
