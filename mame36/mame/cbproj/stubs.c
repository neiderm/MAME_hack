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
int vector_updates; // referenced in  Throttle(void)

//#include <windef.h> // DWORD

/*
 * These are needed to get around DirectX
 */
#include "options.h" // options_type
#include "display.h" // OSDDisplay 
struct OSDDisplay DDrawDisplay;

#include "sound.h" // OSDSound
struct OSDSound DirectSound;

#include "keyboard.h" // OSDKeyboard
struct OSDKeyboard  DIKeyboard;

#include "joystick.h" // OSDJoystick  
struct OSDJoystick  DIJoystick;
