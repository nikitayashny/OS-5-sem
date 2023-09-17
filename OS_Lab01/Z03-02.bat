@echo off
chcp 65001 > nul

echo -- имя этого bat-файла: %~n0
echo -- этот bat-файл создан: %~t0
echo -- путь bat-файла: %~dpnx0

pause