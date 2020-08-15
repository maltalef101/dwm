/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx        = 5;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 7;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;        /* vert inner gap between windows */
static const unsigned int gappoh    = 7;        /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;        /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Deja Vu Sans Mono:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#121212";
static char normfgcolor[]           = "#676e6d";
static char normbordercolor[]       = "#121212";
static char selbgcolor[]            = "#323232";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#323232";
static char col_urgborder[]         = "#cc241d";
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
	[SchemeUrg]  = { selfgcolor, selbgcolor,  col_urgborder  },
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
    { "Spotify",            NULL,             "Spotify Premium",                1 << 8,       0,            0,          0,          -1 },
    { NULL,                 NULL,             "Event Tester",                   0,            1,            0,          1,          -1 },
    // floating assingments:
    { NULL,                 NULL,             "Friends List",                   0,            1,            0,          0,          -1 },
    { NULL,                 NULL,             "Steam - News",                   0,            1,            0,          0,          -1 },
    { NULL,                 NULL,             "Discord Updater",                0,            1,            0,          0,          -1 },
    { "pulsemixer",         NULL,             NULL,                             0,            1,            1,          0,          -1 },
    { "weatherreport",      NULL,             NULL,                             0,            1,            1,          0,          -1 },

};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
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

static Key keys[] = {
	/* modifier                     key        function        argument */

    // #---# basic bindings #---#
	{ MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_space,   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,   togglefloating, {0} },

  // #---# letterkey bindings #---#
	{ MODKEY,                       XK_q,       killclient,     {0} },
    // { MODKEY|ShiftMask,             XK_q,      spawn,           SHCMD("") },
    { MODKEY,                       XK_w,       spawn,          SHCMD("$BROWSER") },
  // { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("st -c 'weatherreport' -g 640x408 -e less $HOME/.local/weatherreport") },
    // { MODKEY,                       XK_e,       spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("") },
    // { MODKEY,                       XK_r,      spawn,          SHCMD("") },
    { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("st -e lf") },
	{ MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,       setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_y,       spawn,          SHCMD("st -e irssi") },
  // { MODKEY|ShiftMask,             XK_y,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_u,      spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") },
    { MODKEY,                       XK_i,       spawn,          SHCMD("st -e htop") },
    // { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("") },
    // { MODKEY,                       XK_o,       spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_u,      spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") },
    { MODKEY,                       XK_p,       spawn,          SHCMD("playerctl --player=spotify play-pause") },
    { MODKEY|ShiftMask,             XK_p,       spawn,          SHCMD("$PLAYER") },
	// { MODKEY,                       XK_a,      spawn,          SHCMD("") },
  // { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("") },
    { MODKEY,                       XK_s,       togglesticky,   {0} },
    { MODKEY|Mod1Mask,              XK_s,       togglegaps,     {0} },
    { MODKEY|ShiftMask|Mod1Mask,    XK_s,       defaultgaps,    {0} },
	{ MODKEY,                       XK_d,       spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_d,      spawn,           SHCMD("discord") },
    { MODKEY,                       XK_f,       togglefullscr,  {0} },
    // { MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("") },
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
    { MODKEY,                       XK_x,       spawn,          SHCMD("slock") },
    // { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_c,      spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_v,      spawn,          SHCMD("") },
    { MODKEY|ShiftMask,             XK_v,       spawn,          SHCMD("st -c pulsemixer -g 120x34 -e pulsemixer") },
	{ MODKEY,                       XK_b,       togglebar,      {0} },
    // { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("") },
	// { MODKEY,                       XK_n,      spawn,          SHCMD("") },
    // { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_m,       spawn,           SHCMD("st -e neomutt") },
    // { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("") },

  // #---# non-letter keys bindings #---#
	{ MODKEY,                       XK_Tab,    view,           {0} },
    // { MODKEY|ShiftMask,             XK_Tab,      spawn,          SHCMD("") },
	{ MODKEY,                       XK_comma,  spawn,          SHCMD("playerctl --player=spotify previous") },
    // { MODKEY|ShiftMask,             XK_comma,  spawn,         SHCMD("") },
	{ MODKEY,                       XK_period, spawn,          SHCMD("playerctl --player=spotify next") },
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

  // #---# tag bindings #---#
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_BackSpace, quit,         {0} },
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

