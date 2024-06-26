#ifndef __AVGDVG__
#define __AVGDVG__

/* vector engine types, passed to vg_init */

#define AVGDVG_MIN          1
#define USE_DVG             1
#define USE_AVG_RBARON      2
#define USE_AVG_BZONE       3
#define USE_AVG             4
#define USE_AVG_TEMPEST     5
#define USE_AVG_MHAVOC      6
#define USE_AVG_SWARS       7
#define USE_AVG_QUANTUM     8
#define AVGDVG_MAX          8

int avgdvg_done (void);
void avgdvg_go (int offset, int data);
void avgdvg_reset (int offset, int data);
int avgdvg_init(int vgType);

/* Apart from the color mentioned below, the vector games will make additional
 * entries for translucency/antialiasing and for backdrop/overlay artwork */

/* Black and White vector colors for Asteroids, Lunar Lander, Omega Race */
void avg_init_palette_white (unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);
/* Monochrome Aqua vector colors for Asteroids Deluxe and Red Baron */
void avg_init_palette_aqua  (unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);
/* Red and Green vector colors for Battlezone */
void avg_init_palette_bzone (unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);
/* Basic 8 rgb vector colors for Tempest, Gravitar, Major Havoc etc. */
void avg_init_palette_multi (unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);
/* Special case for Star Wars and Empire strikes back */
void avg_init_palette_swars (unsigned char *palette, unsigned short *colortable,const unsigned char *color_prom);

/* Some games use a colorram. This is not handled via the Mame core functions
 * right now, but in src/vidhrdw/avgdvg.c itself. */
void tempest_colorram_w (int offset, int data);
void mhavoc_colorram_w (int offset, int data);
void quantum_colorram_w (int offset, int data);

void dvg_screenrefresh(struct osd_bitmap *bitmap,int full_refresh);
void avg_screenrefresh(struct osd_bitmap *bitmap,int full_refresh);
int dvg_start(void);
int avg_start(void);
int avg_start_tempest(void);
int avg_start_mhavoc(void);
int avg_start_starwars(void);
int avg_start_quantum(void);
int avg_start_bzone(void);
int avg_start_redbaron(void);
void dvg_stop(void);
void avg_stop(void);

#endif
