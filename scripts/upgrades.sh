#!/bin/sh

updates=$(pacman -Qu | grep -Fcv "[ignored]" | sed "s/^//;s/^0$//g")
    echo "$updates "
