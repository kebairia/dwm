/* See LICENSE file for copyright and license details. */
/*Constants*/
#define TERMINAL "st"
#define TERMCLASS "St"
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Sans:size=11" };
static const char dmenufont[]       = "Fira Code:size=12";
static const char col_gray1[]       = "#212021";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "95x30", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spfm", "-g", "95x30", "-e", "ncmpcpp", NULL };
const char *spcmd3[] = {TERMINAL, "-n", "spcalc", "-f", "FantasqueSansMono-Regular:pixelsize=27", "-g", "55x10", "-e", "python", "-q", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",        spcmd2},
	{"spcalc",      spcmd3},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	   	instance    title       tags mask     	 isfloating   monitor */
	{ "Gimp",     	   	NULL,       NULL,       1<<3,            	 0,           -1 },
	{ "Emacs",    	   	NULL,       NULL,       2,            	 0,           -1 },
	{ "firefox",  	   	NULL,       NULL,       1,       	 0,           -1 },
	{ "Brave-browser",  	   	NULL,       NULL,       1,       	 0,           -1 },
	{ "Virt-manager",  	NULL,       NULL,       1<<8,       	 0,           -1 },
	{ "VirtualBox Manager", NULL,       NULL,       1<<8,       	 0,           -1 },
	{ "Inkscape",  		NULL,       NULL,       1<<4,       	 0,           -1 },
	{ "Gimp",  		NULL,       NULL,       1<<4,       	 0,           -1 },
	{ "discord",  		NULL,       NULL,       1<<3,       	 0,           -1 },
	{ NULL,	      	  	NULL,       "neomutt",	1<<3,	 	 0,	      -1 },
	{ NULL,	      	  	NULL,       "newsboat",	1<<3,	 	 0,	      -1 },
	{ NULL,	      	  	"spterm",   NULL,	SPTAG(0),	 1,	      -1 },
	{ NULL,	      	  	"spfm",     NULL,	SPTAG(1),	 1,	      -1 },
	{ NULL,	      	  	"spcalc",   NULL,	SPTAG(2),	 1,	      -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* keys definitions */
#define BrightDown	0x1008ff03
#define BrightUp	0x1008ff02
#define AudioMute	0x1008ff12
#define AudioPlay	0x1008ff14
#define AudioNext	0x1008ff17
#define AudioPrev	0x1008ff16
#define AudioDown	0x1008ff11
#define AudioUp		0x1008ff13
//#define TouchPad	0x1008ffa9
#define Print		0xff61
#define MODKEY 		Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,             		XK_p,      spawn,          {.v = dmenucmd } },
	/* STARTING SCRIPTS */
	{ MODKEY,                       XK_Return, 	spawn,	SHCMD("$TERMINAL")  },
	{ MODKEY|ShiftMask,             XK_w, 	   	spawn,	SHCMD("$BROWSER")  },
	{ MODKEY,	             	XK_i, 	   	spawn,	SHCMD("$TERMINAL -e $FILE")  },
	{ MODKEY|ShiftMask,	        XK_e, 	   	spawn,	SHCMD("$TERMINAL -e neomutt")  },
	{ MODKEY,	        	XK_n, 	   	spawn,	SHCMD("$TERMINAL -e newsboat")  },
	{ MODKEY|ShiftMask,	        XK_y, 	   	spawn,	SHCMD("mpt")  },
	{ MODKEY,	       		XK_s, 	   	spawn,	SHCMD("$TERMINAL -e htop")  },
	{ MODKEY|ShiftMask,	        XK_p, 	   	spawn,	SHCMD("passmenu")  },
	{ MODKEY|ControlMask,           XK_m, 	   	spawn,	SHCMD("emacsclient --create-frame --alternate-editor ''")},
	{ MODKEY|ShiftMask,             XK_m, 	   	spawn,	SHCMD("monitors")  },
	{ MODKEY,                       XK_u, 	   	spawn,	SHCMD("_mount")  },
	{ MODKEY|ShiftMask,             XK_u, 	   	spawn,	SHCMD("_umount")  },
	{ MODKEY|ControlMask,           XK_n, 	   	spawn,	SHCMD("_emoji")  },
	{ MODKEY|ShiftMask,             XK_n, 	   	spawn,	SHCMD("_awesomefonts")  },
	/* VOLUME */
	{0,                             AudioDown,	spawn,	SHCMD("amixer -q -D pulse sset Master 5%- unmute ")  },
	{0,                             AudioUp,	spawn,	SHCMD("amixer -q -D pulse sset Master 5%+ unmute")  },
	{0,                             AudioMute,	spawn,	SHCMD("amixer -q -D pulse sset Master toggle; pkill -RTMIN+10 dwmblocks")  },
	{0,                             AudioPlay,	spawn,	SHCMD("mpc toggle")  },
	{0,                             AudioNext,	spawn,	SHCMD("mpc next")  },
	{0,                             AudioPrev,	spawn,	SHCMD("mpc prev")  },
	{MODKEY,                        AudioPlay,	spawn,	SHCMD("mpc seek 0")  },
	{MODKEY,                        AudioNext,	spawn,	SHCMD("mpc seek +10")  },
	{MODKEY,                        AudioPrev,	spawn,	SHCMD("mpc seek -10")  },
	/* BRIGHTNESS */
 	{ 0,                            BrightUp,	spawn,	SHCMD("xbacklight -inc 15")  },
 	{ 0,                            BrightDown,	spawn,	SHCMD("xbacklight -dec 15")  },
 	{ 0,                            Print,		spawn,	SHCMD("scrot '%Y-%m-%d-%s_$wx$h.png' -e 'mv $f ~/pix/shots' && notify-send ' Picture saved in ~/pix/shots'")  },
 	{MODKEY,                        Print,		spawn,	SHCMD("scrot '%Y-%m-%d-%s_$wx$h.png' -s  -e 'mv $f ~/pix/shots' && notify-send ' Picture saved in ~/pix/shots'")  },
	/* SCRATCHPADS */
	{ MODKEY,            		XK_o,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_m,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            		XK_q,	   togglescratch,  {.ui = 2 } },
	/* OTHER */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	/* MOVE+RESIZE */
    	// Movement
	{ MODKEY|ShiftMask,             XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
    	// Resising
	{ MODKEY|ControlMask,           XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask,           XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ControlMask,           XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
    	// Moving to the corners
	{ MODKEY|ControlMask|ShiftMask, XK_j,      moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      moveresizeedge, {.v = "l"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	//{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

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
	//{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
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
