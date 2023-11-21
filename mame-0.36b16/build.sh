#!/bin/bash

# todo: datafile, state added to OBJs 
#  $(OBJ)/state.o $(OBJ)/datafile.o 
# makeifle.unix:
#  ESOUND_CFLAGS = -DSYSDEP_DSP_ALSA
#  ESOUND_LIBS = -lasound

#cat patch.txt | patch -p1 --dry-run

make -f makefile.unix SHELL='sh -x'  MY_CPU=amd64  SOUND_ALSA=1 

