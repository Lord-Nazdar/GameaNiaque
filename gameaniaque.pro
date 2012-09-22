LIBS += C:\libs\SFML-2.0\lib\libsfml-graphics.a
LIBS += C:\libs\SFML-2.0\lib\libsfml-window.a
LIBS += C:\libs\SFML-2.0\lib\libsfml-main.a
LIBS += C:\libs\SFML-2.0\lib\libsfml-system.a

INCLUDEPATH += C:\libs\SFML-2.0\include

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    layermanager.cpp \
    layer.cpp

HEADERS += \
    layermanager.h \
    layer.h
