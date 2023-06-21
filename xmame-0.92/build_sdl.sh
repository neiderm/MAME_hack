#!/bin/bash
make -f makefile.unix  MY_CPU=amd64  DISPLAY_METHOD=SDL SOUND_SDL=1 JOY_SDL=1  LDFLAGS='' 
