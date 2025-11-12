@echo off

setlocal enabledelayedexpansion

set err=

set argCount=0
for %%x in (%*) do (
    set /A argCount+=1
    set "argVec[!argCount!]=%%~x"
)

rem Default fallback if MSVC does not automatically set platform
if "%platform%"=="" set platform=x64

set config=Debug
set compileropts=-DDEBUG=1
set linkeropts=/DEBUG

rem Set project root directory
set root=%~dp0..
for %%I in ("%ROOT%") do set "root=%%~fI"

rem Process command-line arguments arguments
for /L %%i in (1,1,%argCount%) do (
    
    set arg=!argVec[%%i]!

    if !arg! EQU clean goto :clean

    if !arg! EQU release (
        set compileropts=-Od -DDEBUG=0
        set linkeropts=/OPT:REF
        set config=Release
    )
    if !arg! EQU x86 (
        rem Override platform set by MSVC if specified via command-line args
        set platform=x86
    )

)

rem End of entry point procedure
goto :main

rem ==========================
rem Clean
rem ==========================
:clean
rem Deletes all intermediary and binary files from previous compilations
del /S /Q bin\*.dll bin\*.exe bin\*.lib bin\*.pdb bin\*.ilk bin\*.exp > nul 2>&1
del /S /Q obj\*.obj obj\*.pdb > nul 2>&1
del /S /Q tests\obj\*.obj tests\obj\*.pdb > nul 2>&1 
del /S /Q tests\bin\*.dll tests\bin\*.exe tests\bin\*.lib tests\bin\*.pdb^
    tests\bin\*.ilk tests\bin\*.exp > nul 2>&1

rem End of :clean subroutine call
goto :eof

rem ==========================
rem Main
rem ==========================
:main

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

rem Define the engine dynamic link library and application executable filenames
set _dll=libcspd_%platform%.dll
set _lib=libcspd_%platform%.lib
set _exe=libcspd_%platform%.exe

rem Define `compile_flags.txt` file for the LLVM Clang LSP
set flags=compile_flags.txt

rem Clear `compile_flags.txt` file
echo | set /p clear="" > %flags%

rem Make required directories for core engine and sandbox environment
call :mkdirs
if %errorlevel% neq 0 goto :error

goto :build

rem ==========================
rem Make Output Directories
rem ==========================
:mkdirs
rem Make required directories for engine compilation

if not exist obj mkdir obj
if not exist obj\win32\%config%_x86 mkdir obj\win32\%config%_x86
if not exist obj\win32\%config%_x64 mkdir obj\win32\%config%_x64
if not exist bin mkdir bin
if not exist bin\win32\%config%_x86 mkdir bin\win32\%config%_x86
if not exist bin\win32\%config%_x64 mkdir bin\win32\%config%_x64
if not exist tests\obj mkdir tests\obj
if not exist tests\obj\win32\%config%_x86 mkdir tests\obj\win32\%config%_x86
if not exist tests\obj\win32\%config%_x64 mkdir tests\obj\win32\%config%_x64
if not exist tests\bin mkdir tests\bin
if not exist tests\bin\win32\%config%_x86 mkdir tests\bin\win32\%config%_x86
if not exist tests\bin\win32\%config%_x64 mkdir tests\bin\win32\%config%_x64

rem End of `:mkdirs` subroutine call
goto :eof

rem ==========================
rem Build
rem ==========================
:build
rem Builds the entire solution

rem Set the core library `include` and `src` directories
set incdir=%root%\include
set srcdir=%root%\src

rem Set the core library `obj` and `bin` directories
set objdir=%root%\obj\win32\%config%_%platform%
set bindir=%root%\bin\win32\%config%_%platform%

rem Clear variables to store source, include, and object filenames.
set srcs=
set incs=
set objs=

rem Recursively set all relative file paths of `*.h` header files
for /r include %%F in (*.h) do (
    call :include %%F
)
if %errorlevel% neq 0 goto :error

rem Recursively set all relative file paths of `*.c` lib\logc files
for /r lib\logc %%F in (*.h) do (
    call :include %%F
)
if %errorlevel% neq 0 goto :error

rem Recursively set all relative file paths of `*.c` source files
for /r src %%F in (*.c) do ( 
    call :sources %%F
)
if %errorlevel% neq 0 goto :error

rem Recursively set all relative file paths of `*.c` lib\logc files
for /r lib\logc %%F in (*.c) do ( 
    call :sources %%F
)
if %errorlevel% neq 0 goto :error

goto :compile

rem ==========================
rem Include
rem ==========================
:include
rem Reference the absolute and relative paths of each `*.h` header file

call :relpath %~dp1

rem Prevent duplicate include directories
if !prev! neq !relpath! (

    call set "incs=%%incs%% -I%root%!relpath:~0,-1!"
    call :addcompileflag !relpath!

    set "prev=!relpath!"
)

rem End of :include subroutine call
goto :eof

:sources
call :relpath %1
call set "srcs=%%srcs%% %root%!relpath!"

rem End of :sources subroutine call
goto :eof

rem ==========================
rem Compile
rem ==========================
:compile
rem Compile core library `*.c` files
cl /c /MD -Zi -W4 -Wall /std:c17 /Fo%objdir%\ /Fd"%objdir%\vc140.pdb" %incs% %srcs%
if %errorlevel% neq 0 goto :error
echo Library source files compiled successfully & echo.

rem Store all *.obj file names only for the linker
for /r obj %%F in (*.obj) do (
    call set "objs=%%objs%% %objdir%\%%~nxF"
)

rem Link *.obj object files
LINK /nologo /DEBUG %objs:~1% /DLL /OUT:%bindir%\%_dll% /DEF:libcspd.defs
if %errorlevel% neq 0 goto :error
call :relpath %bindir%
echo Library file `%_lib%` created in `%relpath%` successfully. & echo.

rem Copy DLL to where the test executable will be built
copy %bindir%\%_dll% %root%\tests\bin\win32\%config%_%platform% > nul

rem ==========================
rem Test Executable
rem ==========================

rem Set the core library `include` and `src` directories
set incdir=%root%\tests
set srcdir=%root%\tests

rem Clear `srcs` and `objs` variables to store new source and object filenames
set srcs=
set objs=

rem Set the `obj` and `bin` directories for the test project
set objdir=%root%\tests\obj\win32\%config%_%platform%
set bindir=%root%\tests\bin\win32\%config%_%platform%

rem Store all `*.test.c` source files in a variable
for /r tests %%F in (*.test.c) do ( 
    call :relpath %%F
    call set "srcs=%%srcs%% %root%!relpath!"
)

rem Compile test program and link DLL

rem Compile *.test.c files
cl /nologo /c /MD -Zi -W4 -Wall /std:c17 /Fo%objdir%\ /Fd"%objdir%\vc140.pdb" %incs% %srcs:~1%
if %errorlevel% neq 0 goto :error
echo Test source files compiled successfully & echo.

rem Store all *.test.obj file names only for the linker
for /r tests %%F in (*.test.obj) do (
    call set "objs=%%objs%% %objdir%\%%~nxF"
)

rem Link *.test.obj object files
LINK /DEBUG %objs:~1% /OUT:%bindir%\%_exe% %root%\bin\win32\Debug_x64\%_lib%
if %errorlevel% neq 0 goto :error
echo Test source files compiled successfully & echo.

echo Build succeeded.
goto :eof

rem ==========================
rem Relative Path
rem ==========================
rem Gets the relative path from the given absolute path
:relpath
set "abspath=%1%"
set "relpath=!abspath:%root%=!"
goto :eof

rem ==========================
rem Compile Flags
rem ==========================
:addcompileflag
rem Adds a compile flag to `compile_flags.txt` for the Clang LSP.
set flag=%1
rem Invert slashes for include paths to be compatible with the LSP
set cpath=!flag:\=/!
echo -I>> %root%\%flags%
echo .!cpath!>> %root%\%flags%
goto :eof

rem ==========================
rem Error
rem ==========================
:error
rem Error function to call when a build error is encountered
set err=%errorlevel%
echo. 
echo Build failed.
echo Exited with error code: %errorlevel%
exit /b %errorlevel%
