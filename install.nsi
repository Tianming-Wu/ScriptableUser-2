;NSIS Installer for scriptable user.

InstallDir "C:\ScUserEngine"
Icon "icon.ico"

Page components
Page directory
Page license

;------Inst Options-------

Section "Main"
    File "x64\Release\SUCore.dll"
    File "x64\Release\SUEngine.exe"
SectionEnd