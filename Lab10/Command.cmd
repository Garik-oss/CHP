@echo off
:menu
cls
echo ==============================
echo Menu
echo ==============================
echo 1. Display device IPv4 and IPv6 addresses
echo 2. Network trace (traceroute)
echo 3. Get IP address of a hostname or URL
echo 4. Encrypt input text into a new file
echo 5. Decrypt a file
echo 6. Calculate file checksum
echo 7. Exit
echo ==============================
set /p choice=Select an action (1-7): 

if "%choice%"=="1" goto show_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_ip
if "%choice%"=="4" goto encrypt
if "%choice%"=="5" goto decrypt
if "%choice%"=="6" goto checksum
if "%choice%"=="7" exit
goto menu

:show_ip
cls
echo Device IPv4 and IPv6 addresses:
ipconfig | findstr "IPv4 IPv6"
pause
goto menu

:traceroute
cls
set /p hostname=Enter hostname or URL: 
tracert %hostname%
pause
goto menu

:resolve_ip
cls
set /p hostname=Enter hostname or URL: 
nslookup %hostname%
pause
goto menu

:encrypt
cls
set /p text=Enter text to encrypt:
echo %text% > temp.txt
certutil -encode temp.txt encrypted.txt
del temp.txt
echo Text successfully encrypted and saved in encrypted.txt.
pause
goto menu

:decrypt
cls
set /p filename=Enter file name to decrypt:
if not exist %filename% (
    echo %filename% not found.
    pause
    goto menu
)
certutil -decode %filename% decrypted.txt
echo Text successfully decrypted and saved in decrypted.txt.
pause
goto menu

:checksum
cls
set /p filename=Enter file name to calculate checksum:
if not exist %filename% (
    echo %filename% not found.
    pause
    goto menu
)
certutil -hashfile %filename% SHA256
pause
goto menu
