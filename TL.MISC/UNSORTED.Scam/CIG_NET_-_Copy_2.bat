title MADE BY JuGG
echo off & cls
color 9
echo  a,  8a
echo  `8, `8)                            ,adPPRg,
echo   8)  ]8                        ,ad888888888b
echo  ,8' ,8'                    ,gPPR888888888888
echo ,8' ,8'                 ,ad8""   `Y888888888P
echo 8)  8)              ,ad8""        (8888888""
echo 8,  8,          ,ad8""            d888""
echo `8, `8,     ,ad8""            ,ad8""
echo  `8, `" ,ad8""            ,ad8""
echo     ,gPPR8b           ,ad8""
echo    dP:::::Yb      ,ad8""
echo    8):::::(8  ,ad8""
echo    Yb:;;;:d888""   
echo    "8ggg8P"      


set /p Input=Enter Ip :
:top
PING -n 1 %Input% | FIND "TTL="
title  ~Giving Patient Cancer~ %Input%
IF ERRORLEVEL 1 (SET OUT=C & echo Painent Has Died From Cancer...     ) ELSE (SET OUT=B)
color %OUT%
ping -t 1 -1 10 127.0.0.1 >nul
:rainbow
color 1
color 2
color 3
color 4
color 5
color 6
color 7
color 8
color 9
color A
color B
color C
color D
color E
color F
GoTo top