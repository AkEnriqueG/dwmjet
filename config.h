/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=10;antialias=true;autohint=true" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_bg[]          = "#001100";  // Fondo negro verdoso oscuro
static const char col_fg[]          = "#00ff00";  // Verde brillante para texto
static const char col_border[]      = "#008800";  // Verde medio para bordes
static const char col_sel_bg[]      = "#005500";  // Verde oscuro para selección
static const char col_sel_fg[]      = "#00ff00";  // Verde brillante para texto seleccionado
static const char col_sel_border[]  = "#00ff00";  // Verde brillante para borde seleccionado

static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_fg,    col_bg,    col_border },
    [SchemeSel]  = { col_sel_fg,col_sel_bg,col_sel_border },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "kitty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
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
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browsercmd[] = { "brave-browser", NULL };
static const char *emailcmd[] = { "kitty", "-e", "librewolf", NULL };
static const char *newscmd[] = { "kitty", "-e", "brave-browser", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "140x44", NULL };


#include <X11/XF86keysym.h>
static const Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
    { MODKEY,                       XK_e,      spawn,          {.v = emailcmd } },
    { MODKEY,                       XK_n,      spawn,          {.v = newscmd } },
    /* Cmus */
    { 0,            XF86XK_AudioPlay,          spawn,          SHCMD("playerctl play-pause") },
    { 0,            XF86XK_AudioStop,          spawn,          SHCMD("playerctl stop") },
    { 0,            XF86XK_AudioPrev,          spawn,          SHCMD("playerctl previous") },
    { 0,            XF86XK_AudioNext,          spawn,          SHCMD("playerctl next") },

	/* PC escritorio */
	{ 0, XF86XK_Mail, spawn, SHCMD("brave-browser") },
	{ 0, XF86XK_Calculator, spawn, SHCMD("kitty") },
	{ 0, XF86XK_Search, spawn, SHCMD("kitty") },
	{ 0, XF86XK_Tools, spawn, SHCMD("youtube-music") },
	{ 0, XF86XK_Explorer, spawn, SHCMD("thunar") },	
	{ 0, XF86XK_HomePage, spawn, SHCMD("kitty") },	
	{ 0, XF86XK_WWW,  killclient,     {0} },
	
	
	
    
    /* Audio */
    { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
    { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
    { 0, XK_Print, spawn, SHCMD("flameshot gui") },
    // Brightness
    { 0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-") },
    { 0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set 10%+") },
    // SHIFT F1
    { 0,                  XK_F1,     spawn,          SHCMD("kitty") },
    { 0|ShiftMask,                  XK_F2,     spawn,          SHCMD("kitty") },
    { 0|ShiftMask,                  XK_F3,     spawn,          SHCMD("kitty") },
    { 0|ShiftMask,                  XK_F4,     spawn,          SHCMD("kitty") },

    { 0|ShiftMask,                  XK_F5,     spawn,          SHCMD("kitty") },
    { 0|ShiftMask,                  XK_F6,     spawn,          SHCMD("xrandr --output HDMI-A-0 --brightness $(xrandr --verbose | grep -A5 HDMI-A-0 | grep Brightness | awk '{b=$2+0.1; if(b>1.0) b=1.0; print b}')") },
    { 0|ShiftMask,                  XK_F7,     spawn,          SHCMD("hackclock") },
    { 0|ShiftMask,                  XK_F8,     spawn,          SHCMD("xrandr --output HDMI-A-0 --brightness $(xrandr --verbose | grep -A5 HDMI-A-0 | grep Brightness | awk '{b=$2-0.1; if(b<0.2) b=0.2; print b}')") },  

    { 0|ShiftMask,                  XK_F9,     spawn,          SHCMD("brave-browser") },
    { 0|ShiftMask,                  XK_F10,    spawn,          SHCMD("brave-browser") },

    { 0|ShiftMask,                  XK_F11,    spawn,          SHCMD("xrandr --output DisplayPort-1 --auto --right-of HDMI-A-0") },    
    { 0,                            XK_F11,    spawn,          SHCMD("brave-browser") },
    
    { 0|ShiftMask,                  XK_F12,    spawn,          SHCMD("xrandr --output DisplayPort-1 --off") },
    { 0,                            XK_F12,    spawn,          SHCMD("kitty") },

    { MODKEY,                       XK_u,      spawn,          SHCMD("unicode") },
    { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("bookmarks") },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
      
};


/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkTagBar */
static const Button buttons[] = {
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
