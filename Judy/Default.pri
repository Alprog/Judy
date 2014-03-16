
win32|win64:CONFIG += win
unix:!macx:CONFIG += linux
macx:CONFIG += mac

win:DEFINES += WIN
linux:DEFINES += LINUX
mac:DEFINES += MAC
