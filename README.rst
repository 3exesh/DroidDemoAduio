.. _droid_demo_audio:

Droid Demo Audio
###################

Overview
********
A simple sample C++ I2S/Bluetooth demo project that can be used with nRF52840-DK 
board and play some raw audio via I2S on Bluetooth command.

Building and Running
********************

This kernel project outputs to the console.  It can be built and executed
on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: samples/droid_demo_audio
   :host-os: unix
   :board: nrf52840dk_nrf52840
   :goals: run
   :compact:

Sample Output
=============

.. code-block:: console

    Droid Demo Audio ARM

    <repeats endlessly>

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.
