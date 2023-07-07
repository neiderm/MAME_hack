#!/bin/bash
#cat patch.txt | patch -p1 --dry-ru
#make -f makefile.unix DISPLAY_METHOD=x11
make -f makefile.unix SHELL='sh -x'  MY_CPU=amd64  SOUND_ALSA=1 
