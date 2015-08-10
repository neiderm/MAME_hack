/*
 * stubs for unresolved symbols
 */


/*
 * These are workarounds for cutting DirectX from Win32 osd and arguably
 * might belong in winmain.c
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

