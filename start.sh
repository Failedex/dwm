#!/bin/sh

# Display Resolution
xrandr --output Monitor-1 --mode 1920x1080 &

# restarting dwm
csum=""
new_csum=$(sha1sum $(which dwm))
while true
do
    if [ "$csum" != "$new_csum" ]
    then
        csum=$new_csum
        dbus-run-session dwm
    else
        exit 0
    fi
    new_csum=$(shasum $(which dwm))
    sleep 0.5
done
