/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 25;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 25;       /* vert inner gap between windows */
static const unsigned int gappoh    = 25;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 25;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "AcPlus IBM BIOS:size=9:antialias=true:autohint=true"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#dddddd";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan1[]       = "#005577";
static const char col_cyan2[]       = "#8be9fd";
static const char col_purple[]       = "#6272a4";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_black },
	[SchemeSel]  = { col_gray4, col_purple, col_purple },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       							tags mask     isfloating   monitor */
	// { "Gimp",     NULL,       NULL,    							   0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,    							   1 << 8,       0,           -1 },
	{ NULL,				NULL,       "Server",									1 << 8,       0,           -1 },
	{ NULL,				NULL,       "Timer",									1 << 8,       0,           -1 },
	{ NULL,				NULL,       "Notes",									1 << 1,       0,           -1 },
	{ NULL,				NULL,       "Git",										1 << 8,       0,           -1 },
	{ "REAPER",		"REAPER",   "Reaper Keys Feedback",		0,   			    0,           -1 },
	{ "mpv",			NULL,       NULL,											999999999,	  0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.58; /* factor of master area size [0.05..0.95] */
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
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
// static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x40", NULL };
static const char *scratchpadcmd[] = {"st", "-t", scratchpadname, "-g", "80x45", "-e", "nvim", "/home/flex/Dropbox/NOTES/TODO.md", NULL};

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

	{ MODKEY|ShiftMask,								XK_r,					spawn,          SHCMD("st -e dwmrebuild" ) },
	{ MODKEY|ShiftMask,								XK_equal,			spawn,          SHCMD("calc" ) },
	{ MODKEY|ShiftMask|ControlMask,		XK_l,					spawn,					SHCMD("slock" ) },
	{ MODKEY,                       	XK_d,					spawn,					SHCMD("sleep 0.2 && xdotool type --clearmodifiers \"$(date +\"%F \")\" && sleep 0.2 && xdotool keyup Alt_L Alt_R Control_L Control_R Shift_L Shift_R")},
	{ MODKEY,                       	XK_b,					spawn,					SHCMD("bluetoothconnect C8:7B:23:C8:34:32")},
	{ MODKEY|ShiftMask,								XK_b,					spawn,					SHCMD("bluetoothctl disconnect C8:7B:23:C8:34:32")},
	{ MODKEY|ShiftMask|ControlMask,		XK_b,					spawn,					SHCMD("pactl set-card-profile bluez_card.74_5C_4B_D2_86_F7 a2dp-sink")},
	{ MODKEY,													XK_f,					togglefullscr,  {0} },
  { 0,															XK_Print,			spawn,					SHCMD("maim -f jpg -m 9 \"/home/flex/Pictures/SCREENSHOTS/$(date +\"%F %H_%M_%S.jpg\")\"")},
  { ShiftMask,											XK_Print,			spawn,					SHCMD("maim -f jpg -m 9 -s \"/home/flex/Pictures/SCREENSHOTS/$(date +\"%F %H_%M_%S.jpg\")\"")},
	{ MODKEY,													XK_grave,			spawn,					SHCMD("dmenuunicode") },
	{ MODKEY,													XK_m,					spawn,					SHCMD("mullvadconnect") },
	{ MODKEY|ShiftMask,								XK_m,					spawn,					SHCMD("mullvaddisconnect") },
	{ MODKEY|ShiftMask|ControlMask,		XK_m,					spawn,					SHCMD("mailsync") },
	{ MODKEY,													XK_F1,				spawn,					SHCMD("jackrun") },
	{ MODKEY,													XK_F2,				spawn,					SHCMD("jackkill") },
	{ MODKEY,													XK_F3,				spawn,					SHCMD("displaydefault") },
	{ MODKEY|ShiftMask,								XK_F3,				spawn,					SHCMD("displayselect") },
	{ MODKEY,													XK_F7,				spawn,					SHCMD("td-toggle") },
	{ MODKEY,													XK_F8,				spawn,					SHCMD("dmenumount") },
	{ MODKEY,													XK_F9,				spawn,					SHCMD("dmenuumount") },
	{ 0,						XF86XK_AudioMute,								spawn,			    SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioRaiseVolume,				spawn,			    SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioLowerVolume,				spawn,			    SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ 0,						XF86XK_AudioMicMute,						spawn,			    SHCMD("amixer set Capture toggle") },
	{ 0,						XF86XK_MonBrightnessUp,					spawn,			    SHCMD("brightnessup") },
	{ 0,						XF86XK_MonBrightnessDown,				spawn,			    SHCMD("brightnessdown") },
	{ MODKEY|ShiftMask|ControlMask,		XK_r,					spawn,					SHCMD("reboot")},
	{ MODKEY|ShiftMask|ControlMask,		XK_p,					spawn,					SHCMD("poweroff")},
	{ MODKEY,													XK_semicolon,	spawn,					SHCMD("clipstream")},
	{ MODKEY|ShiftMask,								XK_semicolon,	spawn,					SHCMD("clipdownload")},
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
	{ MODKEY|ShiftMask,								XK_i,					spawn,					SHCMD("xcalib -i -a")},
	{ MODKEY,													XK_slash,			spawn,					SHCMD("st -e ~/.local/bin/fzfvim")},
	{ MODKEY|ShiftMask,								XK_slash,			spawn,					SHCMD("st -e vimshortcuts")},
	{ MODKEY|ShiftMask,								XK_d,					spawn,					SHCMD("cd ~/.local/src/; dev $(ls -d */ | dmenu)")},
	// { MODKEY,													XK_x,					spawn,					SHCMD("xcape -e 'Mode_switch=Escape'")},
	{ MODKEY,													XK_o,					spawn,					SHCMD("ytfzf -D")},
	{ MODKEY|ShiftMask,								XK_o,					spawn,					SHCMD("ytfzf -dD -P ~/Downloads/VIDEO/")},
	{ MODKEY|ShiftMask|ControlMask,		XK_m,					spawn,					SHCMD("touchpadtoggle")},
	{ ControlMask,										XK_semicolon,	spawn,					SHCMD("xm")},

	//  _____ _   _ ___ 
	// |_   _| | | |_ _|
	//   | | | | | || | 
	//   | | | |_| || | 
	//   |_|  \___/|___|
	//                  
	// terminal applications

	{ MODKEY|ShiftMask,             	XK_comma,			spawn,          SHCMD("st -t Vifm -e vifmrun" ) },
	{ MODKEY,													XK_e,					spawn,					SHCMD("st -t NeoMutt -e neomutt; mailcheck") },
	{ MODKEY|ShiftMask,								XK_c,					spawn,          SHCMD("st -t Calcurse -e calcurse; calendar" ) },
	{ MODKEY|ShiftMask,								XK_t,					spawn,					SHCMD("st -t typingtest -e tt -theme dracula") },
	{ MODKEY,													XK_t,					spawn,					SHCMD("st -t Htop -e htop") },
	{ MODKEY,													XK_n,					spawn,					SHCMD("cd ~/Dropbox/NOTES/; st -t TODO -e nvim ~/Dropbox/NOTES/TODO.md") },
	{ MODKEY|ShiftMask,								XK_n,					spawn,					SHCMD("cd ~/Dropbox/NOTES/; st -t VimWiki -e nvim -c VimwikiIndex") },
	{ MODKEY|ControlMask|ShiftMask,		XK_n,					spawn,					SHCMD("st -t Newsboat -e newsboat") },
	{ MODKEY,													XK_F4,				spawn,					SHCMD("st -t PulseMixer -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,													XK_F6,				spawn,					SHCMD("torwrap") },
	{ MODKEY|ShiftMask,								XK_e,					spawn,					SHCMD("cd ~/.local/src/dwm/; st -t DWMconfig -e nvim config.def.h")},
	{ ControlMask|ShiftMask,				 	XK_Return,		spawn,					SHCMD("st -t ncmpcpp -e ncmpcpp")},
	{ MODKEY|ControlMask|ShiftMask,		XK_Return,		spawn,					SHCMD("st -t ncspot -e ncspot")},
	{ MODKEY,													XK_s,					spawn,					SHCMD("st -t SuperCollider -e supercollider")},

	//   ____ _   _ ___ 
	//  / ___| | | |_ _|
	// | |  _| | | || | 
	// | |_| | |_| || | 
	//  \____|\___/|___|
	// 
	// gui applications

	{ MODKEY,													XK_q,					spawn,          SHCMD("qpwgraph" ) },
	{ MODKEY|ShiftMask,             	XK_period,	  spawn,					SHCMD("qutebrowser -R" ) },
	{ MODKEY|ShiftMask|ControlMask,  	XK_period,	  spawn,					SHCMD("bravestart" ) },
	{ MODKEY|ShiftMask,								XK_x,					spawn,					SHCMD("xkill") },
	{ MODKEY|ShiftMask,								XK_F4,				spawn,					SHCMD("pavucontrol") },
	{ MODKEY|ControlMask,						 	XK_Return,		spawn,					SHCMD("audacious")},
	{ MODKEY,													XK_r,					spawn,					SHCMD("reaper") },

//  ______        ____  __ 
// |  _ \ \      / /  \/  |
// | | | \ \ /\ / /| |\/| |
// | |_| |\ V  V / | |  | |
// |____/  \_/\_/  |_|  |_|
//                         
// dwm bindings

	{ MODKEY,													XK_equal, 	  incnmaster,     {.i = +1 } },
	{ MODKEY,													XK_minus, 	  incnmaster,     {.i = -1 } },
  { MODKEY|ControlMask,							XK_k,					focusmon,				{.i = -1 } },
	{ MODKEY|ControlMask,							XK_j,					focusmon,				{.i = +1 } },
	{ MODKEY|ShiftMask|ControlMask,		XK_k,					tagmon,					{.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask,		XK_j,					tagmon,					{.i = +1 } },
	{ MODKEY|ShiftMask,								XK_j,					movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,								XK_k,					movestack,      {.i = -1 } },
	{ MODKEY,               	        XK_Return,		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,     	        XK_Return,		spawn,          {.v = termcmd } },
	// { MODKEY,							  	        XK_n,				  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,               	        XK_a,    		  togglebar,      {0} },
	{ MODKEY,               	        XK_z,    		  togglebar,      {0} },
	{ MODKEY,            						  XK_a,    		  togglegaps,     {0} },
	{ MODKEY,            						  XK_g,    		  togglegaps,     {0} },
	{ MODKEY|ShiftMask,  	  					XK_a,					defaultgaps,    {0} },
	{ MODKEY,               	        XK_j,					focusstack,     {.i = +1 } },
	{ MODKEY,               	        XK_k,					focusstack,     {.i = -1 } },
	// { MODKEY|ShiftMask,  	         	XK_h,					incnmaster,     {.i = +1 } },
	// { MODKEY|ShiftMask,  	         	XK_l,					incnmaster,     {.i = -1 } },
	{ MODKEY,               	        XK_h,					setmfact,       {.f = -0.05} },
	{ MODKEY,               	        XK_l,					setmfact,       {.f = +0.05} },
	{ MODKEY,               	        XK_space,			zoom,           {0} },
	// { MODKEY|Mod4Mask,             	 XK_u,  	    incrgaps,       {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_u,  	    incrgaps,       {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 XK_i,  	    incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_i,  	    incrigaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 	XK_o,  	    incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_o,  	    incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 XK_6,  	    incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_6,  	    incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 XK_7,  	    incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_7,  	    incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 XK_8,  	    incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_8,  	    incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,             	 XK_9,  	    incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,   	 XK_9,  	    incrovgaps,     {.i = -1 } },
	// { MODKEY,                      	 XK_Tab,	    view,           {0} },
	{ MODKEY,             						XK_w,					killclient,     {0} },
	{ MODKEY,                 	      XK_u,					setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                 	      XK_i,					setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,        	      XK_u,					setlayout,      {.v = &layouts[2]} },
	// { MODKEY,               	        XK_space	,  setlayout,      {0} },
	{ MODKEY|ShiftMask,       	      XK_space,			togglefloating, {0} },
	{ MODKEY,                 	      XK_0,					view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,       	      XK_0,					tag,            {.ui = ~0 } },
	// { MODKEY,              	         XK_comma,  focusmon,       {.i = -1 } },
	// { MODKEY,              	         XK_period, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,    	         XK_comma,  tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,    	         XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                  	      XK_1,												0)
	TAGKEYS(                  	      XK_2,												1)
	TAGKEYS(                  	      XK_3,												2)
	TAGKEYS(                  	      XK_4,												3)
	TAGKEYS(                  	      XK_5,												4)
	TAGKEYS(                  	      XK_6,												5)
	TAGKEYS(                  	      XK_7,												6)
	TAGKEYS(                  	      XK_8,												7)
	TAGKEYS(                  	      XK_9,												8)
	// { MODKEY|ShiftMask,       	      XK_q,				quit,           {0} },
	{ MODKEY|ShiftMask,								XK_q,				spawn,					SHCMD("killall dwmstart") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

