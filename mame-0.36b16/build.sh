#!/bin/bash

# Apply the patch to install xmame-0.36.1 with backported ALSA sound 
# xmame-0.36.1 is modified for "new" ALSA interface (xmame-0.79.1) which also needs
# upgrade to support streams which were added in xmame-0.37

#cat xmame-0.36b16.patch | patch -p1 --dry-run

make -f makefile.unix SHELL='sh -x'  MY_CPU=amd64  SOUND_ALSA=1 

