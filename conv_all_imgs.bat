@echo off
setlocal enabledelayedexpansion

:: Record the start time
set "start_time=!time!"

set exe_path=".\x64\Debug\Kronko.exe" 

set folder_path=".\Kronko\Images"
set output_folder=".\Kronko\Images\output"

set caps_path=".\Kronko\BottleCaps"

set db_json_path=".\Kronko\JSON\db.json"

if exist "%db_json_path%" (
    del "%db_json_path%"
) else (
    echo File "%db_json_path%" does not exist.
)

!exe_path! --nogui -m --import !db_json_path! --caps !caps_path!

for %%f in ("%folder_path%\*.png" "%folder_path%\*.jpg") do (
    set image_name=%%~nxf
    for %%w in (500 1000 1500) do (
        set output_name=%%~nf_output_%%w%%~xf
        set output_file=!output_folder!\!output_name!
        echo !output_name!
        !exe_path! -g -t -b --nogui --input "!folder_path!\!image_name!" --output "!output_file!" --import !db_json_path! --width %%w --res 1024 1024
    )
)

set "end_time=!time!"

call :CalculateDuration "!start_time!" "!end_time!"
echo Script ran for: !duration!

endlocal
exit /b

:CalculateDuration
set "start_time=%~1"
set "end_time=%~2"

for /f "tokens=1-4 delims=:., " %%a in ("%start_time%") do (
    set /a "start_hours=%%a", "start_minutes=%%b", "start_seconds=%%c", "start_milliseconds=%%d"
)

for /f "tokens=1-4 delims=:., " %%a in ("%end_time%") do (
    set /a "end_hours=%%a", "end_minutes=%%b", "end_seconds=%%c", "end_milliseconds=%%d"
)

:: Calculate the total duration in milliseconds
set /a "duration=("end_hours"-"start_hours")*3600000 + ("end_minutes"-"start_minutes")*60000 + ("end_seconds"-"start_seconds")*1000 + ("end_milliseconds"-"start_milliseconds")"

:: Calculate hours, minutes, seconds, and milliseconds
set /a "hours=duration/3600000, duration=duration%%3600000"
set /a "minutes=duration/60000, duration=duration%%60000"
set /a "seconds=duration/1000, milliseconds=duration%%1000"

:: Format the duration as hours:minutes:seconds.milliseconds
set "duration=!hours!:!minutes!:!seconds!.!milliseconds!"
exit /b

::1.54 unthreaded
::0:50 threaded JSONDB
::