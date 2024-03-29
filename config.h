/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx        = 5;			/* border pixel of windows */
static unsigned int snap				= 32;       	/* snap pixel */
static const unsigned int systraypinning = 0;   	/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   	/* systray spacing */
static const int systraypinningfailfirst = 1;   	/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;			/* 0 means no systray */
static const int swallowfloating    = 0;			/* 1 means swallow floating windows by default */
static const unsigned int gappih    = 15;			/* horiz inner gap between windows */
static const unsigned int gappiv    = 15;        	/* vert inner gap between windows */
static const unsigned int gappoh    = 15;        	/* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;        	/* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;			/* 1 means no outer gap when there is only one window */
static int showbar                  = 1;        	/* 0 means no bar */
static int topbar                   = 1;        	/* 0 means bottom bar */
static const char *fonts[]          = { "Deja Vu Sans Mono:size=10", "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Deja Vu Sans Mono:size=10";
#define BLACK "#1d2021"
#define AQUA "#689d6a"
#define GREEN "#98971a"
static char normbgcolor[]           = BLACK;
static char normfgcolor[]           = "#fbf1c7";
static char normbordercolor[]       = BLACK;
static char selbgcolor[]            = AQUA;
static char selfgcolor[]            = BLACK;
static char selbordercolor[]        = AQUA;
static char col_urgborder[]         = "#fb4934";
static char *colors[][3]      = {
	/*               fg             bg              border   */
	[SchemeNorm] = { normfgcolor,   normbgcolor,    normbordercolor },
	[SchemeSel]  = { selfgcolor,    selbgcolor,     selbordercolor  },
	[SchemeUrg]  = { col_urgborder, col_urgborder,  col_urgborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	*	WM_CLASS(STRING) = instance, class
    *	WM_NAME(STRING) = title
	*/
    /* class                instance          title                             tags mask     isfloating    isterminal  noswallow   monitor */
    // tag assignments:
    { "Brave-browser",      NULL,             NULL,                             1,            0,            0,          0,          -1 },
    { "St",                 "initterm",       NULL,                             1 << 1,       0,            1,          0,          -1 },
    { "St",                 NULL,             NULL,                             0,            0,            1,          0,          -1 },
    { "St",                 "irssi",          NULL,                             1 << 2,       0,            1,          0,          -1 },
    { "discord",            NULL,             NULL,                             1 << 2,       0,            0,          0,          -1 },
    { "zoom",               NULL,             NULL,                             1 << 6,       0,            0,          0,          -1 },
    { "Steam",              NULL,             NULL,                             1 << 7,       0,            0,          0,          -1 },
    { "minecraft-launcher", NULL,             NULL,                             1 << 7,       0,            0,          0,          -1 },
    /* { "spotify-tui",        NULL,             NULL,                             1 << 8,       0,            0,          0,          -1 }, */
    { NULL,                 NULL,             "Event Tester",                   0,            1,            0,          1,          -1 },
    // floating assingments:
    { "St",					"weatherreport",  NULL,                             0,            1,            0,          0,          -1 },
    { "St",					"mail",			  NULL,                             0,            1,            0,          0,          -1 },
    { "St",					"abook",		  NULL,                             0,            1,            0,          0,          -1 },
    { NULL,                 NULL,             "Friends List",                   0,            1,            0,          0,          -1 },
    { NULL,                 NULL,             "Steam - News",                   0,            1,            0,          0,          -1 },
    { NULL,                 NULL,             "Discord Updater",                0,            1,            0,          0,          -1 },
    { "St",					"pulsemixer",     NULL,                             0,            1,            0,          0,          -1 },
    { "St",					"music",          NULL,                             0,            1,            0,          0,          -1 },
    { NULL,					NULL,             "cellphone",                      0,            1,            0,          0,          -1 },
    { NULL,					"Godot_Engine",	  NULL,								0,            1,            0,          0,          -1 },

};

/* layout(s) */
static float mfact     = 0.49; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
    { MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
  /* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
  { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
  { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
  { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
  { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands for opening certain programs */
#define PULSE SHCMD("st -n pulsemixer -g =110x27+56+64 -e pulsemixer")
#define WEATH SHCMD("st -n weatherreport -g =130x41+56+64 -e less -S .local/share/weatherreport")
#define MAIL SHCMD("st -n mail -g =207x54+135-68 -e neomutt; pkill -RTMIN+2 dwmblocks; rmdir ~/.abook")
#define ABOOK SHCMD("st -n abook -g '=207x54+135-68' -e abook -C ~/.config/abook/abookrc --datafile ~/.local/share/abook/addressbook; rmdir ~/.abook")
#define MUSIC SHCMD("st -n music -g '=176x46+242+132' -e ncmpcpp")

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
// center dmenu command (comment top one, uncomment bottom one)
// static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "15", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",          	INTEGER, &borderpx },
	{ "snap",          		INTEGER, &snap },
	{ "showbar",          	INTEGER, &showbar },
	{ "topbar",          	INTEGER, &topbar },
	{ "nmaster",          	INTEGER, &nmaster },
	{ "resizehints",       	INTEGER, &resizehints },
	{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
#include "selfrestart.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },

    { MODKEY,						XK_masculine,	spawn,      SHCMD("dmenuunicode") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    // { MODKEY|ShiftMask,             XK_BackSpace,	quit,         {0} },
	{ MODKEY|ShiftMask,             XK_BackSpace,	self_restart,         {0} },
	{ MODKEY|Mod1Mask,				XK_BackSpace,	quit,				  {0} },

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,			killclient,     {0} },
    // { MODKEY|ShiftMask,             XK_q,      spawn,           SHCMD("") },
    { MODKEY,                       XK_w,       spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,       spawn,          WEATH },
	// { MODKEY,                       XK_e,       spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("") },
    { MODKEY,                       XK_r,		spawn,          SHCMD("st -e lf") },
    // { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_t,       spawn,			SHCMD("") },
    // { MODKEY|ShiftMask,             XK_t,       spawn,      	SHCMD("") },
    { MODKEY,                       XK_y,       spawn,          SHCMD("telegram-desktop") },
    { MODKEY|ShiftMask,             XK_y,       spawn,          SHCMD("discord") },
	// { MODKEY,                       XK_u,      spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") },
    { MODKEY,                       XK_i,       spawn,          SHCMD("st -e htop") },
    // { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("") },
    // { MODKEY,                       XK_o,       spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_u,      spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") },
    { MODKEY,                       XK_p,       spawn,          SHCMD("mpc toggle") },
    // { MODKEY|ShiftMask,             XK_p,       spawn,          SHCMD("$PLAYER") },
	// { MODKEY,                       XK_a,      spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("") },
    { MODKEY,                       XK_s,       togglesticky,   {0} },
    { MODKEY|Mod1Mask,              XK_s,       togglegaps,     {0} },
    { MODKEY|ShiftMask|Mod1Mask,    XK_s,       defaultgaps,    {0} },
	{ MODKEY,                       XK_d,       spawn,          {.v = dmenucmd } },
    /* { MODKEY|ShiftMask,             XK_d,       spawn,          SHCMD("") }, */
    { MODKEY,                       XK_f,       togglefullscr,  {0} },
    // { MODKEY|ShiftMask,             XK_f,       spawn,			SHCMD("") },
    { MODKEY,                       XK_g,       togglescratch,  {.v = scratchpadcmd } },
    // { MODKEY|ShiftMask,             XK_g,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_h,       incnmaster,     {.i = +1} },
    { MODKEY|Mod1Mask,              XK_h,       incrigaps,      {.i = +5} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_h,       incrogaps,      {.i = +5} },
    /* !!! J and K are bound up in the STACKKEYS macro !!! */
    STACKKEYS(MODKEY,                           focus)
    STACKKEYS(MODKEY|ShiftMask,                 push)
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,       incnmaster,      {.i = -1} },
    { MODKEY|Mod1Mask,              XK_l,       incrigaps,      {.i = -5} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_l,       incrogaps,      {.i = -5} },
    { MODKEY,                       XK_z,       spawn,          SHCMD("zathura") },
    // { MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("") },
    { MODKEY,                       XK_x,       spawn,          SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    // { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("") },
	{ MODKEY,                      XK_c,       spawn,          SHCMD("clipmenu") },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("passmenu") },
	{ MODKEY,                       XK_v,      spawn,           PULSE },
	// { MODKEY|ShiftMask,             XK_v,       spawn,          SHCMD("") },
	{ MODKEY,                       XK_b,       togglebar,      {0} },
    // { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_n,      spawn,          MUSIC },
    // { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_m,       spawn,          MAIL },
    { MODKEY|ShiftMask,             XK_m,       spawn,          ABOOK },
	{ MODKEY,						XK_comma,	spawn,		SHCMD("mpc seek 0%") },
	{ MODKEY|ShiftMask,				XK_comma,	spawn,		SHCMD("mpc prev") },
	{ MODKEY,						XK_period,	spawn,		SHCMD("mpc next") },
	{ MODKEY|ShiftMask,				XK_period,	spawn,		SHCMD("mpc repeat") },
	// { MODKEY,						XK_minus,	spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_minus,	spawn,		SHCMD("") },

	{ 0,                            XK_Print,		spawn,      SHCMD("maimsel") },
	{ ShiftMask,                    XK_Print,   	spawn,      SHCMD("maimfull") },
	{ MODKEY,                       XK_Print,		spawn,      SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,             XK_Print,   	spawn,      SHCMD("dmenurecord kill") },
	// { MODKEY,						XK_Scroll_Lock,	spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Scroll_Lock,	spawn,		SHCMD("") },
	// { MODKEY,						XK_Pause,		spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Pause,		spawn,		SHCMD("") },
	// { MODKEY,						XK_Insert,		spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Insert,		spawn,		SHCMD("") },
	// { MODKEY,						XK_Home,		spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Home,		spawn,		SHCMD("") },
	// { MODKEY,						XK_Prior,		spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Prior,		spawn,		SHCMD("") },
	{ MODKEY,						XK_Delete,		spawn,		SHCMD("sysact") },
	{ MODKEY|ShiftMask,				XK_Delete,		spawn,		SHCMD("sysact shutdown") },
	{ MODKEY|Mod1Mask,				XK_Delete,		spawn,		SHCMD("sysact reboot") },
	// { MODKEY,						XK_End,			spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_End,			spawn,		SHCMD("") },
	// { MODKEY,						XK_Next,		spawn,		SHCMD("") },
	// { MODKEY|ShiftMask,				XK_Next,		spawn,		SHCMD("") },

	{ MODKEY,						XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,				XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,						XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,				XK_Right,	tagmon,		{.i = +1 } },

	// { MODKEY,						XK_F1,			spawn,		SHCMD("") },
	/* { MODKEY,			            XK_F2,		spawn,		SHCMD("") }, */
	/* { MODKEY,			            XK_F3,		spawn,		SHCMD("") }, */
	/* { MODKEY,			            XK_F4,		spawn,		SHCMD("") }, */
	/* { MODKEY,			            XK_F5,		spawn,		SHCMD("") }, */
	/* { MODKEY,			            XK_F6,		spawn,		SHCMD("") }, */
	/* { MODKEY,			            XK_F7,		spawn,		SHCMD("") }, */
	{ MODKEY,			            XK_F8,		spawn,		SHCMD("mailsync") },
	{ MODKEY,			            XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			            XK_F10,		spawn,		SHCMD("dmenuumount") },
	{ MODKEY,			            XK_F11,		spawn,		SHCMD("togglenotify") },
	{ MODKEY,			            XK_F12,		spawn,		SHCMD("st -e nmtui") },

	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,			spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,			spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPause,			spawn,		SHCMD("mpc pause") },
	{ 0, XF86XK_AudioPlay,			spawn,		SHCMD("mpc play") },
	{ 0, XF86XK_AudioStop,			spawn,		SHCMD("mpc stop") },
	{ 0, XF86XK_AudioRewind,		spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,		spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,			spawn,		MUSIC },
	{ 0, XF86XK_AudioMicMute,		spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,			spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,			spawn,		SHCMD("$TERMINAL -e bc -l") },
	{ 0, XF86XK_Sleep,				spawn,		SHCMD("sudo -A systemctl suspend-then-hibernate") },
	{ 0, XF86XK_WWW,				spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,				spawn,		SHCMD("$TERMINAL") },
	{ 0, XF86XK_ScreenSaver,		spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,			spawn,		SHCMD("$TERMINAL -e htop") },
	{ 0, XF86XK_Mail,				spawn,		MAIL },
	{ 0, XF86XK_MyComputer,			spawn,		SHCMD("$TERMINAL -e lf /") },
	/* { 0, XF86XK_Battery,			spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,			spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,		spawn,		SHCMD("toggletouchpad") },
	{ 0, XF86XK_TouchpadOff,		spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,			spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function               argument */
	{ ClkWinTitle,          0,              Button2,        zoom,                  {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,             {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating,        {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,           {0} },
	{ ClkTagBar,            0,              Button1,        view,                  {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,            {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,                   {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,             {0} },
};
