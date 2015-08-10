/*
 * Windows build of MAME (v36) for Windows
 * Compilers supported are MingGW (Code::Blocks) and Visual Studio 2003
 * Based on "src/Win32/win32ui.c" from Mame32UI project
 * 2015 Glenn Neidermeier
 */
#include "driver.h"

#include <windows.h>

#include "options.h"
#include "win32/file.h" /* OSDFile File ... path it to avoid filename conflict
                           in hmqaudio */


/***************************************************************************
    function prototypes
 ***************************************************************************/


/***************************************************************************
    Internal variables
 ***************************************************************************/

/* our dialog/configured options */
static options_type playing_game_options;


/***************************************************************************
    External functions
 ***************************************************************************/

int WINAPI WinMain(HINSTANCE    hInstance,
                   HINSTANCE    hPrevInstance,
                   LPSTR        lpCmdLine,
                   int          nCmdShow)
{
    File.init();

    playing_game_options.is_window = 1;
    playing_game_options.gamma = 1.0;
    playing_game_options.brightness = 100;
    playing_game_options.sound = 1;
    playing_game_options.sample_rate = 22050;
    playing_game_options.has_roms = 1;

/*
 in "run_game()", a bunch of global options are copied to Machine e.g.

        Machne->sample_rate = options.samplerate;

 ... before osd_init(), see 'assert(Machine->sample_rate != 0)' in MidasSound_update_audio_stream()
*/
    options.samplerate  = playing_game_options.sample_rate; // in mame::options

    run_game(0); // index

    File.exit();

    return 0;
}


int UpdateLoadProgress(const char* name, int current, int total)
{
    printf("Loading %s (%d of %d)\n", name, current, total);
    return 0;
}

/*
 this is getter for osdepend::osd_init() ... to be propagated out to various subsystems e.g.
  "MAME32App_init(options)" etc. etc.
 The object "GameOptions mame_options" declared in 'mame.h' and referenced globally numerous core modules:
 primarily usrintrf, mame, but also intport, common, snd/3812intf
*/
options_type * GetPlayingGameOptions()
{
    return &playing_game_options;
}

/*
  these belong in Win32/options.c
*/

char * romdirs     = ".;roms";
char * sampledirs  = ".;samples";
char * cfgdirs     = "cfg";

const char* GetRomDirs(void)
{
    return romdirs;
}

const char* GetSampleDirs(void)
{
    return sampledirs;
}

const char* GetCfgDir(void)
{
    return cfgdirs;
}

/*
 * the following functions are not called but needed to resolve the references
 */
const char* GetHiDir(void)
{
    return 0;
}

const char* GetNvramDir(void)
{
    return 0;
}

const char* GetImgDir(void)
{
    return 0;
}

int GetShowPictType(void)
{
    return 0;
}

const char* GetFlyerDir(void)
{
    return 0;
}

const char* GetCabinetDir(void)
{
    return 0;
}

const char* GetStateDir(void)
{
    return 0;
}

const char* GetArtDir(void)
{
    return 0;
}

const char* GetMemcardDir(void)
{
    return 0;
}

/*
 * dummy symbols for DirectX dependencies 
 */

#include "options.h"  /* options_type */
#include "display.h"  /* OSDDisplay */
struct OSDDisplay DDrawDisplay;  /* from src/Win32/DDrawDisplay.c */

#include "sound.h"  /* OSDSound */
struct OSDSound DirectSound;  /* from src/Win32/DirectSound.c */

#include "keyboard.h"  /* OSDKeyboard */
struct OSDKeyboard  DIKeyboard;  /* from src/Win32/DIKeyboard.c */

#include "joystick.h"  /* OSDJoystick */
struct OSDJoystick  DIJoystick;  /* from src/Win32/DIJoystick.c */

