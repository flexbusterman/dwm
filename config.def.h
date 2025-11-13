/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[] = { "BigBlueTerm437 Nerd Font Mono:size=9:antialias=true" };
// static const char dmenufont[]       = "monospace:size=10";
static const char dmenufont[] = { "BigBlueTerm437 Nerd Font Mono:size=9:antialias=true" };
static const char col_black[]				= "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	// [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeNorm] = {col_gray3, col_gray1, col_black},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.58; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ WINKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ WINKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ WINKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ WINKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ WINKEY,                       XK_Return, spawn,          {.v = dmenucmd } },
	// { WINKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ WINKEY,                       XK_a,      togglebar,      {0} },
	{ WINKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ WINKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{WINKEY | ShiftMask, XK_j, movestack, {.i = +1}},
	{WINKEY | ShiftMask, XK_k, movestack, {.i = -1}},
	// { WINKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { WINKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{WINKEY, XK_equal, incnmaster, {.i = +1}},
	{WINKEY, XK_minus, incnmaster, {.i = -1}},
	{ WINKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ WINKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ WINKEY,                       XK_space, zoom,           {0} },
	// { WINKEY,                       XK_Tab,    view,           {0} },
	{ WINKEY,     					        XK_q,      killclient,     {0} },
	{ WINKEY,                       XK_u,      setlayout,      {.v = &layouts[0]} },
	{ WINKEY,                       XK_i,      setlayout,      {.v = &layouts[1]} },
	{WINKEY, XK_f, fullscreen, {0}},

	// { WINKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { WINKEY,                       XK_space,  setlayout,      {0} },
	{ WINKEY | ShiftMask,             XK_space,  togglefloating, {0} },
	{ WINKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ WINKEY | ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { ControlMask | ShiftMask, XK_k, focusmon, {.i = +1}},
    { ControlMask | ShiftMask, XK_j, focusmon, {.i = -1}},
    {WINKEY | ControlMask | ShiftMask, XK_k, tagmon, {.i = +1}},
    {WINKEY | ControlMask | ShiftMask, XK_j, tagmon, {.i = -1}},
    // {WINKEY | MODKEY, XK_k, focusmon, {.i = +1}},
    // {WINKEY | MODKEY, XK_j, focusmon, {.i = -1}},
    // {WINKEY | MODKEY | ShiftMask, XK_k, tagmon, {.i = +1}},
    // {WINKEY | MODKEY | ShiftMask, XK_j, tagmon, {.i = -1}},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// { WINKEY|ShiftMask,             XK_q,      quit,           {0} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         WINKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         WINKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         WINKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            WINKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            WINKEY,         Button3,        toggletag,      {0} },
};
