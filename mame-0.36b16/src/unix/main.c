/*
 * X-mame main-routine
 */

#define __MAIN_C_
#include "xmame.h"

/* put here anything you need to do when the program is started. Return 0 if */
/* initialization was successful, nonzero otherwise. */
int osd_init(void)
{
	/* now invoice system-dependent initialization */
#ifdef MAME_NET
	if (osd_net_init()      !=OSD_OK) return OSD_NOT_OK;
#endif	
	if (osd_input_initpre() !=OSD_OK) return OSD_NOT_OK;
	
	return OSD_OK;
}

/*
 * Cleanup routines to be executed when the program is terminated.
 */
void osd_exit (void)
{
#ifdef MAME_NET
	osd_net_close();
#endif
	osd_input_close();
}


int main (int argc, char **argv)
{
	int res;
	
	/* some display methods need to do some stuff with root rights */
	if (sysdep_init()!= OSD_OK) exit(OSD_NOT_OK);
	
	/* to be absolutly safe force giving up root rights here in case
	   a display method doesn't */
	if(setuid(getuid()))
	{
		perror("setuid");
		sysdep_close();
		return OSD_NOT_OK;
	}
	
        /* Set the title, now auto build from defines from the makefile */
        sprintf(title,"%s (%s) version %s", NAME, DISPLAY_METHOD,
           build_version);

	/* parse configuration file and environment */
	if ((res = config_init(argc, argv)) != 1234) goto leave;
	
        /* Check the colordepth we're requesting */
        if (!options.color_depth && !sysdep_display_16bpp_capable())
           options.color_depth = 8;
	
	/* go for it */
	res = run_game (game_index);

leave:
	sysdep_close();
	/* should be done last since this also closes stdout and stderr */
	config_exit();

	return res;
}
