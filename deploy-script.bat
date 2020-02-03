@ECHO OFF

SETLOCAL

:Loop
IF "%1"=="red" GOTO Red
IF "%1"=="blue" GOTO Blue
IF "%1"=="skills" GOTO Skills

:Blue
SET TEAM=BLUE
SET AUTO=0
touch src\main.cpp
prosv5 make
prosv5 upload --slot 1 --name BLUE
IF "%1"=="blue" GOTO End

:Red
SET TEAM=RED
SET AUTO=0
touch src\main.cpp
prosv5 make
prosv5 upload --slot 2 --name RED
IF "%1"=="red" GOTO End

:Skills
SET TEAM=RED
SET AUTO=1
touch src\main.cpp
prosv5 make
prosv5 upload --slot 3 --name SKILLS
IF "%1"=="skills" GOTO End


:End

ENDLOCAL