@setx GameEngineDep "%CD%\Dependencies_x64"
@if errorlevel 1 @c:\windows\system32\setx GameEngineDep "%CD%"
@if errorlevel 1 (echo "Critical error: unable to configure dependencies variable...") 
@setx GameEngineRes "%CD%\Ressources"
@if errorlevel 1 setx GameEngineRes "%CD%"
@if errorlevel 1 (echo "Critical error: unable to configure ressources variable...") else echo "Configuration done"
@echo copy Dlls 
@xcopy /D Dependencies_x64\bin\Release\*.dll* Project\x64\Release 
@xcopy /D Dependencies_x64\bin\Debug\*.dll* Project\x64\Debug  

@pause


::@setx GameEngineProj "%CD%\Project"
::@if errorlevel 1 setx GameEngineProj "%CD%"
::@if errorlevel 1 (echo "Critical error: unable to configure project variable...")
::@set a=Dependencies_x64\lib\Release\*.dll*
::@set b=Dependencies_x64\lib\Debug\*.dll* 
::@set c=Project\x64\Release
::@set d=Project\x64\Debug