/*
 ******************* X-Mame header file *********************
 * file "xmame.h"
 *
 * by jantonio@dit.upm.es
 *
 ************************************************************
*/

#ifndef __XMAME_H_
#define __XMAME_H_

#ifdef __MAIN_C_
#define EXTERN
#else
#define EXTERN extern
#endif

/*
 * Include files.
 */

#ifdef openstep
#include <libc.h>
#include <math.h>
#endif /* openstep */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "osdepend.h"
#include "mame.h"
#include "sysdep/sysdep_palette.h"
#include "sysdep/rc.h"
#include "sysdep/sound_stream.h"

/*
 * Definitions.
 */
#ifndef TRUE
#define	TRUE			(1)
#endif

#ifndef FALSE
#define FALSE			(0)
#endif

#define OSD_OK			(0)
#define OSD_NOT_OK		(1)

#define DEBUG(x)

#define FRAMESKIP_LEVELS 12

/* Taken from common.h since the rest of common.h creates to many conflicts
   with X headers */
struct my_rectangle
{
	int min_x,max_x;
	int min_y,max_y;
};

/*
 * Global variables.
 */

/* dirty stuff */
#if !defined xgl
EXTERN unsigned char *dirty_lines;
EXTERN unsigned char **dirty_blocks;
EXTERN unsigned char *old_dirty_lines;
EXTERN unsigned char **old_dirty_blocks;
#endif

/* global variables and miscellaneous flags */

EXTERN int		sound_enabled;
EXTERN int	 	widthscale;     /* X scale */
EXTERN int	 	heightscale;    /* Y SCALE */
EXTERN char		*home_dir;
EXTERN char		title[50]; 
EXTERN int		use_mouse;
EXTERN int		use_dirty;
EXTERN int		throttle;
EXTERN int		autoframeskip;
EXTERN int		frameskip;
EXTERN int		game_index;
EXTERN struct osd_bitmap *bitmap;
EXTERN int		use_scanlines;
EXTERN int		cabview;
EXTERN char		*cabname;
EXTERN float		display_aspect_ratio;
EXTERN int 		sleep_idle;
EXTERN int 		max_autoframeskip;
EXTERN struct sysdep_palette_info display_palette_info;
EXTERN struct sysdep_palette_struct *sysdep_palette;
EXTERN struct sound_stream_struct *sound_stream;
#ifdef MESS
EXTERN char		*crcdir;
#endif

/* visual is the visual part of the bitmap */
EXTERN int 		visual_width;
EXTERN int		visual_height;
EXTERN struct my_rectangle visual;

/* File descripters for stdout / stderr redirection, without svgalib inter
   fering */
EXTERN FILE *stdout_file;
EXTERN FILE *stderr_file;

/* system dependent functions */
int  sysdep_init(void);
void sysdep_close(void);
int  sysdep_create_display(void);
int  sysdep_display_alloc_palette(int writable_colors);
int  sysdep_display_set_pen(int pen, unsigned char red, unsigned char green, unsigned char blue);
int  sysdep_display_16bpp_capable(void);
void sysdep_update_display(void);
int  sysdep_set_video_mode(void);
void sysdep_set_text_mode(void);

/* input related */
int  osd_input_initpre(void);
int  osd_input_initpost(void);
void osd_input_close(void);
void sysdep_update_keyboard (void);
void sysdep_mouse_poll(void);

/* dirty functions */
int  osd_dirty_init(void);
void osd_dirty_close(void);
void osd_dirty_merge(void);

/* network funtions */
int  osd_net_init(void);
void osd_net_close(void);

/* debug functions */
int  osd_debug_init(void);
void osd_debug_close(void);

/* mode handling functions */
int mode_disabled(int width, int height);
int mode_match(int width, int height);

/* frameskip functions */
int dos_skip_next_frame(int show_fps_counter);
int barath_skip_next_frame(int show_fps_counter);

/* miscelaneous */
int config_init (int argc, char *argv[]);
void config_exit(void);
int frontend_list(char *gamename);
int frontend_ident(char *gamename);
void init_rom_path(void);
#ifndef HAVE_SNPRINTF
int snprintf(char *s, size_t maxlen, const char *fmt, ...);
#endif

/* option structs */
extern struct rc_option video_opts[];
extern struct rc_option display_opts[];
extern struct rc_option mode_opts[];
extern struct rc_option sound_opts[];
extern struct rc_option input_opts[];
extern struct rc_option network_opts[];
extern struct rc_option fileio_opts[];
extern struct rc_option frontend_list_opts[];
extern struct rc_option frontend_ident_opts[];

#undef EXTERN
#endif
