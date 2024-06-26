#include <math.h>
#include "xmame.h"
#include "driver.h"
#include "profiler.h"
#include "sysdep/misc.h"
//#include "usrintrf.h" /* RB */
/* don't define this for a production version
#define barath_debug
 */

static int modframe = 0;

static int barath_skip_this_frame(void)
{
  return (modframe >= FRAMESKIP_LEVELS);
}

int barath_skip_next_frame(int showfps /* , struct osd_bitmap *bitmap */)
{
  static uclock_t curr = 0;
  static uclock_t prev = 0;
  static uclock_t avg_uclocks = 0;
  static int frames_skipped = 0;
  static int sysload = 0;
  static float framerate = 1;
  static float speed = 1;
  static float lag_rate = -30;

  int skip_this_frame = barath_skip_this_frame();
  int scratch_time = uclock();
#ifdef barath_debug
  int debug_value;
  static float slow_speed = 1;
  int uclocks_per_frame = slow_speed * UCLOCKS_PER_SEC / Machine->drv->frames_per_second;
#else
  int uclocks_per_frame = UCLOCKS_PER_SEC / Machine->drv->frames_per_second;
#endif
  /* project target display time of this frame */
  uclock_t target = prev + (frames_skipped + 1) * uclocks_per_frame;

  /* if lagging by more than 2 frames don't try to make up for it */
  while (scratch_time - target > uclocks_per_frame * 2) {
    target += uclocks_per_frame;
    lag_rate++;
  }
  lag_rate *= 0.99;

  {
    static float framerateavg = 0;
    framerateavg = (framerateavg * 5 + 1 - skip_this_frame) / 6.0;
    framerate = (framerate * 5 + framerateavg) / 6.0;
  }
  if (throttle) {
    int leading = ((sysload > 33) && sleep_idle) ? 0 : uclocks_per_frame;
    int sparetime = target - scratch_time;

    /* test for load-induced lags and set sysload */
    if (autoframeskip && sleep_idle) {
      /* if lag is excessive and framerate is low then we have a system hiccup */
      if ((sysload < 100) && (lag_rate > 3) && (frameskip < max_autoframeskip)) {
	sysload++;
	lag_rate = 3;
      }
      /* after ~2000 frames of no lag start lowering sysload */
      else if (sysload && (fabs(lag_rate) < .00001)) {
	sysload--;
	lag_rate = .000011;	/* wait ~10 frames */
      }
    }
    if (autoframeskip) {
      /* this is an attempt at proportionate feedback to smooth things out */
      int feedback = ((sparetime - uclocks_per_frame / 2) / (uclocks_per_frame / 3));

      frameskip = ((1.0 - framerate) * (FRAMESKIP_LEVELS - 1)) - feedback;

#ifdef barath_debug
      debug_value = feedback;
#endif
      if (frameskip > max_autoframeskip)
	frameskip = max_autoframeskip;
      else if (frameskip < 0)
	frameskip = 0;
    }
    if (sparetime > 0) {
      /* if we're more than 2 frames ahead we need to resynch */
      if (sparetime > uclocks_per_frame * 2)
	target = scratch_time;
      else {
	/* idle until we hit frame ETA or leading */
	profiler_mark(PROFILER_IDLE);
	while (target - uclock() > leading)
	  if (sleep_idle)
	    usleep(100);
	profiler_mark(PROFILER_END);
      }
    }
    /* if we are behind we should force a skip: */
    else if (autoframeskip && (frameskip < max_autoframeskip)
	     && (frames_skipped < 1))
      modframe = FRAMESKIP_LEVELS * 2 - frameskip;

  }				/* if (throttle) */
  if (skip_this_frame && (frames_skipped < FRAMESKIP_LEVELS))
    frames_skipped++;
  else {
    /* update frame timer */
    prev = target;

    /* calculate average running speed for display purposes */
    scratch_time = curr;
    curr = uclock();
    avg_uclocks = (avg_uclocks * 5 + curr - scratch_time) / (6 + frames_skipped);
    speed = (speed * 5 + (float) uclocks_per_frame / avg_uclocks) / 6.0;
    /* double-forward average  */

    if (showfps) {
      static char buf[80] = "";
      static int showme = 0;

      if (showme++ > 5) {
	int fps = (Machine->drv->frames_per_second * framerate * speed + .5);
#ifdef barath_debug
	sprintf(buf, "%2d %d %s%s%s%2d %3d%%(%3d/%3d)", debug_value, sysload,
		throttle ? "T" : "", (throttle && sleep_idle) ? "S" : "",
		(throttle && autoframeskip) ? "A" : "F", frameskip,
		(int) (speed * 100 + .5), (int) (fps / slow_speed),
		(int) (Machine->drv->frames_per_second / slow_speed));

	/* set game speed based on manual frameskip setting */
	if (!throttle && !autoframeskip)
	  slow_speed = (.25 + 3 * frameskip / (float) FRAMESKIP_LEVELS);
#else
	sprintf(buf, " %s%s%sfskp%2d %3d%%(%2d/%d fps)",
	      throttle ? "T " : "", (throttle && sleep_idle) ? "S " : "",
		(throttle && autoframeskip) ? "auto" : "", frameskip,
	 (int) (speed * 100 + .5), fps, (int)Machine->drv->frames_per_second);
#endif
	showme = 0;
      }
      ui_text(buf, Machine->uiwidth - strlen(buf) * Machine->uifontwidth, 0);
    }
    frames_skipped = 0;
  }

  /* give a little grace in case something else sets it off */
  if (sleep_idle && autoframeskip && (sysload > 33)) {
    profiler_mark(PROFILER_IDLE);
    usleep(100);
    profiler_mark(PROFILER_END);
  }
  /* advance frameskip counter */
  if (modframe >= FRAMESKIP_LEVELS)
    modframe -= FRAMESKIP_LEVELS;
  modframe += frameskip;

  return barath_skip_this_frame();
}
