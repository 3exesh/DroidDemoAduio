/**
 ******************************************************************************
 * @file           : main.cpp
 * @brief          : Main program body
 * @author         : Datsii Vladisalav
 * @date           :
 ******************************************************************************
 * @attention
 *
 *  Droid Demo Adudio - nRF52840DK
 *
 ******************************************************************************
 */
#include <zephyr/settings/settings.h>
#include <zephyr/kernel.h>

#include "Llib/periphery/bluetooth/Bluetooth.hpp"
#include "Llib/periphery/i2s/I2s.hpp"
#include "Llib/primitives/audio/Player.hpp"

#include "PlayerControlService.hpp"

#include "sounds/sound_list.hpp"

//<< THREADS : >>
L_THREAD_DEFINE(aduioPlayer_th, 1024, 1, 0, 0);
//<< THREADS / >>

//<< I2S : >>
K_MEM_SLAB_DEFINE_STATIC(i2s_tx_mem_slab, 1024*2*1, 16, 2); // buff*wordWidth*chan
//<< I2S / >>

//<< BLUETOOTH : >>
#define BT_SERVICES_MAXNUM 1
#define BT_ADVERTISINGS_MAXNUM BT_SERVICES_MAXNUM + 1
BluetoothService *btServicesMemory_p[BT_SERVICES_MAXNUM];
bt_data btAdvertisingsMemory_p[BT_ADVERTISINGS_MAXNUM];
//<< BLUETOOTH / >>

int main()
{
    //<< PRESTART : >>

    //<< I2S : >>
    I2s i2s;
    i2s.set(DEVICE_DT_GET(DT_NODELABEL(i2s_rxtx)));
    i2s.setOut(i2s_tx_mem_slab);

    //<< PLAYER : >>
    Player player;
    player.set(aduioPlayer_th);
    player.connect(i2s);

    //<< BLUETOOTH : >>
    Bluetooth::set(btServicesMemory_p, BT_SERVICES_MAXNUM);
    Bluetooth::set(btAdvertisingsMemory_p, BT_ADVERTISINGS_MAXNUM);

    //<< BLUETOOTH : SERVICES : >>
    PlayerControlService PlayerControl_btServ;
    Bluetooth::connect(PlayerControl_btServ);
    PlayerControl_btServ.connect(player);

    //<< INITIALIZATION : >>
    i2s.initOut();
    player.init();
    PlayerControl_btServ.init();
    Bluetooth::init();

    Bluetooth::enable();
    if (IS_ENABLED(CONFIG_SETTINGS)) settings_load();
    Bluetooth::startAdvertising();

    // k_msleep(100);

    // player.soud(sound_OE_Obiymy_8k_st);
    // player.play();

    // while (player.isPlay()) k_msleep(700);

    // player.soud(sound_HARDKISS_ZHiva_16k_st);
    // player.play();

    while (1)
    { // main() have the moust high priority!
        k_msleep(1000);
        __ASM("NOP");
    }
}
