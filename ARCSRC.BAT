@echo off
cls 
echo Archiving Pentagram Source!

pkzip -u source *.bat *.c *.h \c\incl\pent*.h

echo.
echo All Done!
