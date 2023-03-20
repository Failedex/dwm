#!/bin/sh

# Display Resolution
xrandr --output Monitor-1 --mode 1920x1080 &

# compositor
# input settings
/usr/bin/setxkbmap -option caps:swapescape &
synclient TapButton1=1 &
synclient TapButton2=3 &
syndaemon -i 0.5 -d &

# Display Resolution
xrandr --output eDP1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output DP1 --mode 1440x900 --pos 1920x90 --rotate normal --output HDMI1 --off --output VIRTUAL1 --off

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
pulseaudio &

# dwmblocks
dwmblocks &

## if not found, launch a new one
if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then eval `dbus-launch --sh-syntax`; fi

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
