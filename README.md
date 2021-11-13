# ClearTemp
More than just clearing temp files...
-
---

*This is super-light C project, which lasts roughly 6ms.*

# Running ClearTemp:
- Compiling
	- [Linux way](#Linux)
	- [Windows way](#Windows)
	- [Simplified way](#Simplified)
- [Running](#Running)
- [Flags](#Flags)
- [Getting ClearTemp](#Getting)

# Linux
To run ClearTemp on Linux, **you have to** get submodules and then run makefile. To get submodules ([EngoDatabase](https://github.com/ENGO150/EngoDatabase)), use commands (in ClearTemp folder) `git submodule init` and then `git submodule update`. Now you have to run makefile (or you can run out/ClearTemp, but I STRONGLY recommend not using that way). Makefile is located in project folder (ClearTemp/Makefile). You can run makefile by command `make` from Makefile's (project) directory.

# Windows
Running ClearTemp on Windows is same as running on Linux, except you have to install compiler AND use Windows commands (jump to [simplified](#Simplified)). My favorite compiler is [MinGW](https://sourceforge.net/projects/mingw/). Search for any tutorial on YouTube if needed.

# Simplified
There's also simplified way to compile and run ClearTemp. Run **cleartemp-simplified** (use file supported by your OS; Linux = cleartemp-simplified.**sh**, Windows = cleartemp-simplified.**bat**) and run it. **If you don't have properly configured git and gcc, this will not work!**

# Running
To run compiled program, **you have to run it from project directory**. If you will not do this (making shortcut etc.), program will probably print **"Resource folder not found"** (language configuration files weren't found) and end. Running is possible by double clicking from project directory (you can't use flags here), or in terminal - still using project directory (the method below is working in Linux terminal and Microsoft powershell; if you're using the powershell method, you probably have to use ClearTemp.exe instead of ClearTemp):

`./out/ClearTemp [--console] [--usernameFlag:NAME] [--block:PASSWORD] [--unblock:PASSWORD] [--excex] [--debug] [--exit] [--language:LANG] [--logs]`

# Flags
- --console = show console
- --username:NAME = clear temp of specific user (replace NAME with user's name) !!THIS ISN'T WORKING ON LINUX - DEFAULT TEMP DIRECTORY ON LINUX IS /TMP!!
- --block:PASSWORD = block deleting temp with this program (replace PASSWORD with password for blocking !YOU CAN USE SPECIAL CHARACTERS, BUT AT YOUR OWN RISK!)
- --unblock:PASSWORD = unblock deleting temp with this program (replace PASSWORD with password you used [-block])
- --excex = exiting on exception (that is, whenever a program finds a temporary file that cannot be deleted, it stops)
- --debug = doesn't remove any of your temp file, just tests the program
- --exit = shows exit reasons
- --language:LANG = use more languages (replace LANG with language shortcut; Available: EN, CZ)
- --logs = uses log files generated in logs/
The args in square brackets **aren't** required, and you also don't need to use both of them. I am not responsible for any misuse. Use this program only with the permission of the user to whom you are deleting temporary files. I am developing this program on Linux (Arch), but it should work perfectly on Windows, too.

# Getting
Clone the repository using `git clone https://github.com/ENGO150/ClearTemp.git` for latest 'release' or you can download the latest **stable** release [here](https://github.com/ENGO150/ClearTemp/releases/latest).
