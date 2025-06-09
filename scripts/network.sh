#!/bin/bash
# icons depend on nerdfonts being installed
network() {
wire="$(ip a | grep eth0 | grep inet | wc -l)"
wifi="$(ip a | grep wlan | grep inet | wc -l)"

if [ $wire = 1 ]; then
    echo "  "
elif [ $wifi = 1 ]; then
    echo " $(nmcli dev wifi | grep '*' | grep Infra | awk '{print $8}')"
else
    echo " "
fi
}

vpn() {
#state="$(cat /sys/class/net/ton0/operstate)"

if [ $(cat /sys/class/net/ton0/operstate) = 'unknown' ]; then
    echo ""
else
    echo " "
fi
}

echo "$(network) $(vpn)"
