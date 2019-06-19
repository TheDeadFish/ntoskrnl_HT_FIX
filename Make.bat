:: create directories
mkdir bin 2>NUL
mkdir exm 2>NUL
mkdir dll 2>NUL

:: build object files
@call :gen_obj 32
@endlocal
@call :gen_obj 64

:: build exm files
@setlocal
@call exmod.bat x64
@call :gen_exm ntkrnlpa x86.5.2.3790.3959 cpuid-32.o
@call :gen_exm ntoskrnl x86.5.2.3790.3959 cpuid-32.o
@call :gen_exm ntoskrnl x64.5.2.3790.3959 cpuid-64.o
build-exm.bat

:gen_obj
@setlocal
@call exmod.bat x%1
@gcc src\cpuid-%1.cc %CFLAGS2% -D__W32API_USE_DLLIMPORT__ -c -o cpuid-%1.o
@exit /B

:gen_exm  
exe_mod +exm\%1.exe;htfix.exm:%2 src\%1;%2.def %3
@exit /B
