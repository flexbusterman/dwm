/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Px437 IBM BIOS:size=7:antialias=true:autohint=true"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

static Key keys[] = {
	/* modifier                     	key						function        argument */

	//  ____            _       _       
	// / ___|  ___ _ __(_)_ __ | |_ ___ 
	// \___ \ / __| '__| | '_ \| __/ __|
	//  ___) | (__| |  | | |_) | |_\__ \
	// |____/ \___|_|  |_| .__/ \__|___/
	//                   |_|            
	// bindings to run scripts
	
	{ MODKEY|ShiftMask,								XK_r,					spawn,          SHCMD("alacritty -e dwmrebuild" ) },
	{ MODKEY|ShiftMask|ControlMask,		XK_l,					spawn,					SHCMD("slock" ) },
	{ MODKEY,                       	XK_d,					spawn,					SHCMD("sleep 0.2 && xdotool type --clearmodifiers \"$(date +\"%F \")\"")},
	{ MODKEY,                       	XK_b,					spawn,					SHCMD("bluetoothconnect 74:5C:4B:D2:86:F7")},
	{ MODKEY|ShiftMask,								XK_b,					spawn,					SHCMD("bluetoothctl disconnect 74:5C:4B:D2:86:F7")},
	{ MODKEY,													XK_f,					togglefullscr,  {0} },
  { 0,															XK_Print,			spawn,					SHCMD("maim -f jpg -m 9 \"/home/flex/Pictures/SCREENSHOTS/$(date +\"%F %H_%M_%S.jpg\")\"")},
  { ShiftMask,											XK_Print,			spawn,					SHCMD("maim -f jpg -m 9 -s \"/home/flex/Pictures/SCREENSHOTS/$(date +\"%F %H_%M_%S.jpg\")\"")},
	{ MODKEY,													XK_grave,			spawn,					SHCMD("dmenuunicode") },
	{ MODKEY,													XK_m,					spawn,					SHCMD("mullvadconnect") },
	{ MODKEY|ShiftMask,								XK_m,					spawn,					SHCMD("mullvaddisconnect") },
	{ MODKEY|ShiftMask|ControlMask,		XK_m,					spawn,					SHCMD("mailsync") },
	{ MODKEY,													XK_F1,				spawn,					SHCMD("jackrun") },
	{ MODKEY,													XK_F2,				spawn,					SHCMD("jackkill") },
	{ MODKEY,													XK_F3,				spawn,					SHCMD("displayselect") },
	{ MODKEY,													XK_F7,				spawn,					SHCMD("td-toggle") },
	{ MODKEY,													XK_F8,				spawn,					SHCMD("dmenumount") },
	{ MODKEY,													XK_F9,				spawn,					SHCMD("dmenuumount") },
	{ 0,						XF86XK_AudioMute,								spawn,			    SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioRaiseVolume,				spawn,			    SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioLowerVolume,				spawn,			    SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioMicMute,						spawn,			    SHCMD("amixer set Capture toggle") },
	{ 0,						XF86XK_MonBrightnessUp,					spawn,			    SHCMD("xbacklight -inc $(bc <<< \"$(xbacklight) * 0.5 + 0.15\")") },
	{ 0,						XF86XK_MonBrightnessDown,				spawn,			    SHCMD("xbacklight -dec $(bc <<< \"$(xbacklight) * 0.5\")") },
	{ MODKEY|ShiftMask|ControlMask,		XK_r,					spawn,					SHCMD("reboot")},
	{ MODKEY|ShiftMask|ControlMask,		XK_p,					spawn,					SHCMD("poweroff")},
	{ MODKEY,													XK_semicolon,	spawn,					SHCMD("stream")},
	{ MODKEY,													XK_p,					spawn,					SHCMD("stack -p")},
	{ MODKEY,													XK_y,					spawn,					SHCMD("stack -y")},
	{ MODKEY|ShiftMask,								XK_p,					spawn,					SHCMD("passmenu")},
	{ MODKEY,													XK_Up,				spawn,					SHCMD("cpuperformance")},
	{ MODKEY,													XK_Down,			spawn,					SHCMD("cpupowersave")},
	{ ControlMask|ShiftMask,					XK_j,					spawn,					SHCMD("musicnext")},
	{ ControlMask|ShiftMask,					XK_k,					spawn,					SHCMD("musicprev")},
	{ ControlMask|ShiftMask,					XK_h,					spawn,					SHCMD("musicseekbackward")},
	{ ControlMask|ShiftMask,					XK_l,					spawn,					SHCMD("musicseekforward")},
	{ ControlMask|ShiftMask,					XK_space,			spawn,					SHCMD("musicplaypause")},
	
	//  _____ _   _ ___ 
	// |_   _| | | |_ _|
	//   | | | | | || | 
	//   | | | |_| || | 
	//   |_|  \___/|___|
	//                  
	// terminal applications

	{ MODKEY|ShiftMask,             	XK_comma,			spawn,          SHCMD("alacritty -t Vifm -e vifmrun" ) },
	{ MODKEY,													XK_e,					spawn,					SHCMD("alacritty -t NeoMutt -e neomutt") },
	{ MODKEY,													XK_t,					spawn,					SHCMD("alacritty -t Htop -e htop") },
	{ MODKEY,													XK_n,					spawn,					SHCMD("cd ~/Dropbox/NOTES/; alacritty -t VimWiki -e nvim -c VimwikiIndex") },
	{ MODKEY|ShiftMask,								XK_n,					spawn,					SHCMD("cd ~/Dropbox/NOTES/; alacritty -t VimWiki -e nvim ~/Dropbox/NOTES/TODO.md") },
	{ MODKEY,													XK_r,					spawn,					SHCMD("alacritty -t Newsboat -e newsboat") },
	{ MODKEY,													XK_F4,				spawn,					SHCMD("alacritty -t PulseMixer -e pulsemixer") },
	{ MODKEY,													XK_F6,				spawn,					SHCMD("torwrap") },
	{ MODKEY|ShiftMask,								XK_e,					spawn,					SHCMD("cd ~/.local/src/dwm/; alacritty -t DWMconfig -e nvim config.def.h")},
	{ ControlMask|ShiftMask,				 	XK_Return,		spawn,					SHCMD("alacritty -t ncmpcpp -e ncmpcpp")},
	{ MODKEY|ControlMask|ShiftMask,		XK_Return,		spawn,					SHCMD("alacritty -t ncspot -e ncspot")},
	{ MODKEY,													XK_s,					spawn,					SHCMD("supercollider")},

	//   ____ _   _ ___ 
	//  / ___| | | |_ _|
	// | |  _| | | || | 
	// | |_| | |_| || | 
	//  \____|\___/|___|
	// 
	// gui applications

	{ MODKEY,													XK_q,					spawn,          SHCMD("qpwgraph" ) },
	{ MODKEY,             						XK_period,	  spawn,					SHCMD("qutebrowser" ) },
	{ MODKEY|ShiftMask,             	XK_period,	  spawn,					SHCMD("bravestart" ) },
	{ MODKEY|ShiftMask,								XK_x,					spawn,					SHCMD("xkill") },
	{ MODKEY|ShiftMask,								XK_F4,				spawn,					SHCMD("pavucontrol") },
	{ MODKEY|ControlMask,						 	XK_Return,		spawn,					SHCMD("audacious")},

	{ MODKEY,													XK_equal, 	  incnmaster,     {.i = +1 } },
	{ MODKEY,													XK_minus, 	  incnmaster,     {.i = -1 } },
	// { MODKEY,     XK_a,   togglegaps, {0} },
  { MODKEY|ControlMask,							XK_j,					focusmon,				{.i = -1 } },
	{ MODKEY|ControlMask,							XK_k,					focusmon,				{.i = +1 } },
	{ MODKEY|ControlMask,							XK_h,					tagmon,					{.i = -1 } },
	{ MODKEY|ControlMask,							XK_l,					tagmon,					{.i = +1 } },
	{ MODKEY|ShiftMask,								XK_j,					movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,								XK_k,					movestack,      {.i = -1 } },

//  ______        ____  __ 
// |  _ \ \      / /  \/  |
// | | | \ \ /\ / /| |\/| |
// | |_| |\ V  V / | |  | |
// |____/  \_/\_/  |_|  |_|
//                         
// dwm bindings

	{ MODKEY,                       XK_Return,	spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,	spawn,          {.v = termcmd } },
	// { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,				focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,				focusstack,     {.i = -1 } },
	// { MODKEY|ShiftMask,            	XK_h,				incnmaster,     {.i = +1 } },
	// { MODKEY|ShiftMask,            	XK_l,				incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,				setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,				setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,		zoom,           {0} },
	// { MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             					XK_w,				killclient,     {0} },
	{ MODKEY,                       XK_u,				setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_i,				setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_o,				setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,		togglefloating, {0} },
	{ MODKEY,                       XK_0,				view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,				tag,            {.ui = ~0 } },
	// { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	// { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,												0)
	TAGKEYS(                        XK_2,												1)
	TAGKEYS(                        XK_3,												2)
	TAGKEYS(                        XK_4,												3)
	TAGKEYS(                        XK_5,												4)
	TAGKEYS(                        XK_6,												5)
	TAGKEYS(                        XK_7,												6)
	TAGKEYS(                        XK_8,												7)
	TAGKEYS(                        XK_9,												8)
	{ MODKEY|ShiftMask,             XK_q,				quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

