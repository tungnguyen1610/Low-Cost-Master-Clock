#! /bin/bash
config-pin p9.20 timer
echo "Succesfully config pin p9.20 to Timer 6"
g++ config_timer6.c -o config_timer6
echo "Compiled code succesfully"
