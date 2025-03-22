REM 
REM     BUILD.BAT (v1.0)
REM     -----------------------------------------------------------
REM 
REM     Small Batch script that runs several commands used to build
REM     and compile the AES project. This script also provides
REM     basic error management and clean program output.
REM 
REM     Script written for learning purposes only.
REM     © 2025 Sacha Meurice

@echo off & cls



REM Check if source files exist
if not exist AES (
    echo ERROR: Could not find AES directory.
    goto :END
)

if not exist "main.c" (
    echo ERROR: Could not find main.c file.
    goto :END
)


REM Prepare current directory
if not exist "obj" (
    mkdir obj
)

del *.exe 2> NUL
del obj\*.o 2> NUL



REM Compilation of aes.c
GCC -pedantic -Wextra -Wall -g -c AES\aes.c -o obj\aes.o

if %errorLevel% NEQ 0 (
    echo AES.c compiling failed! & echo.
    goto :END
)


REM Compilation of main.c
GCC -pedantic -Wextra -Wall -g -c main.c -o obj\main.o

if %errorLevel% NEQ 0 (
    echo MAIN.c compiling failed! & echo.
    goto :END
)


REM Linking
GCC -o main.exe obj\aes.o obj\main.o

if %errorLevel% NEQ 0 (
    echo Code linking failed! & echo.
    goto :END
)



REM Set some default test vectors
set AES_input=3243f6a8885a308d313198a2e0370734
set AES_key=2b7e151628aed2a6abf7158809cf4f3c

REM This should be the program's output
set AES_output=3925841d02dc09fbdc118597196a0b32


REM Program's execution
main %AES_input% %AES_key%


:END
echo. & echo.
pause & exit
