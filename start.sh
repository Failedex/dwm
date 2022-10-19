#!/bin/sh

# Keyboard Layout
/usr/bin/setxkbmap -option caps:swapescape &

# Display Resolution
xrandr --output Monitor-1 --mode 1920x1080 &

# compositor
picom &

# notifications
dunst &

# nm-applet
nm-applet --indicator &

# wallpaper
nitrogen --restore &

# dwmblocks
dwmblocks &

# low battery check
i3-battery-popup -L 21 -n -t 10s &

# Klipper
klipper &

# restarting dwm
csum=""
new_csum=$(sha1sum $(which dwm))
while true
do
    if [ "$csum" != "$new_csum" ]
    then
        csum=$new_csum
        dwm
    else
        exit 0
    fi
    new_csum=$(shasum $(which dwm))
    sleep 0.5
done

# Execute dwm
exec dwm
