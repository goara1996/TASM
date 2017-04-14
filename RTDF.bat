@ECHO OFF

start "" /WAIT td "%~1\_%~1.exe"
del _%~1.tr