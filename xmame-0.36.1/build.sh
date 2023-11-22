#!/bin/bash

# todo:
# CB project settings
#  VERSION= 
# makefile.unix:
#  CFLAGS.amd64      = -DLSB_FIRST -DALIGN_INTS -DALIGN_SHORTS -D__LP64__

#cat patch.txt | patch -p1 --dry-run

make -f makefile.unix SHELL='sh -x'  MY_CPU=amd64  SOUND_ALSA=1 

