:: Script to set the development environment variables on Windows.

:: Variable names use Microsoft visual Studio project codenames
:: https://en.wikipedia.org/w/index.php?title=Visual_Studio&oldid=1356912898#History

@echo off

rem Set platform to the processor architecture if running as a standalone script
if "%Platform%"=="" set Platform=%PROCESSOR_ARCHITECTURE%

rem Define Visual Studio Community environment variables
set Dev16_A="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
set Dev17_A="C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat"

rem Define Visual Studio Build Tools environment variables
set Dev16_B="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
set Dev17_B="C:\Program Files (x86)\Microsoft Visual Studio\18\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"

rem Configure development environment
if not defined DevEnvDir (

    setlocal EnableDelayedExpansion
    if defined MsvcDir (
        rem Preference MsvcDir variable in env.ini
        if exist !MsvcDir! endlocal & call !MsvcDir! %Platform% && goto :EOF
    )
    endlocal

    rem Preference the latest version of Visual Studio Community
    if exist %Dev17_A% call %Dev17_A% %Platform% && goto :EOF
    if exist %Dev16_A% call %Dev16_A% %Platform% && goto :EOF

    rem Preference the latest version of Visual Studio Build Tools
    if exist %Dev17_B% call %Dev17_B% %Platform% && goto :EOF
    if exist %Dev16_B% call %Dev16_B% %Platform% && goto :EOF

    rem No valid installation of Visual Studio or Visual Studio Build Tools was found
    echo Error: Unable to locate compiler toolchain
    echo Check: At least one of the following should be valid:  &echo  - !Dev16_A:~1,-1! &echo  - !Dev17_A:~1,-1! &echo  - !Dev16_B:~1,-1! &echo  - !Dev17_B:~1,-1! 
    set ErrorLevel=1
)
