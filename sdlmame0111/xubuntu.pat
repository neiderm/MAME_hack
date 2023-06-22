diff -Naur sdlmame0111.org/makefile sdlmame0111++++/makefile
--- sdlmame0111.org/makefile	2006-12-11 21:50:30.000000000 -0500
+++ sdlmame0111++++/makefile	2023-04-30 12:36:57.971798291 -0400
@@ -49,7 +49,7 @@
 #-------------------------------------------------
 
 # uncomment next line to include the debugger
-# DEBUG = 1    
+DEBUG = 1    
  
 # uncomment next line to use DRC MIPS3 engine
 X86_MIPS3_DRC = 1
@@ -73,13 +73,13 @@
 # ATHLON = 1
 # I686 = 1
 # P4 = 1
-PM = 1
-# AMD64 = 1
+#PM = 1
+AMD64 = 1
 # G4 = 1
 # G5 = 1
 
 # uncomment next line if you are building for a 64-bit target
-# PTR64 = 1
+PTR64 = 1
 
 # uncomment next line to build expat as part of MAME build
 # BUILD_EXPAT = 1
@@ -280,6 +280,7 @@
 CFLAGSOSDEPEND = $(CFLAGS)
 
 LDFLAGS = -WO
+LDFLAGS =
 
 ifdef SYMBOLS
 LDFLAGS = 
@@ -338,7 +339,7 @@
 #-------------------------------------------------
 
 # start with an empty set of libs
-LIBS = 
+LIBS = -lm -lpthread -lX11
 
 # add expat XML library
 ifdef BUILD_EXPAT
