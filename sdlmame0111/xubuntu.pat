diff -Naur sdlmame0111++++/makefile sdlmame0111/makefile
--- sdlmame0111++++/makefile	2023-04-30 12:36:57.971798291 -0400
+++ sdlmame0111/makefile	2023-06-21 20:31:17.005612051 -0400
@@ -49,7 +49,7 @@
 #-------------------------------------------------
 
 # uncomment next line to include the debugger
-DEBUG = 1    
+# DEBUG = 1    
  
 # uncomment next line to use DRC MIPS3 engine
 X86_MIPS3_DRC = 1
@@ -73,7 +73,7 @@
 # ATHLON = 1
 # I686 = 1
 # P4 = 1
-#PM = 1
+# PM = 1
 AMD64 = 1
 # G4 = 1
 # G5 = 1
@@ -279,7 +279,6 @@
 # extra options needed *only* for the osd files
 CFLAGSOSDEPEND = $(CFLAGS)
 
-LDFLAGS = -WO
 LDFLAGS =
 
 ifdef SYMBOLS
@@ -338,7 +337,7 @@
 # libraries
 #-------------------------------------------------
 
-# start with an empty set of libs
+# start with a default set of libs
 LIBS = -lm -lpthread -lX11
 
 # add expat XML library
