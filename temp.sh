#!/bin/bash
# xdotool move mouse to bottom right corner, getting the screen resolution
xdotool mousemove $(xdotool getdisplaygeometry | awk '{print $1-1, $2-1}')
