#!/bin/sh

# input settings
/usr/bin/setxkbmap -option caps:swapescape &
xset r rate 500 50 &

# Display Resolution
xrandr --output eDP1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output DP1 --mode 1440x900 --pos 1920x90 --rotate normal --output HDMI1 --off --output VIRTUAL1 --off &

# map touch-screen to specific monitor
xinput map-to-output "ELAN900C:00 04F3:2C66" eDP1 &

# compositor
picom &

# notification
dunst &

# nm-applet
nm-applet -d &

# clipmenu
clipmenud &

# wallpaper
nitrogen --restore &
# wal -R


# low battery check
~/dwm-6.3/i3-battery-popup -L 15 -n -t 10s &

# stupid things
udiskie --automount --notify &
unclutter --hide-on-touch --timeout 10 &
while true; do state=$(xinput) && sleep 2 && [[ $state != $(xinput) ]] && setxkbmap -option caps:swapescape && xinput map-to-output "ELAN900C:00 04F3:2C66 Stylus Pen (0)" eDP1; done &
$HOME/.config/eww/meowidgets/scripts/timer.py loop &

# dwmblocks
dwmblocks &

## if not found, launch a new one
if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then eval `dbus-launch --sh-syntax`; fi
