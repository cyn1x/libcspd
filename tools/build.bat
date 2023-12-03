@echo off

setlocal enabledelayedexpansion

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem Change directory to the project root
popd

if not exist obj mkdir obj
if not exist bin mkdir bin
if not exist tests\obj mkdir tests\obj
if not exist tests\bin mkdir tests\bin

:: del /S /Q obj\*.* > nul
:: del /S /Q bin\*.* > nul
del /S /Q tests\obj*.* > nul
del /S /Q tests\bin*.* > nul

set dll=turbo.dll
set exe=turbo.exe

rem/||(
Store the absolute ^path of the project root directory in a variable 
followed by a slash to stay consistent with `~dp0` when using 
functions ^for splitting strings. ^)
)
set root=%cd%\
set cmp=!root:~0,-1!

rem Recursively set all relative include directory paths
for /r include %%d in (.) do ( 
    set "abspath=%%d"
    set "relpath=!abspath:%cmp%=!"
    call set "incs=%%incs%% -I..!relpath:~0,-2!"
)

pushd obj

rem Recursively set all relative file paths of *.c source files
for /r ..\src %%f in (*.c) do ( 
    set "abspath=%%f"
    set "relpath=!abspath:%cmp%=!"
    call set "srcs=%%srcs%% ..!relpath!"
)

rem Compile *.c files
cl /c /LD -Zi -W4 -Wall %incs% /std:c11 %srcs:~1%

popd
pushd bin

rem Store all *.obj file names only for the linker
for /r ..\obj %%f in (*.obj) do (
    call set "objs=%%objs%% ..\obj\%%~nxf"
)

rem Link *.obj object files
LINK /DEBUG %objs:~1% /DLL /OUT:%dll%
rem Copy DLL to where the test executable will be built
copy ..\bin\turbo.dll ..\tests\bin\turbo.dll

rem Store all *.test.c source files in a variable
for /r ..\tests %%f in (*.c) do ( 
    call set "testsrcs=%%testsrcs%% %%~nxf"
)

popd
pushd tests

rem Compile *.test.c files
cl /Fo"obj\\" /Fd"obj\\" /c -Zi -W4 -Wall %testsrcs% %incs%

rem Store all *test.obj file names only for the linker
for /r obj %%f in (*.obj) do (
    call set "testobjs=%%testobjs%% obj\%%~nxf"
)

rem Link *.test.obj object files
LINK %testobjs:~1% /OUT:bin\%exe% ..\bin\turbo.lib

popd
