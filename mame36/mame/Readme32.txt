                 M.A.M.E.  -  Multiple Arcade Machine Emulator
          Copyright (C) 1997-2000 by Nicola Salmoria and The MAME Team

                 MAME32 Copyright (C) 1997-2000 by The MAME32 team.


                          MAME32 Release Notes
                          --------------------

This is release 0.36 MAME32, the Multiple Arcade Machine Emulator for Win32.

MAME32 is simple to use--put zipped ROM files in a roms subdirectory,
zipped sample files in a samples subdirectory, and run MAME32.
MAME32 requires DirectX 3.0 or higher to be installed on your system.
If you need DirectX, go to http://www.microsoft.com/directx and download
the latest DirectX runtime (version 7) for Windows 95/98.
If you use Windows NT 4.0, install Service Pack 3 or higher.


Requirements
------------

- Windows 95, Windows 98, Windows NT 4.0 or Windows 2000.
- DirectX version 3.0 or higher.
- Pentium class cpu.


Acknowledgements
----------------
Thanks to John Hardy IV for excellent testing.
Also, thanks to Mike Haaland, Jeff Miller, Andrew Kirmse,
Mohammad Rezaei and Robert Schlabbach for contributing code to MAME32.


Usage
-----

MAME32 [name of the game to run] [options]

options:
--------
-resolution XxY
              Where X and Y are width and height (ex: '-resolution 800x600')
              MAME goes some lengths to autoselect a good resolution. You can
              override MAME's choice with this option. You can omit the
              word "resolution" and simply use -XxY (e.g. '-800x600') as a
              shortcut. Frontend authors are advised to use -resolution XxY,
              however.

-skiplines N / -skipcolumns N
              If you run a game in a video mode smaller than the visible area,
              you can adjust its position using the PgUp and PgDn keys (alone
              for vertical panning, shifted for horizontal panning). You can
              also use these two parameters to set the initial position: 0 is
              the default, meaning that the screen is centered. You can specify
              both positive and negative offsets.

-scanlines/-noscanlines (default: -scanlines)
              Scanlines are small, evenly-spaced, horizontal blank lines that
              are typical of real arcade monitors. If you don't prefer this
              "authentic" look, turn scanlines off.

-double/-nodouble (default: double)
              Use nodouble to disable pixel doubling (faster, but smaller picture).
              Use double to force pixel doubling when the image doesn't fit in
              the screen (you'll have to use PGUP and PGDN to scroll).

-depth n      (default: auto)
              Some games need 16-bit color to get accurate graphics. To improve
              speed, you can use '-depth 8', which limits the display to
              standard 256-color mode. (You can also use '-depth 16' to force
              256-color games to use 16-bit color, but this isn't recommended.)

-gamma n      (Default is 1.0)
              Sets the initial gamma correction value.

-vsync/-novsync (default: -novsync)       
              Synchronize video display with the video beam instead of using
              the timer. 

-ror          Rotates the display clockwise by 90 degrees.
-rol          Rotates display anticlockwise.
-flipx        Flips display horizontally.
-flipy        Flips display vertically.
              -ror and -rol provide authentic *vertical* scanlines, given that you
              have turned your monitor on its side.
              CAUTION:
              Monitors are complicated, high-voltage electronic devices.
              Some monitors are designed to be rotated. If yours is _not_ one
              of them, but you absolutely must turn it on its side, you do so
              at your own risk.

              *******************************************
              PLEASE DO NOT LEAVE YOUR MONITOR UNATTENDED
              IF IT IS PLUGGED IN AND TURNED ON ITS SIDE!
              *******************************************

-frameskip n  (default: auto)
              Skip frames to speed up the emulation. The argument is the number
              of frames to skip out of 12. For example, if the game normally
              runs at 60 fps, "-frameskip 2" will make it run at 50 fps,
              "-frameskip 6" at 30 fps. Use F11 to check the speed your
              computer is actually reaching. If it is below 100%, increase the
              frameskip value. You can press F9 to change frameskip while
              running the game.
              When set to auto (the default), the frameskip setting is
              dynamically adjusted during run time to display the maximum
              possible frames without dropping below 100% speed.

-antialias/-noantialias (default: -antialias)
              Antialiasing for the vector games.

-beam n       Sets the width in pixels of the vectors. n is a float in the
              range of 1.00 through 16.00.

-flicker n    Make the vectors flicker. n is an optional argument, a float in
              the range range 0.00 - 100.00 (0=none 100=maximum).

-translucency/-notranslucency (default: -translucency)
              Enables or disables vector translucency.

-sr n         Set the audio sample rate. The default is 22050. Smaller values
              (e.g. 11025) cause lower audio quality but faster emulation speed.
              Higher values (e.g. 44100) cause higher audio quality but slower
              emulation speed.

-stereo/-nostereo (default: -stereo)
              Selects stereo or mono output for games supporting stereo sound.

-volume n     (default: 0)
              Sets the startup volume. It can later be changed with the On
              Screen Display (see Keys section). The volume is an attenuation
              in dB: e.g., "-volume -12" will start with -12dB attenuation.

-ym3812opl/-noym3812opl (default: -ym3812opl)
              Uses the SoundBlaster OPL chip for music emulation of the YM3812
              chip. This is faster, and is reasonably accurate, since the chips
              are 100% compatible.  There is no control on the volume, however,
              and you need a real OPL chip for it to work  (If you are using an
              SB-compatible card that emulates the OPL in software, the built-in
              digital emulation will probably sound better).
              On NT4.0, you will need to install mameopl.sys for the -ym3812opl option.

-joy/-nojoy   (default: -nojoy)
              Allows joystick input.
              Use the Windows control panel to calibrate the joystick.

-hotrod       Sets a default keyboard configuration suitable for the HotRod
              joystick by HanaHo Games.

-hotrodse     Sets a default keyboard configuration suitable for the HotRod SE
              joystick by HanaHo Games.

-log          Create a log of illegal memory accesses in ERROR.LOG

-help, -?     Display current MAME version and copyright notice.

-mouse/-nomouse (default: -mouse)
              Enables/disables mouse support.

-cheat        Cheats, like the speedup in Pac Man or the level-skip in many
              other games, are disabled by default. Use this switch to turn
              them on.

-debug        Activates the integrated debugger.
              During emulation, press the Tilde key (~) to activate the
              debugger. This is available only if the program is compiled with
              MAME_DEBUG defined.

-nosamples    Turn off sample loading.

-noartwork    Turn off artwork loading.


MAME32 specific options. All the above plus:
--------------------------------------------
-noddraw      Uses Windows GDI to display in a window instead of using DirectDraw.
-window       Display in a window. The opposite of -screen.
-screen       Display fullscreen (default). The opposite of -window.
-nosound      Turn off audio.
-midas        Use the MIDAS Digital Audio System for audio. Try this option
              if the DirectSound audio sounds choppy or slows down MAME32. This can
              happen if your audio drivers don't provide DirectSound hardware support.
              This is the best option for Windows NT 4.0 users.
-directsound  Use the sound subsystem which uses the DirectSound API.
-vscanlines/-novscanlines
              Use vertical scanlines. Simulates scanlines of vertical monitors.
-quit         Quit after running the first game. Useful when specifying a game on the command line.
-noautopause  Disables pausing the game when MAME32 loses focus.
-useblit      Use a BitBlit to transfer image data to the screen in fullscreen mode.
              This only applies to the double option with no scanlines.
              This may be faster or slower depending on your system.
-nommx        Disable the MMX code.
-nocpudetect  Do not try to detect an MMX processor.
-dikbd        Use DirectInput for keyboard input.
-dijoy        Use DirectInput for joystick input. Only avalible with DirectX 5 or above.
-joygui       Enable the joystick to select games in the UI.
-dijoygui     Use DirectInput for the joystick to select games in the UI.
-ignorebadoptions Allows MAME32 to run with bogus options.

Keys
----
Tab          Toggles the configuration menu.
Tilde        Toggles the On Screen Display.
             Use the up and down arrow keys to select the parameter (global
             volume, mixing level, gamma correction etc.), left and right to
             arrow keys to modify it.
P            Pauses the game.
Shift+P      While paused, advances to next frame.
F3           Resets the game.
F4           Show the game graphics. Use cursor keys to change set/color,
             F4 or Esc to return to the emulation.
F9           Change frame skip on the fly.
F10          Toggles speed throttling.
F11          Toggles speed display.
Shift+F11    Toggles profiler display.
F12          Saves a screen snapshot. The default target directory is 'images'.
ESC          Exits emulator.


Known problems 
--------------

MAME32 may perform poorly under Windows NT. DirectX under NT can be slow
when emulating hardware, especially sound and joysticks. You may get better
performance by disabling sound, joysticks, or by changing video modes. Sorry,
Chris loves NT, but its hardware support of DirectX isn't very fast right now. 

MAME32 may run slow in a window if your desktop is at 24 bit or 
32 bit color depth.  This isn't a problem, it's just a fact--moving around 
that much more video memory takes a long time.  Chris optimized the 16 bit color
depth version a bit, so it's about as fast as it can get. 

Some DirectDraw display drivers don't support locking the primary surface
in fullscreen mode. MAME32 will perform blits from a back buffer in this case.
Note that this is slower than writing directly to the primary surface.

When an error occurs starting a game, a spurious dialog box may appear with the
message that the roms may be corrupt. In most cases, this message can be ignored.

There are some games which use an OPL chip for music. These are identified in the
readme.txt file as requiring a Sound Blaster OPL chip. MAME32 will not produce
music for these games on Windows NT unless you install the mameopl.sys driver or
run MAME32 with administrative privledges.

The joystick mapping settings only work with the DirectInput Joystick option.

Triple buffering may not work on some video cards on NT when in 8 bit mode.

Contacts
--------
Michael Soderstrom:        ichael@geocities.com
Christopher Kirmse         ckirmse@pobox.com
John L. Hardy IV:          mame32qa@yahoo.com
MAME home page:            http://www.mame.net
Michael's MAME32 page:     http://www.classicgaming.com/mame32
Christopher's MAME32 page: http://www.geocities.com/TimesSquare/Lair/8706/mame32.html
John L. Hardy IV's page:   http://www.classicgaming.com/mame32qa
Compiling MAME32 page:     http://www.hypertech.com/mame
MIDAS home page:           http://www.s2.org/midas
SEAL home page:            http://www.egerter.com/seal
