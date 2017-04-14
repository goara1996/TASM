@ECHO OFF

set comeback=%~dp0%

cd %~1

call compile.bat %~2

cd %comeback%