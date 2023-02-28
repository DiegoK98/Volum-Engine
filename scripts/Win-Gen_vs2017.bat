@echo off
pushd ..\
call vendor\premake\premake5.exe vs2017
popd
PAUSE