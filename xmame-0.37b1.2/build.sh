#!/bin/bash

# patched XMAME for ALSA sound on Linux, 
# uses puckman ROM set
# alsa.c from xmame-0.79.1, other dsp related files from xmame-0.37b7.1

# cat patch.txt | patch -p1 --dry-run

make -f makefile.unix SHELL='sh -x'  MY_CPU=amd64  SOUND_ALSA=1 
