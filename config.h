/*                          
 *        __                 
 *   ____/ /      ______ ___ 
 *  / __  / | /| / / __ `__ \
 * / /_/ /| |/ |/ / / / / / /
 * \__,_/ |__/|__/_/ /_/ /_/ 
 *
 * Applied Patches:
 * - fullgaps (https://dwm.suckless.org/patches/fullgaps)
 * - statusallmons (https://dwm.suckless.org/patches/statusallmons)
 * - statuspadding (https://dwm.suckless.org/patches/statuspadding)
 * - alwayscenter (https://dwm.suckless.org/patches/alwayscenter)
 * - notitle (https://dwm.suckless.org/patches/notitle)
 * - dwmblocks (https://github.com/ashish-yadav11/dwmblocks > patches)
 *
 */ 

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows          */
static const unsigned int snap      = 32;       /* snap pixel 				        */
static const unsigned int gappx     = 22;       /* gaps between windows             */
static const int indx 	            = 2;        /* height of tag indicator          */
static const int horizpadbar        = 4;        /* horizontal padding for statusbar */
static const int vertpadbar         = 4;        /* vertical padding for statusbar   */
static const int showbar            = 1;        /* 0 means no bar                   */
static const int topbar             = 1;        /* 0 means bottom bar               */

static const char *fonts[]          = {"Noto Sans Mono:style=Bold:size=11:antialias=true:autohint=true",
                                       "consolas:size=15:antialias=true:autohint=true",
                                       "fontawesome:size=11:antialias=true:autohint=true"};


/* color definitions */
static const char col_background[]  = "#1e1e1e"; /* background color of bar               */
static const char col_border[]      = "#444444"; /* border color unfocused windows        */
static const char col_font[]        = "#a9a9a9"; /* default font color                    */
static const char col_active[]      = "#004763"; /* border color focused windows and tags */


/* color schemes */
enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel };

static const char *colors[][3]        = {
	/*               fg          bg               border     */
	[SchemeNorm] = { col_font,   col_background,  col_border  }, // \x11
	[SchemeCol1] = { "#a54242",  col_background,  col_border  }, // \x12
	[SchemeCol2] = { "#8c9440",  col_background,  col_border  }, // \x13
	[SchemeCol3] = { "#de935f",  col_background,  col_border  }, // \x14
	[SchemeCol4] = { "#5f819d",  col_background,  col_border  }, // \x15
	[SchemeCol5] = { "#85678f",  col_background,  col_border  }, // \x16
	[SchemeCol6] = { "#5e8d87",  col_background,  col_border  }, // \x17
	[SchemeSel]  = { col_font,   col_active,      col_active  }, // \x18
};


/* tagging */
static const char *tags[] = {"\uf121", "\uf0ac", "\uf06d", "\uf292"};


/* wm class rules */
static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{  NULL,      NULL,      "popup",     0,            1,           -1 },
};


/* initial layout(s) */
static const float mfact        = 0.5;  /* factor of master area size [0.05..0.95]      */
static const int nmaster        = 1;    /* number of clients in master area             */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window  */


/* layout indicators */
static const Layout layouts[] = {
	/* symbol     	 arrangement */
	{ ">  \uf1b2 ",  tile },
	{ ">  \uf5fd ",  NULL },
	{ ">  [M] ",     monocle },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* shell command helper (pre dwm-5.0) */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon };
static const char *termcmd[]  = { "urxvt", NULL };


/* keyboard shortcuts */
static Key keys[] = {
	/* modifier     (chain key)     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },

	/* layout switching */
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },

	/* layout manipulation */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_0,      setgaps,        {.i = 0  } },

	/* monitor naviation */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	/* tag navigation */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* custom keybinds */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("maim -s -u | xclip -selection clipboard -t image/png -i") },

	/* exiting keybind(s) */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};


/* button definitions */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	/* dwmblocks signal(s) */
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} }, /* left   */
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} }, /* middle */
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} }, /* right  */
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} }, /* up     */
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} }, /* down   */
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} }, /* s + lc */

	/* additional keybinds */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

