@echo off
echo all params: %1, %2
echo mode: %1
echo file name: %2

if "%1"=="" (goto case1) else (goto case2)

:case1
    echo operation = {create, delete}
    echo name = file_name
    goto exit

:case2
    if "%2"=="" (goto case3) else (goto case4)

:case3
    echo no file name
    goto exit

:case4
if "%1" == "create" (goto createcase)
if "%1" == "delete" (goto deletecase) else (goto operationcase)
:operationcase
    echo incorrect operation
    goto exit

:createcase
if exist %2 (goto casefound)
copy /b NUL %2 > NUL
echo file %2 was created
goto exit

:deletecase
if not exist %2 (goto casenotfound)
del %2
echo file %2 was deleted
goto exit

:casefound
echo dile %2 is already exists
goto exit

:casenotfound
echo file %2 not found
goto exit

:exit