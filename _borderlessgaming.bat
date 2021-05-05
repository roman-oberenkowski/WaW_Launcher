@echo off
tasklist /FI "IMAGENAME eq BorderlessGaming.exe" 2>NUL | find /I /N "BorderlessGaming.exe">NUL
if "%ERRORLEVEL%"=="0" (echo "BG Running...") else (start "" "C:\Program Files (x86)\Borderless Gaming\BorderlessGaming.exe" 
echo "BG Launched...")