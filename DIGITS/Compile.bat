@ECHO OFF

set file=digits

ECHO Compilation...
tasm.exe %file%.asm
tlink.exe /v %file%.obj, _%file%.exe
ECHO Deleting unnecessary files...
del %file%.lst
del %file%.obj
del _%file%.map
ECHO [START PROGRAM]
_%file%.exe
ECHO [END   PROGRAM]