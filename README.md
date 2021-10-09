# ClearTemp
More than just clearing temp files...
-
---

*This is super-light C project, which lasts roughly 6ms.*

# Running ClearTemp:
- Compiling
	- [Linux way](#Linux)
	- [Windows way](#Windows)
- [Running](#Running)
- [Flags](#Flags)
- [Getting ClearTemp](#Getting)

# Linux
To run ClearTemp on Linux, you have to run makefile (or you can run Debug/ClearTemp, but I STRONGLY recommend not using that way). Makefile is located in Debug folder (Debug/makefile). You can run makefile by command `make` from makefile's directory - here it is Debug/.

# Windows
Running ClearTemp on Windows is similar to running on Linux, except you have to install compiler. My favorite is [MinGW](https://sourceforge.net/projects/mingw/). Search for any tutorial on YouTube if needed.

# Running
To run compiled program, you have to run it from directory, where it was compiled (Debug/). If you will not do this (making shortcut etc.), program will probably print "EDBLOC is NULL" and end. Running is possible by double clicking (you can't use flags here), or in terminal (the method below is working in Linux terminal and Microsoft powershell; if you're using the powershell method, you probably have to use ClearTemp.exe instead of ClearTemp):

`./ClearTemp [--console] [--usernameFlag:NAME] [--block:PASSWORD] [--unblock:PASSWORD] [--excex] [--debug] [--exit] [--language:LANG]`

# Flags
- -console = show console
- -username:NAME = clear temp of specific user (replace NAME with user's name) !!THIS ISN'T WORKING ON LINUX - DEFAULT TEMP DIRECTORY ON LINUX IS /TMP!!
- -block:PASSWORD = block deleting temp with this program (replace PASSWORD with password for blocking !YOU CAN USE SPECIAL CHARACTERS, BUT AT YOUR OWN RISK!)
- -unblock:PASSWORD = unblock deleting temp with this program (replace PASSWORD with password you used [-block])
- -excex = exiting on exception (that is, whenever a program finds a temporary file that cannot be deleted, it stops)
- -debug = doesn't remove any of your temp file, just tests the program
- -exit = shows exit reasons
- -language:LANG = use more languages (replace LANG with language shortcut; Available: EN, CZ)

The args in square brackets aren't required, and you also don't need to use both of them. I am not responsible for any misuse. Use this program only with the permission of the user to whom you are deleting temporary files. I am developing this program on Linux (Arch), but it should work perfectly on Windows, too.


# Getting
Clone the repository using `git clone https://github.com/ENGO150/ClearTemp.git` for latest 'release' or you can download the latest stable release [here](https://github.com/ENGO150/ClearTemp/releases/latest).
