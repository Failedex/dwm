#!/bin/sh

# Import the colors
. "${HOME}/.cache/wal/colors.sh"

dmenu_cmd="dmenu_run -h 30 -nb '$color0' -nf '$color15' -sb '$color1' -sf '$color15'"

echo "$dmenu_cmd"

j4-dmenu-desktop --dmenu="$dmenu_cmd"
