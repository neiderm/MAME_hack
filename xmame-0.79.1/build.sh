#!/bin/bash

# cat patch.txt  | patch -p1 --dry-run

make -f makefile.unix  SHELL='sh -x'  MY_CPU=amd64  DISPLAY_METHOD=x11 SOUND_ALSA=1 LDFLAGS='' 


