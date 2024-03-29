/***************************************************************************

Super Pac-Man memory map (preliminary)

driver by Aaron Giles

CPU #1:
0000-03ff video RAM
0400-07ff color RAM
0800-0f7f RAM
0f80-0fff sprite data 1 (sprite number & color)
1000-177f RAM
1780-17ff sprite data 2 (x, y position)
1800-1f7f RAM
1f80-1fff sprite data 3 (high bit of y, flip flags, double-size flags)
2000      watchdog timer?
4040-43ff RAM shared with CPU #2
4800-480f custom I/O chip #1
4810-481f custom I/O chip #2
5000      reset CPU #2
5002-5003 IRQ enable
5008-5009 sound enable
500a-500b CPU #2 enable
8000      watchdog timer
c000-ffff ROM

CPU #2:
0000-0040 sound registers
0040-03ff RAM shared with CPU #1
f000-ffff ROM

Interrupts:
CPU #1 IRQ generated by VBLANK
CPU #2 uses no interrupts

***************************************************************************/

#include "driver.h"
#include "vidhrdw/generic.h"

extern unsigned char *mappy_soundregs;
void mappy_sound_enable_w(int offset,int data);
void mappy_sound_w(int offset,int data);

extern unsigned char *superpac_sharedram;
extern unsigned char *superpac_customio_1,*superpac_customio_2;
int superpac_customio_r(int offset);
int superpac_sharedram_r(int offset);
int superpac_sharedram_r2(int offset);
void superpac_sharedram_w(int offset,int data);
void superpac_customio_w_1(int offset,int data);
void superpac_customio_w_2(int offset,int data);
int superpac_customio_r_1(int offset);
int superpac_customio_r_2(int offset);
void superpac_interrupt_enable_1_w(int offset,int data);
void superpac_cpu_enable_w(int offset,int data);
int superpac_interrupt_1(void);
void superpac_reset_2_w(int offset,int data);

int pacnpal_sharedram_r2(int offset);
void pacnpal_sharedram_w2(int offset,int data);
int pacnpal_interrupt_2(void);
void pacnpal_interrupt_enable_2_w(int offset,int data);

int superpac_vh_start(void);
void superpac_vh_screenrefresh(struct osd_bitmap *bitmap,int full_refresh);
void superpac_init_machine(void);
void superpac_vh_convert_color_prom(unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);


/* CPU 1 read addresses */
static struct MemoryReadAddress readmem_cpu1[] =
{
	{ 0x0000, 0x1fff, MRA_RAM },                                       /* general RAM */
	{ 0x4040, 0x43ff, superpac_sharedram_r },     /* shared RAM */
	{ 0x4800, 0x480f, superpac_customio_r_1 },   /* custom I/O chip #1 interface */
	{ 0x4810, 0x481f, superpac_customio_r_2 },   /* custom I/O chip #2 interface */
	{ 0xa000, 0xffff, MRA_ROM },						/* SPC-2.1C at 0xc000, SPC-1.1B at 0xe000 */
	{ -1 }                                              /* end of table */
};


/* CPU 1 write addresses */
static struct MemoryWriteAddress writemem_cpu1[] =
{
	{ 0x0000, 0x03ff, videoram_w, &videoram, &videoram_size },          /* video RAM */
	{ 0x0400, 0x07ff, colorram_w, &colorram },          /* color RAM */
	{ 0x0800, 0x0f7f, MWA_RAM },                        /* RAM */
	{ 0x0f80, 0x0fff, MWA_RAM, &spriteram, &spriteram_size },            /* sprite RAM, area 1 */
	{ 0x1000, 0x177f, MWA_RAM },                        /* RAM */
	{ 0x1780, 0x17ff, MWA_RAM, &spriteram_2 },          /* sprite RAM, area 2 */
	{ 0x1800, 0x1f7f, MWA_RAM },                        /* RAM */
	{ 0x1f80, 0x1fff, MWA_RAM, &spriteram_3 },          /* sprite RAM, area 3 */
	{ 0x2000, 0x2000, MWA_NOP },                        /* watchdog timer */
	{ 0x4040, 0x43ff, superpac_sharedram_w, &superpac_sharedram },	/* shared RAM */
	{ 0x4800, 0x480f, superpac_customio_w_1, &superpac_customio_1 },	/* custom I/O chip #1 interface */
	{ 0x4810, 0x481f, superpac_customio_w_2, &superpac_customio_2 },	/* custom I/O chip #2 interface */
	{ 0x5000, 0x5000, superpac_reset_2_w },				/* reset CPU #2 */
	{ 0x5002, 0x5003, superpac_interrupt_enable_1_w },  /* interrupt enable */
	{ 0x5008, 0x5009, mappy_sound_enable_w },           /* sound enable */
	{ 0x500a, 0x500b, superpac_cpu_enable_w },          /* interrupt enable */
	{ 0x8000, 0x8000, MWA_NOP },                        /* watchdog timer */
	{ 0xa000, 0xffff, MWA_ROM },                        /* SPC-2.1C at 0xc000, SPC-1.1B at 0xe000 */
	{ -1 }                                              /* end of table */
};


/* CPU 2 read addresses */
static struct MemoryReadAddress superpac_readmem_cpu2[] =
{
	{ 0xf000, 0xffff, MRA_ROM },                        /* ROM code */
	{ 0x0040, 0x03ff, superpac_sharedram_r2 },          /* shared RAM with the main CPU */
	{ -1 }                                              /* end of table */
};


/* CPU 2 write addresses */
static struct MemoryWriteAddress superpac_writemem_cpu2[] =
{
	{ 0x0040, 0x03ff, superpac_sharedram_w },           /* shared RAM with the main CPU */
	{ 0x0000, 0x003f, mappy_sound_w, &mappy_soundregs },/* sound control registers */
	{ 0xf000, 0xffff, MWA_ROM },                        /* ROM code */
	{ -1 }                                              /* end of table */
};


/* CPU 2 read addresses */
static struct MemoryReadAddress pacnpal_readmem_cpu2[] =
{
	{ 0xf000, 0xffff, MRA_ROM },                        /* ROM code */
	{ 0x0040, 0x03ff, pacnpal_sharedram_r2 },           /* shared RAM with the main CPU */
	{ -1 }                                              /* end of table */
};


/* CPU 2 write addresses */
static struct MemoryWriteAddress pacnpal_writemem_cpu2[] =
{
	{ 0x0040, 0x03ff, pacnpal_sharedram_w2 },           /* shared RAM with the main CPU */
	{ 0x0000, 0x003f, mappy_sound_w, &mappy_soundregs },/* sound control registers */
	{ 0x2000, 0x2001, pacnpal_interrupt_enable_2_w },   /* interrupt enable */
	{ 0x2006, 0x2007, mappy_sound_enable_w },           /* sound enable */
	{ 0xf000, 0xffff, MWA_ROM },                        /* ROM code */
	{ -1 }                                              /* end of table */
};


/* input from the outside world */
INPUT_PORTS_START( superpac )
	PORT_START	/* DSW0 */
	PORT_DIPNAME( 0x0f, 0x00, DEF_STR( Difficulty ) )
	PORT_DIPSETTING(    0x00, "Rank 0-Normal" )
	PORT_DIPSETTING(    0x01, "Rank 1-Easiest" )
	PORT_DIPSETTING(    0x02, "Rank 2" )
	PORT_DIPSETTING(    0x03, "Rank 3" )
	PORT_DIPSETTING(    0x04, "Rank 4" )
	PORT_DIPSETTING(    0x05, "Rank 5" )
	PORT_DIPSETTING(    0x06, "Rank 6-Medium" )
	PORT_DIPSETTING(    0x07, "Rank 7" )
	PORT_DIPSETTING(    0x08, "Rank 8-Default" )
	PORT_DIPSETTING(    0x09, "Rank 9" )
	PORT_DIPSETTING(    0x0a, "Rank A" )
	PORT_DIPSETTING(    0x0b, "Rank B-Hardest" )
	PORT_DIPSETTING(    0x0c, "Rank C-Easy Auto" )
	PORT_DIPSETTING(    0x0d, "Rank D-Auto" )
	PORT_DIPSETTING(    0x0e, "Rank E-Auto" )
	PORT_DIPSETTING(    0x0f, "Rank F-Hard Auto" )
	PORT_DIPNAME( 0x30, 0x00, DEF_STR( Coin_B ) )
	PORT_DIPSETTING(    0x20, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x30, DEF_STR( 2C_3C ) )
	PORT_DIPSETTING(    0x10, DEF_STR( 1C_2C ) )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Demo_Sounds ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x00, DEF_STR( On ) )
	PORT_DIPNAME( 0x80, 0x00, "Freeze" )
	PORT_DIPSETTING(    0x00, DEF_STR( Off ) )
	PORT_DIPSETTING(    0x80, DEF_STR( On ) )

	PORT_START	/* DSW1 */
	PORT_DIPNAME( 0x07, 0x00, DEF_STR( Coin_A ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 2C_3C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_7C ) )
	PORT_DIPNAME( 0x38, 0x00, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x38, "None" )
	PORT_DIPSETTING(    0x30, "30k" )
	PORT_DIPSETTING(    0x08, "30k 80k" )
	PORT_DIPSETTING(    0x00, "30k 100k" )
	PORT_DIPSETTING(    0x10, "30k 120k" )
	PORT_DIPSETTING(    0x18, "30k 80k 80k" )
	PORT_DIPSETTING(    0x20, "30k 100k 100k" )
	PORT_DIPSETTING(    0x28, "30k 120k 120k" )
/* TODO: bonus scores for 5 lives */
/* 	PORT_DIPNAME( 0x38, 0x00, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x38, "None" )
	PORT_DIPSETTING(    0x28, "30k" )
	PORT_DIPSETTING(    0x30, "40k" )
	PORT_DIPSETTING(    0x00, "30k 100k" )
	PORT_DIPSETTING(    0x08, "30k 120k" )
	PORT_DIPSETTING(    0x10, "40k 120k" )
	PORT_DIPSETTING(    0x18, "30k 100k 100k" )
	PORT_DIPSETTING(    0x20, "40k 120k 120k" ) */
	PORT_DIPNAME( 0xc0, 0x00, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x40, "1" )
	PORT_DIPSETTING(    0x80, "2" )
	PORT_DIPSETTING(    0x00, "3" )
	PORT_DIPSETTING(    0xc0, "5" )

	PORT_START	/* FAKE */
	/* The player inputs are not memory mapped, they are handled by an I/O chip. */
	/* These fake input ports are read by mappy_customio_data_r() */
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP | IPF_4WAY )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT | IPF_4WAY )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN | IPF_4WAY )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT | IPF_4WAY )
	PORT_BIT_IMPULSE( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1, 1 )
	PORT_BITX(0x20, IP_ACTIVE_HIGH, IPT_BUTTON1, 0, IP_KEY_PREVIOUS, IP_JOY_PREVIOUS )
	PORT_BIT( 0xc0, IP_ACTIVE_HIGH, IPT_UNUSED )

	PORT_START	/* FAKE */
	PORT_BIT_IMPULSE( 0x01, IP_ACTIVE_HIGH, IPT_COIN1, 1 )
	PORT_BIT_IMPULSE( 0x02, IP_ACTIVE_HIGH, IPT_COIN2, 1 )
	PORT_BIT( 0x0c, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT_IMPULSE( 0x10, IP_ACTIVE_HIGH, IPT_START1, 1 )
	PORT_BIT_IMPULSE( 0x20, IP_ACTIVE_HIGH, IPT_START2, 1 )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Cocktail ) )
	PORT_SERVICE( 0x80, IP_ACTIVE_HIGH )
INPUT_PORTS_END


INPUT_PORTS_START( pacnpal )
	PORT_START	/* DSW0 */
	PORT_DIPNAME( 0x03, 0x00, DEF_STR( Coin_B ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 2C_3C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_2C ) )
	PORT_DIPNAME( 0x0c, 0x00, "Rank" )
	PORT_DIPSETTING(    0x00, "A" )
	PORT_DIPSETTING(    0x04, "B" )
	PORT_DIPSETTING(    0x08, "C" )
	PORT_DIPSETTING(    0x0c, "D" )
	PORT_BIT( 0xf0, IP_ACTIVE_HIGH, IPT_UNUSED )

	PORT_START	/* DSW1 */
	PORT_DIPNAME( 0x07, 0x00, DEF_STR( Coin_A ) )
	PORT_DIPSETTING(    0x07, DEF_STR( 3C_1C ) )
	PORT_DIPSETTING(    0x05, DEF_STR( 2C_1C ) )
	PORT_DIPSETTING(    0x00, DEF_STR( 1C_1C ) )
	PORT_DIPSETTING(    0x06, DEF_STR( 2C_3C ) )
	PORT_DIPSETTING(    0x01, DEF_STR( 1C_2C ) )
	PORT_DIPSETTING(    0x02, DEF_STR( 1C_3C ) )
	PORT_DIPSETTING(    0x03, DEF_STR( 1C_6C ) )
	PORT_DIPSETTING(    0x04, DEF_STR( 1C_7C ) )
	PORT_DIPNAME( 0x38, 0x18, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x00, "None" )
	PORT_DIPSETTING(    0x38, "30k" )
	PORT_DIPSETTING(    0x18, "20k 70k" )
	PORT_DIPSETTING(    0x20, "30k 70k" )
	PORT_DIPSETTING(    0x28, "30k 80k" )
	PORT_DIPSETTING(    0x30, "30k 100k" )
	PORT_DIPSETTING(    0x08, "20k 70k 70k" )
	PORT_DIPSETTING(    0x10, "30k 80k 80k" )
	/* TODO: bonus scores are different for 5 lives */
/* 	PORT_DIPNAME( 0x38, 0x18, DEF_STR( Bonus_Life ) )
	PORT_DIPSETTING(    0x00, "None" )
	PORT_DIPSETTING(    0x30, "30k" )
	PORT_DIPSETTING(    0x38, "40k" )
	PORT_DIPSETTING(    0x18, "30k 80k" )
	PORT_DIPSETTING(    0x20, "30k 100k" )
	PORT_DIPSETTING(    0x28, "40k 120k" )
	PORT_DIPSETTING(    0x08, "30k 80k 80k" )
	PORT_DIPSETTING(    0x10, "40k 100k 100k" ) */
	PORT_DIPNAME( 0xc0, 0x80, DEF_STR( Lives ) )
	PORT_DIPSETTING(    0x00, "1" )
	PORT_DIPSETTING(    0x40, "2" )
	PORT_DIPSETTING(    0x80, "3" )
	PORT_DIPSETTING(    0xc0, "5" )

	PORT_START	/* FAKE */
	/* The player inputs are not memory mapped, they are handled by an I/O chip. */
	/* These fake input ports are read by mappy_customio_data_r() */
	PORT_BIT( 0x01, IP_ACTIVE_HIGH, IPT_JOYSTICK_UP | IPF_4WAY )
	PORT_BIT( 0x02, IP_ACTIVE_HIGH, IPT_JOYSTICK_RIGHT | IPF_4WAY )
	PORT_BIT( 0x04, IP_ACTIVE_HIGH, IPT_JOYSTICK_DOWN | IPF_4WAY )
	PORT_BIT( 0x08, IP_ACTIVE_HIGH, IPT_JOYSTICK_LEFT | IPF_4WAY )
	PORT_BIT_IMPULSE( 0x10, IP_ACTIVE_HIGH, IPT_BUTTON1, 2 )
	PORT_BITX(0x20, IP_ACTIVE_HIGH, IPT_BUTTON1, 0, IP_KEY_PREVIOUS, IP_JOY_PREVIOUS )
	PORT_BIT( 0xc0, IP_ACTIVE_HIGH, IPT_UNUSED )

	PORT_START	/* FAKE */
	PORT_BIT_IMPULSE( 0x01, IP_ACTIVE_HIGH, IPT_COIN1, 2 )
	PORT_BIT_IMPULSE( 0x02, IP_ACTIVE_HIGH, IPT_COIN2, 2 )
	PORT_BIT( 0x0c, IP_ACTIVE_HIGH, IPT_UNUSED )
	PORT_BIT_IMPULSE( 0x10, IP_ACTIVE_HIGH, IPT_START1, 2 )
	PORT_BIT_IMPULSE( 0x20, IP_ACTIVE_HIGH, IPT_START2, 2 )
	PORT_DIPNAME( 0x40, 0x00, DEF_STR( Cabinet ) )
	PORT_DIPSETTING(    0x00, DEF_STR( Upright ) )
	PORT_DIPSETTING(    0x40, DEF_STR( Cocktail ) )
	PORT_SERVICE( 0x80, IP_ACTIVE_HIGH )
INPUT_PORTS_END


/* SUPERPAC -- ROM SPV-1.3C (4K) */
static struct GfxLayout charlayout =
{
	8,8,                                           /* 8*8 characters */
	256,                                           /* 256 characters */
	2,                                             /* 2 bits per pixel */
	{ 0, 4 },                                      /* the two bitplanes for 4 pixels are packed into one byte */
	{ 8*8+0, 8*8+1, 8*8+2, 8*8+3, 0, 1, 2, 3 },    /* bits are packed in groups of four */
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8 },    /* characters are rotated 90 degrees */
	16*8                                           /* every char takes 16 bytes */
};


/* SUPERPAC -- ROM SPV-2.3F (8K) */
static struct GfxLayout spritelayout =
{
	16,16,                                         /* 16*16 sprites */
	128,                                           /* 128 sprites */
	2,                                             /* 2 bits per pixel */
	{ 0, 4 },                                      /* the two bitplanes for 4 pixels are packed into one byte */
	{ 0, 1, 2, 3, 8*8, 8*8+1, 8*8+2, 8*8+3,
			16*8+0, 16*8+1, 16*8+2, 16*8+3, 24*8+0, 24*8+1, 24*8+2, 24*8+3 },
	{ 0*8, 1*8, 2*8, 3*8, 4*8, 5*8, 6*8, 7*8,
			32*8, 33*8, 34*8, 35*8, 36*8, 37*8, 38*8, 39*8 },
	64*8                                           /* every sprite takes 64 bytes */
};


static struct GfxDecodeInfo gfxdecodeinfo[] =
{
	{ REGION_GFX1, 0, &charlayout,      0, 64 },
	{ REGION_GFX2, 0, &spritelayout, 64*4, 64 },
	{ -1 } /* end of array */
};


static struct namco_interface namco_interface =
{
	23920,	/* sample rate (approximate value) */
	8,		/* number of voices */
	100,	/* playback volume */
	REGION_SOUND1	/* memory region */
};



static struct MachineDriver machine_driver_superpac =
{
	/* basic machine hardware  */
	{
		{
			CPU_M6809,
			1100000,             /* 1.1 Mhz */
			readmem_cpu1,        /* MemoryReadAddress */
			writemem_cpu1,       /* MemoryWriteAddress */
			0,                   /* IOReadPort */
			0,                   /* IOWritePort */
			interrupt,           /* interrupt routine */
			1                    /* interrupts per frame */
		},
		{
			CPU_M6809,
			1100000,             /* 1.1 Mhz */
			superpac_readmem_cpu2,/* MemoryReadAddress */
			superpac_writemem_cpu2,/* MemoryWriteAddress */
			0,                   /* IOReadPort */
			0,                   /* IOWritePort */
			ignore_interrupt,    /* interrupt routine */
			1                    /* interrupts per frame */
		}
	},
	60, DEFAULT_60HZ_VBLANK_DURATION,	/* frames per second, vblank duration */
	100,	/* 100 CPU slices per frame - an high value to ensure proper */
			/* synchronization of the CPUs */
	superpac_init_machine,     /* init machine routine */

	/* video hardware */
	36*8, 28*8,                /* screen_width, screen_height */
	{ 0*8, 36*8-1, 0*8, 28*8-1 },/* struct rectangle visible_area */
	gfxdecodeinfo,             /* GfxDecodeInfo * */
	32,                        /* total colors */
	4*(64+64),                 /* color table length */
	superpac_vh_convert_color_prom, /* convert color prom routine */

	VIDEO_TYPE_RASTER|VIDEO_SUPPORTS_DIRTY,
	0,                         /* vh_init routine */
	generic_vh_start,          /* vh_start routine */
	generic_vh_stop,           /* vh_stop routine */
	superpac_vh_screenrefresh, /* vh_update routine */

	/* sound hardware */
	0,0,0,0,
	{
		{
			SOUND_NAMCO,
			&namco_interface
		}
	}
};

static struct MachineDriver machine_driver_pacnpal =
{
	/* basic machine hardware  */
	{
		{
			CPU_M6809,
			1100000,             /* 1.1 Mhz */
			readmem_cpu1,        /* MemoryReadAddress */
			writemem_cpu1,       /* MemoryWriteAddress */
			0,                   /* IOReadPort */
			0,                   /* IOWritePort */
			interrupt,           /* interrupt routine */
			1                    /* interrupts per frame */
		},
		{
			CPU_M6809,
			1100000,             /* 1.1 Mhz */
			pacnpal_readmem_cpu2,/* MemoryReadAddress */
			pacnpal_writemem_cpu2,/* MemoryWriteAddress */
			0,                   /* IOReadPort */
			0,                   /* IOWritePort */
			pacnpal_interrupt_2, /* interrupt routine */
			1                    /* interrupts per frame */
		}
	},
	60, DEFAULT_60HZ_VBLANK_DURATION,	/* frames per second, vblank duration */
	100,	/* 100 CPU slices per frame - an high value to ensure proper */
			/* synchronization of the CPUs */
	superpac_init_machine,     /* init machine routine */

	/* video hardware */
	36*8, 28*8,                /* screen_width, screen_height */
	{ 0*8, 36*8-1, 0*8, 28*8-1 },/* struct rectangle visible_area */
	gfxdecodeinfo,             /* GfxDecodeInfo * */
	32,                        /* total colors */
	4*(64+64),                 /* color table length */
	superpac_vh_convert_color_prom, /* convert color prom routine */

	VIDEO_TYPE_RASTER|VIDEO_SUPPORTS_DIRTY,
	0,                         /* vh_init routine */
	generic_vh_start,          /* vh_start routine */
	generic_vh_stop,           /* vh_stop routine */
	superpac_vh_screenrefresh, /* vh_update routine */

	/* sound hardware */
	0,0,0,0,
	{
		{
			SOUND_NAMCO,
			&namco_interface
		}
	}
};




ROM_START( superpac )
	ROM_REGION( 0x10000, REGION_CPU1 )	/* 64k for code */
	ROM_LOAD( "sp1.2",        0xc000, 0x2000, 0x4bb33d9c )
	ROM_LOAD( "sp1.1",        0xe000, 0x2000, 0x846fbb4a )

	ROM_REGION( 0x10000, REGION_CPU2 )	/* 64k for the second CPU */
	ROM_LOAD( "spc-3.1k",     0xf000, 0x1000, 0x04445ddb )

	ROM_REGION( 0x1000, REGION_GFX1 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "sp1.6",        0x0000, 0x1000, 0x91c5935c )

	ROM_REGION( 0x2000, REGION_GFX2 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "spv-2.3f",     0x0000, 0x2000, 0x670a42f2 )

	ROM_REGION( 0x0220, REGION_PROMS )
	ROM_LOAD( "superpac.4c",  0x0000, 0x0020, 0x9ce22c46 ) /* palette */
	ROM_LOAD( "superpac.4e",  0x0020, 0x0100, 0x1253c5c1 ) /* chars */
	ROM_LOAD( "superpac.3l",  0x0120, 0x0100, 0xd4d7026f ) /* sprites */

	ROM_REGION( 0x0100, REGION_SOUND1 )	/* sound prom */
	ROM_LOAD( "superpac.3m",  0x0000, 0x0100, 0xad43688f )
ROM_END

ROM_START( superpcm )
	ROM_REGION( 0x10000, REGION_CPU1 )	/* 64k for code */
	ROM_LOAD( "spc-2.1c",     0xc000, 0x2000, 0x1a38c30e )
	ROM_LOAD( "spc-1.1b",     0xe000, 0x2000, 0x730e95a9 )

	ROM_REGION( 0x10000, REGION_CPU2 )	/* 64k for the second CPU */
	ROM_LOAD( "spc-3.1k",     0xf000, 0x1000, 0x04445ddb )

	ROM_REGION( 0x1000, REGION_GFX1 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "spv-1.3c",     0x0000, 0x1000, 0x78337e74 )

	ROM_REGION( 0x2000, REGION_GFX2 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "spv-2.3f",     0x0000, 0x2000, 0x670a42f2 )

	ROM_REGION( 0x0220, REGION_PROMS )
	ROM_LOAD( "superpac.4c",  0x0000, 0x0020, 0x9ce22c46 ) /* palette */
	ROM_LOAD( "superpac.4e",  0x0020, 0x0100, 0x1253c5c1 ) /* chars */
	ROM_LOAD( "superpac.3l",  0x0120, 0x0100, 0xd4d7026f ) /* sprites */

	ROM_REGION( 0x0100, REGION_SOUND1 )	/* sound prom */
	ROM_LOAD( "superpac.3m",  0x0000, 0x0100, 0xad43688f )
ROM_END

ROM_START( pacnpal )
	ROM_REGION( 0x10000, REGION_CPU1 )	/* 64k for code */
	ROM_LOAD( "pap13b.cpu",   0xa000, 0x2000, 0xed64a565 )
	ROM_LOAD( "pap12b.cpu",   0xc000, 0x2000, 0x15308bcf )
	ROM_LOAD( "pap11b.cpu",   0xe000, 0x2000, 0x3cac401c )

	ROM_REGION( 0x10000, REGION_CPU2 )	/* 64k for the second CPU */
	ROM_LOAD( "pap14.cpu",    0xf000, 0x1000, 0x330e20de )

	ROM_REGION( 0x1000, REGION_GFX1 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "pap16.cpu",    0x0000, 0x1000, 0xa36b96cb )

	ROM_REGION( 0x2000, REGION_GFX2 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "pap15.vid",    0x0000, 0x2000, 0xfb6f56e3 )

	ROM_REGION( 0x0220, REGION_PROMS )
	ROM_LOAD( "papi6.vid",    0x0000, 0x0020, 0x52634b41 ) /* palette */
	ROM_LOAD( "papi5.vid",    0x0020, 0x0100, 0xac46203c ) /* chars */
	ROM_LOAD( "papi4.vid",    0x0120, 0x0100, 0x686bde84 ) /* sprites */

	ROM_REGION( 0x0100, REGION_SOUND1 )	/* sound prom */
	ROM_LOAD( "papi3.cpu",    0x0000, 0x0100, 0x83c31a98 )
ROM_END

ROM_START( pacnchmp )
	ROM_REGION( 0x10000, REGION_CPU1 )	/* 64k for code */
	ROM_LOAD( "pap3.1d",      0xa000, 0x2000, 0x20a07d3d )
	ROM_LOAD( "pap3.1c",      0xc000, 0x2000, 0x505bae56 )
	ROM_LOAD( "pap11b.cpu",   0xe000, 0x2000, 0x3cac401c )

	ROM_REGION( 0x10000, REGION_CPU2 )	/* 64k for the second CPU */
	ROM_LOAD( "pap14.cpu",    0xf000, 0x1000, 0x330e20de )

	ROM_REGION( 0x1000, REGION_GFX1 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "pap2.3c",      0x0000, 0x1000, 0x93d15c30 )

	ROM_REGION( 0x2000, REGION_GFX2 | REGIONFLAG_DISPOSE )
	ROM_LOAD( "pap2.3f",      0x0000, 0x2000, 0x39f44aa4 )

	ROM_REGION( 0x0220, REGION_PROMS )
	ROM_LOAD( "papi6.vid",    0x0000, 0x0020, BADCRC( 0x52634b41 ) ) /* palette */
	ROM_LOAD( "papi5.vid",    0x0020, 0x0100, BADCRC( 0xac46203c ) ) /* chars */
	ROM_LOAD( "papi4.vid",    0x0120, 0x0100, BADCRC( 0x686bde84 ) ) /* sprites */

	ROM_REGION( 0x0100, REGION_SOUND1 )	/* sound prom */
	ROM_LOAD( "papi3.cpu",    0x0000, 0x0100, 0x83c31a98 )
ROM_END



GAME( 1982, superpac, 0,        superpac, superpac, 0, ROT90, "Namco", "Super Pac-Man" )
GAME( 1982, superpcm, superpac, superpac, superpac, 0, ROT90, "[Namco] (Bally Midway license)", "Super Pac-Man (Midway)" )
GAME( 1983, pacnpal,  0,        pacnpal,  pacnpal,  0, ROT90, "Namco", "Pac & Pal" )
GAME( 1983, pacnchmp, pacnpal,  pacnpal,  pacnpal,  0, ROT90, "Namco", "Pac-Man & Chomp Chomp" )
