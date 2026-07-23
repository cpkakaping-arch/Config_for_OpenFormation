@echo off
setlocal EnableDelayedExpansion

:: ============================================================
::                OPEN FORMATION - Hacker Edition
:: ============================================================

title Open Formation
color 0A
mode con: cols=120 lines=36
cls

echo.
echo.
echo ==============================================================================================================
echo.
echo        OOOOO    PPPPPP    EEEEEEE   N     N
echo       OO   OO   PP   PP   EE        NN    N
echo       OO   OO   PPPPPP    EEEEE     N N   N
echo       OO   OO   PP        EE        N  N  N
echo        OOOOO    PP        EEEEEEE   N   N N
echo.
echo.
echo      FFFFFFF   OOOOO    RRRRRR    M     M    AAAAA    TTTTTTT   III   OOOOO   N     N
echo      FF       OO   OO   RR   RR   MM   MM   AA   AA      T       I   OO   OO  NN    N
echo      FFFFF    OO   OO   RRRRRR    M M M M   AAAAAAA      T       I   OO   OO  N N   N
echo      FF       OO   OO   RR  RR    M  M  M   AA   AA      T       I   OO   OO  N  N  N
echo      FF        OOOOO    RR   RR   M     M   AA   AA      T      III   OOOOO   N   N N
echo.
echo ==============================================================================================================
echo.

echo [*] Booting Open Formation environment...
ping 127.0.0.1 -n 2 >nul

echo [*] Loading compiler................................................. [ OK ]
ping 127.0.0.1 -n 2 >nul

echo [*] Loading Git...................................................... [ OK ]
ping 127.0.0.1 -n 2 >nul

echo [*] Loading Development Environment................................. [ OK ]
ping 127.0.0.1 -n 2 >nul

echo [*] Loading Libraries............................................... [ OK ]
ping 127.0.0.1 -n 2 >nul

echo [*] Initializing Terminal........................................... [ OK ]
ping 127.0.0.1 -n 2 >nul

echo [*] Checking System................................................. [ OK ]
ping 127.0.0.1 -n 2 >nul

echo.
echo --------------------------------------------------------------------------------------------------------------
echo.
echo             C Development   ^|   Git   ^|   Linux   ^|   PowerShell   ^|   Networking
echo             Reverse Engineering   ^|   Cybersecurity   ^|   Open Source
echo.
echo --------------------------------------------------------------------------------------------------------------
echo.
echo             Version : 1.0.0
echo             Author  : Dieson Parfait
echo             Status  : READY
echo             Host    : %COMPUTERNAME%
echo             User    : %USERNAME%
echo             Date    : %DATE%
echo             Time    : %TIME%
echo.
echo ==============================================================================================================
echo.
echo                              Welcome to Open Formation
echo.
echo ==============================================================================================================
echo.

pause