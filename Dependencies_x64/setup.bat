@setx GameEngineDep "%CD%"
@if errorlevel 1 @c:\windows\system32\setx GameEngineDep "%CD%"
@if errorlevel 1 (echo "Critical error: unable to configure environment...") else echo "Configuration done"
@pause
