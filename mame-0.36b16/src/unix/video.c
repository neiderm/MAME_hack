/*
 * X-Mame generic video code
 *
 */
#define __VIDEO_C_
#include <math.h>
#include "xmame.h"
#include "driver.h"
#include "profiler.h"
#include "input.h"
/* for uclock */
#include "sysdep/misc.h"

#define FRAMESKIP_DRIVER_COUNT 2

extern int bitmap_dirty;
static const int safety = 16;
static float beam_f, flicker_f;
static float widthscale_f, heightscale_f;
static char *vector_res = NULL;
static int use_auto_double = 1;
static int frameskipper = 0;
static float gamma_correction = 1.0;
static int brightness = 100;
static float brightness_paused_adjust = 1.0;

/* some prototypes */
static int video_handle_scale(struct rc_option *option, const char *arg,
   int priority);
static int video_verify_scale(struct rc_option *option, const char *arg,
   int priority);
static int video_verify_beam(struct rc_option *option, const char *arg,
   int priority);
static int video_verify_flicker(struct rc_option *option, const char *arg,
   int priority);
static int video_verify_bpp(struct rc_option *option, const char *arg,
   int priority);

struct rc_option video_opts[] = {
   /* name, shortname, type, dest, deflt, min, max, func, help */
   { "Video Related",	NULL,			rc_seperator,	NULL,
     NULL,		0,			0,		NULL,
     NULL },
   { "bpp",		NULL,			rc_int,		&options.color_depth,
     "0",		0,			0,		video_verify_bpp,
     "Specify the colordepth the core should render, one of: auto(0), 8, 16" },
   { "heightscale",	NULL,			rc_float,	&heightscale_f,
     "1",		0.5,			5.0,		video_verify_scale,
     "Set Y-Scale aspect ratio" },
   { "widthscale",	NULL,			rc_float,	&widthscale_f,
     "1",		0.5,			5.0,		video_verify_scale,
     "Set X-Scale aspect ratio" },
   { "scale",		NULL,			rc_use_function, NULL,
     NULL,		0,			0,		video_handle_scale,
     "Set X-Y Scale to the same aspect ratio. For vector games scale (and also width- and heightscale) may have value's like 1.5 and even 0.5. For scaling of regular games this will be rounded to an int" },
   { "autodouble",	"noautodouble",		rc_bool,	&use_auto_double,
     "1",		0,			0,		NULL,
     "Enable/disable automatic scale doubling for 1:2 pixel aspect ratio games" },
   { "dirty",		"nodirty",		rc_bool,	&use_dirty,
     "1",		0,			0,		NULL,
     "Enable/disable use of dirty rectangles" },
   { "scanlines",	"noscanlines",		rc_bool,	&use_scanlines,
     "0",		0,			0,		NULL,
     "Enable/disable displaying simulated scanlines" },
   { "artwork",		"noartwork",		rc_bool,	&options.use_artwork,
     "1",		0,			0,		NULL,
     "Use/don't use artwork if available" },
   { "frameskipper",	NULL,			rc_int,		&frameskipper,
     "0",		0,			FRAMESKIP_DRIVER_COUNT-1, NULL,
     "Select which autoframeskip and throttle routines to use. Available choices are:\n0 Dos frameskip code\n1 Enhanced frameskip code by William A. Barath" },
   { "throttle",	"nothrottle",		rc_bool,	&throttle,
     "1",		0,			0,		NULL,
     "Enable/disable throttle" },
   { "sleepidle",	"nosleepidle",		rc_bool,	&sleep_idle,
     "0",		0,			0,		NULL,
     "Enable/disable sleep during idle" },
   { "autoframeskip",	"noautoframeskip",	rc_bool,	&autoframeskip,
     "1",		0,			0,		NULL,
     "Enable/disable autoframeskip" },
   { "maxautoframeskip", NULL,			rc_int,		&max_autoframeskip,
     "8",		0,			FRAMESKIP_LEVELS-1, NULL,
     "Set highest allowed frameskip for autoframeskip" },
   { "frameskip",	NULL,			rc_int,		&frameskip,
     "0",		0,			FRAMESKIP_LEVELS-1, NULL,
     "Set frameskip when not using autoframeskip" },
   { "brightness",	NULL,			rc_int,		&brightness,
     "100",		0,			100,		NULL,
     "Set the brightness (0-100%%)" },
   { "gamma-correction", NULL,			rc_float,	&gamma_correction,
     "1.0",		0.5,			2.0,		NULL,
     "Set the gamma-correction (0.5-2.0)" },
   { "norotate",	NULL,			rc_set_int,	&options.norotate,
     NULL,		1,			0,		NULL,
     "Disable rotation" },
   { "ror",		NULL,			rc_set_int,	&options.ror,
     NULL,		1,			0,		NULL,
     "Rotate display 90 degrees rigth" },
   { "rol",		NULL,			rc_set_int,	&options.rol,
     NULL,		1,			0,		NULL,
     "Rotate display 90 degrees left" },
   { "flipx",		NULL,			rc_set_int,	&options.flipx,
     NULL,		1,			0,		NULL,
     "Flip X axis" },
   { "flipy",		NULL,			rc_set_int,	&options.flipy,
     NULL,		1,			0,		NULL,
     "Flip Y axis" },
   { "Vector Games Related", NULL,		rc_seperator,	NULL,
     NULL,		0,			0,		NULL,
     NULL },
   { "vectorres",	NULL,			rc_string,	&vector_res,
     NULL,		0,			0,		NULL,
     "Always scale vectorgames to XresxYres, keeping their aspect ratio. This overrides the scale options" },
   { "beam",		NULL,			rc_float,	&beam_f,
     "1.0",		1.0,			16.0,		video_verify_beam,
     "Set the beam size for vector games" },
   { "flicker",		NULL,			rc_float,	&flicker_f,
     "0.0",		0.0,			100.0,		video_verify_flicker,
     "Set the flicker for vector games" },
   { "antialias",	"noantialias",		rc_bool,	&options.antialias,
     "1",		0,			0,		NULL,
     "Enable/disable antialiasing" },
   { "translucency",	"notranslucency",	rc_bool,	&options.translucency,
     "1",		0,			0,		NULL,
     "Enable/disable tranlucency" },
   { NULL,		NULL,			rc_link,	display_opts,
     NULL,		0,			0,		NULL,
     NULL },     
   { NULL,		NULL,			rc_end,		NULL,
     NULL,		0,			0,		NULL,
     NULL }
};

static int video_handle_scale(struct rc_option *option, const char *arg,
   int priority)
{
   if (rc_set_option2(video_opts, "widthscale", arg, priority))
      return -1;
   if (rc_set_option2(video_opts, "heightscale", arg, priority))
      return -1;
      
   option->priority = priority;
   
   return 0;
}

static int video_verify_scale(struct rc_option *option, const char *arg,
   int priority)
{
   int scale = *(float *)option->dest;
   
   if (scale < 1)
      scale = 1;
   
   /* widthscale or heightscale? */
   if (!strcmp(option->name, "widthscale"))
      widthscale = scale;
   else
      heightscale = scale;

   option->priority = priority;

   return 0;
}

static int video_verify_beam(struct rc_option *option, const char *arg,
   int priority)
{
   options.beam = (int)(beam_f * 0x00010000);
   if (options.beam < 0x00010000)
      options.beam = 0x00010000;
   else if (options.beam > 0x00100000)
      options.beam = 0x00100000;

   option->priority = priority;

   return 0;
}

static int video_verify_flicker(struct rc_option *option, const char *arg,
   int priority)
{
   options.flicker = (int)(flicker_f * 2.55);
   if (options.flicker < 0)
      options.flicker = 0;
   else if (options.flicker > 255)
      options.flicker = 255;

   option->priority = priority;

   return 0;
}

static int video_verify_bpp(struct rc_option *option, const char *arg,
   int priority)
{
   if( (options.color_depth != 0) &&
       (options.color_depth != 8) &&
       (options.color_depth != 16) )
   {
      options.color_depth = 0;
      fprintf(stderr, "error: invalid value %s, for bpp\n", arg);
      return -1;
   }

   option->priority = priority;

   return 0;
}

/* Create a bitmap. Also calls osd_clearbitmap() to appropriately initialize */
/* it to the background color. */
/* VERY IMPORTANT: the function must allocate also a "safety area" 16 pixels wide all */
/* around the bitmap. This is required because, for performance reasons, some graphic */
/* routines don't clip at boundaries of the bitmap. */
struct osd_bitmap *osd_new_bitmap(int width,int height,int depth)       /* ASG 980209 */
{
	struct osd_bitmap *bitmap;

	if (!width) width++;
	if (!height) height++;

	if (Machine->orientation & ORIENTATION_SWAP_XY)
	{
		int temp;

		temp = width;
		width = height;
		height = temp;
	}

	if ((bitmap = malloc(sizeof(struct osd_bitmap))) != 0)
	{
		int i,rowlen,rdwidth;
		unsigned char *bm;

		if (depth != 8 && depth != 16) depth = 8;

		bitmap->depth = depth;
		bitmap->width = width;
		bitmap->height = height;

		rdwidth = (width + 7) & ~7;     /* round width to a quadword */
		if (depth == 16)
			rowlen = 2 * (rdwidth + 2 * safety) * sizeof(unsigned char);
		else
			rowlen =     (rdwidth + 2 * safety) * sizeof(unsigned char);

		if ((bm = malloc((height + 2 * safety) * rowlen)) == 0)
		{
			free(bitmap);
			return 0;
		}

		if ((bitmap->line = malloc((height + 2 * safety) * sizeof(unsigned char *))) == 0)
		{
			free(bm);
			free(bitmap);
			return 0;
		}

		for (i = 0;i < height + 2 * safety;i++)
		{
			if (depth == 16)
				bitmap->line[i] = &bm[i * rowlen + 2*safety];
			else
				bitmap->line[i] = &bm[i * rowlen + safety];
		}
		bitmap->line += safety;

		bitmap->_private = bm;

		osd_clearbitmap(bitmap);
	}

	return bitmap;
}

void osd_free_bitmap(struct osd_bitmap *bitmap)
{
	if (bitmap)
	{
		bitmap->line -= safety;
		free(bitmap->line);
		free(bitmap->_private);
		free(bitmap);
		bitmap = NULL;
	}
}

/* set the bitmap to black */
void osd_clearbitmap(struct osd_bitmap *bitmap)
{
	int i;

	memset (bitmap->_private, 0, (bitmap->line[1] - bitmap->line[0]) *
	   (bitmap->height + 2 * safety));

	if (bitmap == Machine->scrbitmap)
	{
		bitmap_dirty = 1;
		osd_mark_dirty (0,0,bitmap->width-1,bitmap->height-1,1);
	}
}

struct osd_bitmap *osd_create_display(int width, int height, int depth,
   int attributes)
{
   int i;
   
   if (Machine->drv->video_attributes & VIDEO_TYPE_VECTOR)
   {
      int vector_width, vector_height;
      if(vector_res &&
         sscanf(vector_res, "%dx%d", &vector_width, &vector_height) == 2)
      {
         if( Machine->orientation & ORIENTATION_SWAP_XY)
         {
            widthscale_f  = (float)vector_width  / height;
            heightscale_f = (float)vector_height / width;
         }
         else
         {
            widthscale_f  = (float)vector_width  / width;
            heightscale_f = (float)vector_height / height;
         }
         if (widthscale_f > heightscale_f)
            widthscale_f  = heightscale_f;
         else
            heightscale_f = widthscale_f;
         fprintf(stderr_file, "Vectorres %dx%d, scale = %f\n",
            vector_width, vector_height, heightscale_f);
      }
      width  *= widthscale_f;
      height *= heightscale_f;
      widthscale = heightscale = 1;
      /* round with & heigth to a multiple of 8 */
      width  &= ~7;
      height &= ~7;
      /* store info into a visual struct */
      visual.min_x = 0;
      visual.min_y = 0;
      visual.max_x = width - 1;
      visual.max_y = height - 1;
   }
   else
      /* we use the same struct as the core, but under a different name,
         to avoid header conflicts */
      memcpy(&visual, &Machine->drv->visible_area, sizeof(struct my_rectangle));
     
   if (!(bitmap = osd_new_bitmap(width,height, depth)))
      return NULL;
   
   if( Machine->orientation & ORIENTATION_SWAP_XY) {
      i=visual.max_x; visual.max_x=visual.max_y; visual.max_y=i;
      i=visual.min_x; visual.min_x=visual.min_y; visual.min_y=i;
      i=width; width=height; height=i;
   } 

   if (Machine->orientation & ORIENTATION_FLIP_X)
   {
      i            = width - visual.min_x - 1;
      visual.min_x = width - visual.max_x - 1;
      visual.max_x = i;
   }
   
   if (Machine->orientation & ORIENTATION_FLIP_Y)
   {
      i            = height - visual.min_y - 1;
      visual.min_y = height - visual.max_y - 1;
      visual.max_y = i;
   }
   
   /* Can we do dirty? First check if its a vector game */
   if (Machine->drv->video_attributes & VIDEO_TYPE_VECTOR)
   {
      if (use_dirty) use_dirty  = 2;
   }
   else if ( (Machine->drv->video_attributes & VIDEO_SUPPORTS_DIRTY) == 0 )
   {
      use_dirty = FALSE;
   }
   
   if(use_auto_double &&
      (Machine->drv->video_attributes & VIDEO_PIXEL_ASPECT_RATIO_MASK) ==
      VIDEO_PIXEL_ASPECT_RATIO_1_2)
   {
      if (Machine->orientation & ORIENTATION_SWAP_XY)
         widthscale  *= 2;
      else
         heightscale *= 2;
   }
  
   /* round to 8, since the new dirty code works with 8x8 blocks,
      and we need to round to sizeof(long) for the long copies anyway */
   if (visual.min_x & 7)
   {
      if((visual.min_x - (visual.min_x & ~7)) < 4)
         visual.min_x &= ~7;
       else
         visual.min_x = (visual.min_x + 7) & ~7;
   }
   if ((visual.max_x+1) & 7)
   {
      if(((visual.max_x+1) - ((visual.max_x+1) & ~7)) > 4)
         visual.max_x = ((visual.max_x+1 + 7) & ~7) - 1;
       else
         visual.max_x = ((visual.max_x+1) & ~7) - 1;
   }

   /* rounding of the y-coordinates is only nescesarry when we are doing dirty */
   if (use_dirty)
   {
      if (visual.min_y & 7)
      {
         if((visual.min_y - (visual.min_y & ~7)) < 4)
            visual.min_y &= ~7;
          else
            visual.min_y = (visual.min_y + 7) & ~7;
      }
      if ((visual.max_y+1) & 7)
      {
         if(((visual.max_y+1) - ((visual.max_y+1) & ~7)) > 4)
            visual.max_y = ((visual.max_y+1 + 7) & ~7) - 1;
          else
            visual.max_y = ((visual.max_y+1) & ~7) - 1;
      }
   }
   
   /* now calculate the visual width / height */
   visual_width  = visual.max_x - visual.min_x + 1;
   visual_height = visual.max_y - visual.min_y + 1;

#if !defined xgl
   if (osd_dirty_init()!=OSD_OK) return NULL;
#endif
   
   if (sysdep_create_display() != OSD_OK)
      return NULL;
   
   /* a lott of display_targets need to have the display initialised before
      initialising any input devices */
   if (osd_input_initpost()!=OSD_OK) return NULL;
   
   set_ui_visarea (visual.min_x, visual.min_y, visual.max_x, visual.max_y);
   
   if (use_dirty)   fprintf(stderr_file,"Using dirty_buffer strategy\n");
   if (bitmap->depth==16) fprintf(stderr_file,"Using 16bpp video mode\n");
   
   /* for debugging only */
   fprintf(stderr_file, "width= %d, height = %d, viswidth = %d, visheight = %d,"
           "visstartx= %d, visstarty= %d\n",
            width, height, visual_width, visual_height, visual.min_x,
            visual.min_y);
   
   return bitmap;
}   

int osd_allocate_colors(unsigned int totalcolors, const unsigned char *palette,
   unsigned short *pens, int modifiable)
{
   int i;
   int color_start = 0;
   int writable_colors = 0;
   int max_colors = (bitmap->depth == 8)? 256:65536;
   
   if (totalcolors > max_colors)
   {
      fprintf(stderr_file,
         "Warning: More than %d colors (%d) are needed for this emulation,\n"
         "some parts of the screen may be corrupted\n", max_colors, 
         totalcolors);
      /* fill the remainder of the pens array with 0's to make sure */
      /* nothing strange happens                                    */
      for (i=max_colors; i<totalcolors; i++)
         pens[i] = 0;
      totalcolors = max_colors;
   }
   else
      fprintf(stderr_file, "Game uses %d colors\n", totalcolors);

   if ((bitmap->depth == 8) || modifiable)
   {
      writable_colors = totalcolors + 2;
      if (writable_colors > max_colors)
         writable_colors = max_colors;
   }
   
   /* alloc the sysdep_palette */
   if(!(sysdep_palette = sysdep_palette_create(bitmap->depth,
      writable_colors)))
      return 1;
      
   sysdep_palette_set_gamma(sysdep_palette, gamma_correction);
   sysdep_palette_set_brightness(sysdep_palette, brightness * brightness_paused_adjust);
   
   /* init the palette */
   if (writable_colors)
   {
      int color_start = (totalcolors < max_colors)? 1:0;

      for (i=0; i<totalcolors; i++)
      {
         pens[i] = i+color_start;
         sysdep_palette_set_pen(sysdep_palette, i+color_start, palette[i*3],
            palette[i*3+1], palette[i*3+2]);
      }
      if(color_start)
         sysdep_palette_set_pen(sysdep_palette, 0, 0, 0, 0);
      if( writable_colors > (totalcolors+color_start) )
         sysdep_palette_set_pen(sysdep_palette, writable_colors - 1, 0xFF, 0xFF,
            0xFF);
      Machine->uifont->colortable[0] = 0;
      Machine->uifont->colortable[1] = writable_colors - 1;
      Machine->uifont->colortable[2] = writable_colors - 1;
      Machine->uifont->colortable[3] = 0;
   }
   else
   {
      for (i=0; i<totalcolors; i++)
      {
         pens[i] = sysdep_palette_make_pen(sysdep_palette, palette[i*3],
            palette[i*3+1], palette[i*3+2]);
      }
      Machine->uifont->colortable[0] = sysdep_palette_make_pen(sysdep_palette,
         0, 0, 0);
      Machine->uifont->colortable[1] = sysdep_palette_make_pen(sysdep_palette,
         0xFF, 0xFF, 0xFF);
      Machine->uifont->colortable[2] = sysdep_palette_make_pen(sysdep_palette,
         0xFF, 0xFF, 0xFF);
      Machine->uifont->colortable[3] = sysdep_palette_make_pen(sysdep_palette,
         0, 0, 0);
   }
   return 0;
}

void osd_get_pen(int pen,unsigned char *red, unsigned char *green, unsigned char *blue)
{
    sysdep_palette_get_pen(sysdep_palette, pen, red, green, blue);
}

void osd_modify_pen(int pen, unsigned char red,unsigned char green,unsigned char blue) 
{
   sysdep_palette_set_pen(sysdep_palette, pen, red, green, blue);
}

static int skip_next_frame = 0;

typedef int (*skip_next_frame_func)(int show_fps_counter);

static skip_next_frame_func skip_next_frame_functions[FRAMESKIP_DRIVER_COUNT] =
{
   dos_skip_next_frame,
   barath_skip_next_frame
};

int osd_skip_this_frame(void)
{
   return skip_next_frame;
}

/* Update the display. */
void osd_update_video_and_audio(void)
{
   int i;
   static int showfps=0, showfpstemp=0; 
   int skip_this_frame;
   int need_to_clear_bitmap=0;
   
   if (input_ui_pressed(IPT_UI_FRAMESKIP_INC))
   {
      if (autoframeskip)
      {
	 autoframeskip = 0;
	 frameskip = 0;
      }
      else
      {
	 if (frameskip == FRAMESKIP_LEVELS-1)
	 {
	    frameskip = 0;
	    autoframeskip = 1;
	 }
	 else frameskip++;
      }

      if (showfps == 0) showfpstemp = 2 * Machine->drv->frames_per_second;
   }

   if (input_ui_pressed(IPT_UI_FRAMESKIP_DEC))
   {
      if (autoframeskip)
      {
	 autoframeskip = 0;
	 frameskip = FRAMESKIP_LEVELS-1;
      }
      else
      {
	 if (frameskip == 0) autoframeskip = 1;
	 else frameskip--;
      }

      if (showfps == 0)	showfpstemp = 2 * Machine->drv->frames_per_second;
   }

   if (!keyboard_pressed(KEYCODE_LSHIFT) && !keyboard_pressed(KEYCODE_RSHIFT)
       && !keyboard_pressed(KEYCODE_LCONTROL) && !keyboard_pressed(KEYCODE_RCONTROL)
       && input_ui_pressed(IPT_UI_THROTTLE))
   {
      throttle ^= 1;
   }

   if (input_ui_pressed(IPT_UI_THROTTLE) && (keyboard_pressed(KEYCODE_RSHIFT) || keyboard_pressed(KEYCODE_LSHIFT)))
   {
      sleep_idle ^= 1;
   }

   if (!keyboard_pressed(KEYCODE_LSHIFT) && !keyboard_pressed(KEYCODE_RSHIFT)
       && !keyboard_pressed(KEYCODE_LCONTROL) && !keyboard_pressed(KEYCODE_RCONTROL)
       && input_ui_pressed(IPT_UI_SHOW_FPS))
   {
      if (showfpstemp)
      {
	 showfpstemp = 0;
	 need_to_clear_bitmap = 1;
      }
      else
      {
	 showfps ^= 1;
	 if (showfps == 0)
	 {
	    need_to_clear_bitmap = 1;
	 }
      }
   }

   if (keyboard_pressed (KEYCODE_LCONTROL))
   {
      if (keyboard_pressed_memory (KEYCODE_INSERT))
         frameskipper = 0;
      if (keyboard_pressed_memory (KEYCODE_HOME))
         frameskipper = 1;
   }
   
   if (showfpstemp)         /* MAURY_BEGIN: nuove opzioni */
   {
      showfpstemp--;
      if (showfpstemp == 0) need_to_clear_bitmap = 1;
   }

   skip_this_frame = skip_next_frame;
   skip_next_frame =
      (*skip_next_frame_functions[frameskipper])(showfps || showfpstemp);
   
   if (skip_this_frame == 0)
   {
      profiler_mark(PROFILER_BLIT);
      sysdep_palette_update(sysdep_palette);
      sysdep_update_display();
      profiler_mark(PROFILER_END);
   }
   
   if (sound_stream && sound_enabled)
      sound_stream_update(sound_stream);

   if (need_to_clear_bitmap) osd_clearbitmap(bitmap);
}

void osd_set_gamma(float gamma)
{
   sysdep_palette_set_gamma(sysdep_palette, gamma);
}

float osd_get_gamma(void)
{
   return sysdep_palette_get_gamma(sysdep_palette);
}

/* brightess = percentage 0-100% */
void osd_set_brightness(int _brightness)
{
   brightness = _brightness;
   sysdep_palette_set_brightness(sysdep_palette, brightness *
      brightness_paused_adjust);
}

int osd_get_brightness(void)
{
   return brightness;
}

void osd_save_snapshot(void)
{
   save_screen_snapshot();
}

void osd_pause(int paused)
{
   if (paused)
      brightness_paused_adjust = 0.65;
   else
      brightness_paused_adjust = 1.0;

   sysdep_palette_set_brightness(sysdep_palette, brightness *
      brightness_paused_adjust);
}
