/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:size=14" };
static const char dmenufont[]       = "Hack:size=14";
static const char col_white[]       = "#ffffff";
static const char col_gray[]        = "#111111";
static const char col_black[]       = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_black, col_black, col_gray },
	[SchemeSel]  = { col_black, col_black, col_white},
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
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile    }, /* first entry is default */
    { "TTT",	  bstack  },
	{ "[M]",      monocle },
	{ "><>",      NULL    }, /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,	KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "/home/ivan/.script/wm/dmenu", NULL };

#include<X11/XF86keysym.h>

static Key keys[] = {
	/* modifier         key                        function        argument */
	{ MODKEY,           XK_Return,                 spawn,          SHCMD("~/.script/wm/term") },
	{ MODKEY,           XK_g,                      spawn,          SHCMD("google-chrome-stable --profile-directory=Default") },
	{ MODKEY,           XK_c,                      spawn,          SHCMD("firefox") },
	{ MODKEY,           XK_n,                      spawn,          SHCMD("~/.script/wm/term -e ~/.script/vifmrun") },
	{ MODKEY,           XK_m,                      spawn,          SHCMD("~/.script/wm/term -e pmn") },
	{ MODKEY,           XK_p,                      spawn,          SHCMD("pavucontrol") },
	{ MODKEY,           XK_b,                      spawn,          SHCMD("blueberry") },
	{ MODKEY|ShiftMask, XK_Escape,                 spawn,          SHCMD("~/.script/system/suspend") },
	{ 0,                XF86XK_PowerOff,           spawn,          SHCMD("~/.script/system/suspend") },
	{ MODKEY,           XK_d,                      spawn,          SHCMD("~/.script/wm/dmenu") },
	{ MODKEY,           XK_a,                      spawn,          SHCMD("~/.script/wm/toggle-audio") },
	{ MODKEY,           XK_space,                  spawn,          SHCMD("~/.script/wm/toggle-layout") },
	{ 0,                XF86XK_AudioRaiseVolume,   spawn,          SHCMD("~/.script/wm/volume-up") },
	{ 0,                XF86XK_AudioLowerVolume,   spawn,          SHCMD("~/.script/wm/volume-down") },
	{ 0,                XF86XK_AudioMute,          spawn,          SHCMD("~/.script/wm/volume-mute") },
	{ 0,                XK_Print,                  spawn,          SHCMD("~/.script/wm/pscreen-full") },
	{ ShiftMask,        XK_Print,                  spawn,          SHCMD("~/.script/wm/pscreen-crop") },
	{ 0,                XF86XK_MonBrightnessUp,    spawn,          SHCMD("~/.script/wm/brightness-up") },
	{ 0,                XF86XK_MonBrightnessDown,  spawn,          SHCMD("~/.script/wm/brightness-down") },
	{ 0,                XF86XK_AudioPrev,		   spawn,          SHCMD("~/.script/wm/audio-prev") },
	{ 0,                XF86XK_AudioPlay,		   spawn,          SHCMD("~/.script/wm/audio-play") },
	{ 0,                XF86XK_AudioPause,  	   spawn,          SHCMD("~/.script/wm/audio-pause") },
	{ 0,                XF86XK_AudioNext,		   spawn,          SHCMD("~/.script/wm/audio-next") },
	{ MODKEY|ShiftMask, XK_a,                      spawn,          SHCMD("~/.script/audio a") },
	{ MODKEY|ShiftMask, XK_h,                      spawn,          SHCMD("~/.script/audio h") },

	{ MODKEY,           XK_k,                      focusstack,     {.i = +1 } },
	{ MODKEY,           XK_i,                      focusstack,     {.i = -1 } },
	{ MODKEY,           XK_semicolon,              focusstack,     {.i = 0  } },

	{ MODKEY|ShiftMask, XK_j,                      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask, XK_l,                      setmfact,       {.f = +0.05} },

	{ MODKEY,           XK_j,                      zoom,           {0} },
	{ MODKEY,           XK_l,                      zoom,           {0} },

	{ MODKEY,           XK_e,                      killclient,     {0} },
	{ MODKEY|ShiftMask, XK_e,                      quit,           {0} },

	{ MODKEY,           XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask, XK_t,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_f,                      setlayout,      {.v = &layouts[2]} },

	{ MODKEY,           XK_period,                 togglefloating, {0} },

	{ MODKEY,           XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,                 tagmon,         {.i = +1 } },

	TAGKEYS(            XK_1,                                      0)
	TAGKEYS(            XK_2,                                      1)
	TAGKEYS(            XK_3,                                      2)
	TAGKEYS(            XK_4,                                      3)
	TAGKEYS(            XK_5,                                      4)
	TAGKEYS(            XK_6,                                      5)
	TAGKEYS(            XK_7,                                      6)
	TAGKEYS(            XK_8,                                      7)
	TAGKEYS(            XK_9,                                      8)
	{ MODKEY,           XK_Escape,      		   view,           {.ui = 1 << 8} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};

