/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
// #include "/home/f/.cache/wal/colors-wal-dwm.h"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const          int swallowfloating = 1;
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int horizpadbar        = 10;        /* horizontal padding for statusbar */
static const int vertpadbar         = 12;        /* vertical padding for statusbar */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const char *fonts[]          = { "Iosevka Nerd Font:size=12" };
static const char dmenufont[]       = "Iosevka Nerd Font:size=10";
static const char col_gray1[]       = "#1e1e2e";
static const char col_gray2[]       = "#313244";
static const char col_text[]       = "#cdd6f4";
static const char col_gray4[]       = "#6c7086";
static const char col_red[]         = "#f38ba8";
static const char col_red2[]         = "#89b4fa";
static const char col_urgborder[]         = "#ff0000";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_text, col_gray1, col_gray1 },
	[SchemeSel]  = { col_text, col_gray2,  col_gray4  },
	[SchemeUrg]  = { col_text, col_gray2,  col_red  },
};


typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "spterm", NULL };
const char *spcmd2[] = {"alacritty", "--class", "spranger", "-e", "ranger", NULL };
const char *spcmd3[] = {"alacritty", "--class", "spncmpcpp", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"spncmpcpp",   spcmd3},
};

/* tagging */
static const char *tags[] = { "\u4e00", "\u4e8c", "\u4e09", "\u56db", "\u4e94"};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const char *tagsel[][2] = {
 	{ "#eba0ac", col_gray2 },
	{ "#fab387", col_gray2 },
	{ "#f9e2af", col_gray2 },
	{ "#a6e3a1", col_gray2 },
	{ "#94e2d5", col_gray2 },
// 	{ sel_fg, norm_bg },
// 	{ sel_fg, norm_bg },
// 	{ sel_fg, norm_bg },
// 	{ sel_fg, norm_bg },
// 	{ sel_fg, norm_bg },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,          0,          1,           -1 },
	{ "eww",      NULL,       NULL,       0,            1,          0,          1,           -1 },
	{ "Onboard",  NULL,       NULL,       0,            1,          0,          1,           -1 },
	{ "Tk",       NULL,       NULL,       0,            1,          0,          1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,          0,          0,           -1 },
	{ "Steam",    NULL,       NULL,       1 << 8,       1,          0,          1,           -1 },
	{ "floatst",  NULL,       NULL,       0,            1,          0,          0,           -1 },
	{ "Qalculate-gtk", NULL,  NULL,       0,            1,          0,          0,           -1 },
	{ "st",       NULL,       NULL,       0,            0,          1,          0,           -1 },
	{ "alacritty",NULL,       NULL,       0,            0,          1,          0,           -1 },
	{ "kitty",    NULL,       NULL,       0,            0,          1,          0,           -1 },
	{ "feh",      NULL,       NULL,       0,            1,          0,          0,           -1 },
	{ "mpv",      NULL,       NULL,       0,            1,          0,          0,           -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,		1,	        0,           -1 },
	{ NULL,		  "spranger",	NULL,		SPTAG(1),		1,		1,	        0,           -1 },
	{ NULL,		  "spncmpcpp",	NULL,		SPTAG(2),		1,		1,	        0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "/home/f/dwm-6.3/dmen.sh" };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *layoutmenu_cmd = "/home/f/dwm-6.3/layoutmenu.sh";

static const char *brightness_up[] = {"brightnessctl", "-e", "s", "+5000", NULL};
static const char *brightness_down[] = {"brightnessctl", "-e", "s", "5000-", NULL};
static const char *brightness_update[] = {"pkill", "-RTMIN+6", "dwmblocks", NULL};

static const char *volume_up[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL};
static const char *volume_down[] = {"pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL};
static const char *volume_mute[] = {"pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL};
static const char *volume_update[] = {"pkill", "-RTMIN+1", "dwmblocks", NULL};

static const char *player_toggle[] = {"playerctl", "play-pause", NULL};
static const char *player_next[] = {"playerctl", "next", NULL};
static const char *player_previous[] = {"playerctl", "previous", NULL};

static const char *lockscreen[] = {"i3lock", "-i", "/home/f/Pictures/wallpapers/minimalistic/dark-cat-rosewater.png", NULL};
static const char *locksleep[] = {"dm-tool", "lock", NULL};

static const char *rofi[] = {"rofi", "-show", "drun", NULL};
static const char *widgets[] = {"/home/f/.config/eww/meowidgets/scripts/launch", NULL};
static const char *sliderwidgets[] = {"/home/f/.config/eww/meowidgets/scripts/launch_sliders", NULL};
static const char *freebird[] = {"play", "/home/f/dwm-6.3/freebird.mp3", NULL};

static const char *flameshot[] = {"flameshot", "launcher", NULL};
static const char *flameshotgui[] = {"flameshot", "gui", NULL};

static const Launcher launchers[] = {
       /* command       name to display */
	{ widgets,         " " },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          SHCMD("st -c floatst -G $(slop)") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  defaultgaps,    {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[12]} },
	{ MODKEY,                       XK_bracketleft,      cyclelayout,      {.i = -1} },
	{ MODKEY,                       XK_bracketright,      cyclelayout,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,            			XK_s,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_e,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_n,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_q,      spawn,          SHCMD("qalculate-gtk") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
    {0,                XF86XK_MonBrightnessUp, spawn,          {.v = brightness_up} },
    {0,              XF86XK_MonBrightnessDown, spawn,          {.v = brightness_down} },
    {0,                XF86XK_MonBrightnessUp, spawn,          {.v = brightness_update} },
    {0,              XF86XK_MonBrightnessDown, spawn,          {.v = brightness_update} },
    {0,                      XF86XK_AudioMute, spawn,          {.v= volume_mute} },
    {0,               XF86XK_AudioLowerVolume, spawn,          {.v= volume_down} },
    {0,               XF86XK_AudioRaiseVolume, spawn,          {.v= volume_up} },
    {0,                      XF86XK_AudioMute, spawn,          {.v= volume_update} },
    {0,               XF86XK_AudioLowerVolume, spawn,          {.v= volume_update} },
    {0,               XF86XK_AudioRaiseVolume, spawn,          {.v= volume_update} },
    {0,                      XF86XK_AudioPlay, spawn,          {.v= player_toggle} },
    {0,                     XF86XK_AudioPause, spawn,          {.v= player_toggle} },
    {0,                      XF86XK_AudioNext, spawn,          {.v= player_next} },
    {0,                      XF86XK_AudioPrev, spawn,          {.v= player_previous} },
    {0,                            0x0000ff61, spawn,          {.v= flameshot} },
    {ShiftMask,                    0x0000ff61, spawn,          {.v= flameshotgui} },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v= lockscreen} },
	{ MODKEY|ControlMask,           XK_x,      spawn,          {.v= locksleep} },
	{ MODKEY,                       XK_d,      spawn,          {.v = rofi } },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("export CM_LAUNCHER=rofi && clipmenu") },
	{ MODKEY,                       XK_semicolon,      spawn,  {.v = widgets } },
	{ MODKEY|ShiftMask|ControlMask, XK_1,      spawn,          {.v = freebird } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        layoutmenu, {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = sliderwidgets } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

