# ClearTemp
Project that clears your temp files.
-
NOTE: THIS IS JUST ALPHA! FLAGS AREN'T WORKING AND YOU MUST RUN CLEARTEMP FROM THE BUILD FOLDER (cmake-build-debug)
-
---
You can launch the file by double-clicking it, but if you want to use some flags, launch it from command line:

./ClearTemp [-console] [-usernameFlag:NAME] [-block:PASSWORD] [-unblock:PASSWORD] [-excex] [-debug] [-exit] [-language:LANG]

^ This works on Linux shell or Windows powershell

- -console = show console
- -usernameFlag:NAME = clear temp of specific user (replace NAME with user's name) !!THIS ISN'T WORKING ON LINUX - DEFAULT TEMP DIRECTORY ON LINUX IS /TMP!!
- -block:PASSWORD = block deleting temp with this program (replace PASSWORD with password for blocking !YOU CAN USE SPECIAL CHARACTERS, BUT AT YOUR OWN RISK!)
- -unblock:PASSWORD = unblock deleting temp with this program (replace PASSWORD with password you used [-block])
- -excex = exiting on exception (that is, whenever a program finds a temporary file that cannot be deleted, it stops)
- -debug = doesn't remove any of your temp file, just tests the program
- -exit = shows exit reasons
- -language:LANG = use more languages (replace LANG with language shortcut; Available: EN, CZ)

The args in square brackets aren't required, and you also don't need to use both of them. I am not responsible for any misuse. Use this program only with the permission of the user to whom you are deleting temporary files. I am developing this program on Linux (Ubuntu), but it should work perfectly on Windows, too.

Java version of ClearTemp lasted 300ms, the new C version lasts 10ms.

*you can download the jar file [here](https://github.com/ENGO150/ClearTemp/releases/latest).
