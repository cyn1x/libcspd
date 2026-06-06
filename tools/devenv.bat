:: Script to set the development environment variables on Windows.

@echo off

setlocal enabledelayedexpansion

set ArgCount=0
for %%I in (%*) do (
    set /A ArgCount+=1
    set "ArgVec[!ArgCount!]=%%~I"
)

rem Default fallback if MSVC does not automatically set platform
if "%Platform%"=="" set Platform=x64

rem Process command-line arguments arguments
for /L %%I in (1,1,%ArgCount%) do (
    
    set arg=!argVec[%%I]!

    if !Arg! EQU x86 (
        rem Override platform set by MSVC if specified via command-line args
        set Platform=x86
    )

)

rem Configure development environment
if not defined DevEnvDir (

    rem Define Visual Studio Community environment variables
    set Dev16_A="C:\Program Files\Microsoft Visual Studio\20822\Community\VC\Auxiliary\Build\vcvarsall.bat"
    set Dev17_A="C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat"

    rem Define Visual Studio Build Tools environment variables
    set Dev16_B="C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
    set Dev17_B="C:\Program Files\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"

    rem Preference the latest version of Visual Studio Community
    if exist !Dev17_A! (
        call !Dev17_A! %Platform%
        goto :EOF
    )
    if exist !Dev16_A! ( 
        call %Dev16_A% %Platform% 
        goto :EOF 
    )

    rem Preference the latest version of Visual Studio Build Tools
    if exist !Dev17_B! (
        call !Dev17_B! %Platform%
        goto :EOF
    )
    if exist !Dev16_B! ( 
        call !Dev16_B! %Platform% 
        goto :EOF 
    )

    rem No valid installation of Visual Studio or Visual Studio Build Tools was found
    echo Error: Unable to locate compiler toolchain
    echo Check: At least one of the following should be valid:  &echo  - !Dev16_A:~1,-1! &echo  - !Dev17_A:~1,-1! &echo  - !Dev16_B:~1,-1! &echo  - !Dev17_B:~1,-1! 
    set Result=1
)
