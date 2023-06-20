diff -Naur ../orgs/sdlmame0111/build ../sdlmame0111/build
--- ../orgs/sdlmame0111/build	1969-12-31 19:00:00.000000000 -0500
+++ ../sdlmame0111/build	2023-06-20 19:14:05.000000000 -0400
@@ -0,0 +1,13 @@
+#NAME="Ubuntu"
+#VERSION="20.04.6 LTS (Focal Fossa)"
+#ID=ubuntu
+#ID_LIKE=debian
+#PRETTY_NAME="Ubuntu 20.04.6 LTS"
+#VERSION_ID="20.04"
+#HOME_URL="https://www.ubuntu.com/"
+#SUPPORT_URL="https://help.ubuntu.com/"
+#BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
+#PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
+#VERSION_CODENAME=focal
+#UBUNTU_CODENAME=focal
+make -f makefile   NOWERROR=1
diff -Naur ../orgs/sdlmame0111/makefile ../sdlmame0111/makefile
--- ../orgs/sdlmame0111/makefile	2006-12-11 21:50:30.000000000 -0500
+++ ../sdlmame0111/makefile	2023-06-20 19:03:53.000000000 -0400
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
@@ -280,6 +280,8 @@
 CFLAGSOSDEPEND = $(CFLAGS)
 
 LDFLAGS = -WO
+# xubuntu 20, gcc-9: error: unrecognized command line option ‘-WO’;
+LDFLAGS =
 
 ifdef SYMBOLS
 LDFLAGS = 
@@ -338,7 +340,9 @@
 #-------------------------------------------------
 
 # start with an empty set of libs
-LIBS = 
+LIBS =
+# xubuntu 20 
+LIBS = -lm -lpthread -lX11
 
 # add expat XML library
 ifdef BUILD_EXPAT
