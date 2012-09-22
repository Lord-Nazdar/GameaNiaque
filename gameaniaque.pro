LIBS += C:\QtSDK\mingw\lib\SFML\libsfml-graphics.a
LIBS += C:\QtSDK\mingw\lib\SFML\libsfml-window.a
LIBS += C:\QtSDK\mingw\lib\SFML\libsfml-main.a
LIBS += C:\QtSDK\mingw\lib\SFML\libsfml-system.a
INCLUDEPATH += C:\QtSDK\mingw\include\SFML

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    layermanager.cpp \
    layer.cpp

HEADERS += \
    layermanager.h \
    layer.h
