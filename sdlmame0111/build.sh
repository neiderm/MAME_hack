#!/bin/bash

#NAME="Ubuntu"
#VERSION="20.04.6 LTS (Focal Fossa)"
#VERSION="22.04.3 LTS (Jammy Jellyfish)"
# install:
# libgtk2.0-dev libgconf2-dev libsdl1.2-dev

#  # patched makefile: 
#  # PM=1
#  AMD64=1 DEBUG=1 PTR64=1 NOWERROR=1
#  # LDFLAGS = -WO
#  LDFLAGS =
#  LIBS = -lm -lpthread -lX11

# schaser_sx10 redefined

# cat xubuntu.pat  | patch -p1 --dry-run

make -f makefile  AMD64=1 DEBUG=1 PTR64=1 NOWERROR=1 

