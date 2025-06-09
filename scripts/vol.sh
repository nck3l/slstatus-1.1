#!/bin/bash

VOL="$(wpctl get-volume @DEFAULT_SINK@ | grep Volume | awk '{print(100 * $2)}')"
MUTE="$(wpctl get-volume @DEFAULT_SINK@ | grep Volume | awk '{print $3}')"

VOLICON=""
MUTEICON=""

if [ "$MUTE" = "[MUTED]" ]; then
	echo "$MUTEICON"
else
	echo "$VOL $VOLICON"
fi
