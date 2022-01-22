# ClearTemp
More than just clearing temp files...
-
---

*This is super-light C++ project, which lasts roughly 10ms.*

# Running ClearTemp:
- Compiling
	- [Linux way](#Linux)
	- [Windows way](#Windows)
	- [Simplified way](#Simplified)
- [Running](#Running)
- [Flags](#Flags)
- [Getting ClearTemp](#Getting)

# Linux
To run ClearTemp on Linux, **you have to** get submodules and then run makefile (cmake). You can use the [simplified](#Simplified) way, or you can do it yourself. To get submodules ([JSON](https://github.com/nlohmann/json)), use commands (in ClearTemp folder) `git submodule init`, `git submodule update`, then open JSON-lib (libs/json/) and install it with `cmake .`, `make` and `make install`. Now you have to run cmake. Cmake is in project folder (ClearTemp/CMakeLists.txt). You can run cmake by command `cmake ..` from folder, you want to store output, I would recommend using folder `out/`...

# Windows
Running ClearTemp on Windows is same as running on [Linux](#Linux), except you have to install compiler(s). My favorite compiler is [MinGW](https://sourceforge.net/projects/mingw/) AND you have to install [CMake](https://cmake.org/). Search for any tutorial on YouTube if needed.

# Simplified
Running can be really simple. If you didn't use ClearTemp before, you'll need to launch `configure` script to setup libraries. Then you can run `build` script to compile project. Then the output file should be saved in `out/` as `ClearTemp`...

# Running
To run compiled program, **you have to run it from project directory**. If you will not do this (making shortcut etc.), program will probably print **"Resource folder not found"** (language configuration files weren't found) and end. Running is possible in terminal - still using project directory (the method below is working in Linux terminal and Microsoft powershell (or cmd); if you're using the powershell method, you probably have to use ClearTemp.exe instead of ClearTemp):

`./out/ClearTemp [--console] [--username:NAME] [--block:PASSWORD] [--unblock:PASSWORD] [--excex] [--debug] [--exit] [--language:LANG] [--logs]`

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