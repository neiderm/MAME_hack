/*
 * stubs for unresolved symbols
 */ 


/*
 * vector stuff referenced in onscrd_vector_intensity()
 * from src/vidhrdw/vector.c
 */
float vector_get_intensity(void)
{
  return 1.0;
}

void vector_set_intensity(float _intensity)
{
}

/*
 * from src/vidhrdw/avgdvg.c
 */
int vector_updates; /* referenced in  Throttle(void)  */

//#include <windef.h> // DWORD

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

