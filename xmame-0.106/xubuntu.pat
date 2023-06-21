diff -Naur ../xmame-0.106/build.sh ../orgs/xmame-0.106/build.sh
--- ../xmame-0.106/build.sh	2023-06-20 20:23:54.000000000 -0400
+++ ../orgs/xmame-0.106/build.sh	1969-12-31 19:00:00.000000000 -0500
@@ -1,13 +0,0 @@
-# NAME="Ubuntu"
-# VERSION="20.04.6 LTS (Focal Fossa)"
-# ID=ubuntu
-# ID_LIKE=debian
-# PRETTY_NAME="Ubuntu 20.04.6 LTS"
-# VERSION_ID="20.04"
-# HOME_URL="https://www.ubuntu.com/"
-# SUPPORT_URL="https://help.ubuntu.com/"
-# BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
-# PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
-# VERSION_CODENAME=focal
-# UBUNTU_CODENAME=focal
-make -f makefile  NOWERROR=1 SOUND_SDL=1
diff -Naur ../xmame-0.106/Makefile ../orgs/xmame-0.106/Makefile
--- ../xmame-0.106/Makefile	2023-06-20 19:48:03.000000000 -0400
+++ ../orgs/xmame-0.106/Makefile	2006-05-15 12:53:34.000000000 -0400
@@ -576,7 +576,7 @@
 ###########################################################################
 
 # i386, GNU asm
-#MY_CPU = i386
+MY_CPU = i386
 
 # i386, no asm -- needed for the Intel C++ compiler, which does not fully
 # understand GCC's inline assembly syntax, though you may still enable 
@@ -588,7 +588,7 @@
 # MY_CPU = ia64
 
 # Opteron/Athlon64
-MY_CPU = amd64
+# MY_CPU = amd64
 
 # Intel EM64T
 # MY_CPU = em64t
diff -Naur ../xmame-0.106/makefile.unix ../orgs/xmame-0.106/makefile.unix
--- ../xmame-0.106/makefile.unix	2023-06-20 19:48:03.000000000 -0400
+++ ../orgs/xmame-0.106/makefile.unix	2006-05-15 12:53:34.000000000 -0400
@@ -576,7 +576,7 @@
 ###########################################################################
 
 # i386, GNU asm
-#MY_CPU = i386
+MY_CPU = i386
 
 # i386, no asm -- needed for the Intel C++ compiler, which does not fully
 # understand GCC's inline assembly syntax, though you may still enable 
@@ -588,7 +588,7 @@
 # MY_CPU = ia64
 
 # Opteron/Athlon64
-MY_CPU = amd64
+# MY_CPU = amd64
 
 # Intel EM64T
 # MY_CPU = em64t
diff -Naur ../xmame-0.106/xubuntu.pat ../orgs/xmame-0.106/xubuntu.pat
--- ../xmame-0.106/xubuntu.pat	2023-06-20 20:25:23.000000000 -0400
+++ ../orgs/xmame-0.106/xubuntu.pat	1969-12-31 19:00:00.000000000 -0500
@@ -1,59 +0,0 @@
-diff -Naur ../xmame-0.106/build.sh ../orgs/xmame-0.106/build.sh
---- ../xmame-0.106/build.sh	2023-06-20 20:23:54.000000000 -0400
-+++ ../orgs/xmame-0.106/build.sh	1969-12-31 19:00:00.000000000 -0500
-@@ -1,13 +0,0 @@
--# NAME="Ubuntu"
--# VERSION="20.04.6 LTS (Focal Fossa)"
--# ID=ubuntu
--# ID_LIKE=debian
--# PRETTY_NAME="Ubuntu 20.04.6 LTS"
--# VERSION_ID="20.04"
--# HOME_URL="https://www.ubuntu.com/"
--# SUPPORT_URL="https://help.ubuntu.com/"
--# BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
--# PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
--# VERSION_CODENAME=focal
--# UBUNTU_CODENAME=focal
--make -f makefile  NOWERROR=1 SOUND_SDL=1
-diff -Naur ../xmame-0.106/Makefile ../orgs/xmame-0.106/Makefile
---- ../xmame-0.106/Makefile	2023-06-20 19:48:03.000000000 -0400
-+++ ../orgs/xmame-0.106/Makefile	2006-05-15 12:53:34.000000000 -0400
-@@ -576,7 +576,7 @@
- ###########################################################################
- 
- # i386, GNU asm
--#MY_CPU = i386
-+MY_CPU = i386
- 
- # i386, no asm -- needed for the Intel C++ compiler, which does not fully
- # understand GCC's inline assembly syntax, though you may still enable 
-@@ -588,7 +588,7 @@
- # MY_CPU = ia64
- 
- # Opteron/Athlon64
--MY_CPU = amd64
-+# MY_CPU = amd64
- 
- # Intel EM64T
- # MY_CPU = em64t
-diff -Naur ../xmame-0.106/makefile.unix ../orgs/xmame-0.106/makefile.unix
---- ../xmame-0.106/makefile.unix	2023-06-20 19:48:03.000000000 -0400
-+++ ../orgs/xmame-0.106/makefile.unix	2006-05-15 12:53:34.000000000 -0400
-@@ -576,7 +576,7 @@
- ###########################################################################
- 
- # i386, GNU asm
--#MY_CPU = i386
-+MY_CPU = i386
- 
- # i386, no asm -- needed for the Intel C++ compiler, which does not fully
- # understand GCC's inline assembly syntax, though you may still enable 
-@@ -588,7 +588,7 @@
- # MY_CPU = ia64
- 
- # Opteron/Athlon64
--MY_CPU = amd64
-+# MY_CPU = amd64
- 
- # Intel EM64T
- # MY_CPU = em64t
