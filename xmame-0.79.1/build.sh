#!/bin/bash

# cat patch.txt  | patch -p1 --dry-run

# Xubuntu-14.04: requires patch x11_windows.c for "transparency issue", sound is very broken
#make -f makefile.unix  SHELL='sh -x'  MY_CPU=amd64  DISPLAY_METHOD=x11 SOUND_ALSA=1 LDFLAGS='' 

# Xubuntu-14.04: sound is very broken
# make -f makefile.unix  SHELL='sh -x'   DISPLAY_METHOD=SDL SOUND_SDL=1 LDFLAGS=''

# Xubuntu-20.04: SDL sound is not great until .92
# make -f makefile.unix  SHELL='sh -x'   DISPLAY_METHOD=SDL SOUND_SDL=1 LDFLAGS=''

# Xubuntu-20.04: requires patch x11_windows.c for "transparency issue", SDL sound is not great until .92
# make -f makefile.unix  SHELL='sh -x'  MY_CPU=amd64  DISPLAY_METHOD=x11 SOUND_SDL=1 LDFLAGS=''

# Xubuntu-20.04: sound OK
# make -f makefile.unix  SHELL='sh -x'  MY_CPU=amd64  DISPLAY_METHOD=SDL SOUND_ALSA=1 LDFLAGS=''
make -f makefile.unix  SHELL='sh -x'  MY_CPU=amd64  DISPLAY_METHOD=x11 SOUND_ALSA=1 LDFLAGS=''


# Preprocessor defines:

# INLINE="static __inline__"
# LSB_FIRST
# x11
# stricmp=strcasecmp
# strnicmp=strncasecmp
# UNIX
# SOUND_ALSA=1
# HAS_NAMCO
# HAS_NAMCO_52XX
# HAS_NAMCO_54XX
# HAS_SAMPLES
# HAS_Z80
# HAS_SN76496=1
# HAS_AY8910=1
# NAME=\'"xmame"\'
# DISPLAY_METHOD=\'"x11"\'
# XMAMEROOT=\'"/usr/local/share/xmame"\'
# SYSCONFDIR=\'"/usr/local/share/xmame"\'
# SYSDEP_DSP_ALSA
# TINY_COMPILE=1
 
