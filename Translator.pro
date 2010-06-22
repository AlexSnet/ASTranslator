# -------------------------------------------------
# Project created by QtCreator 2009-02-25T13:42:22
# -------------------------------------------------
QT += network \
    script
TARGET = Translator
DESTDIR = bin
TEMPLATE = app

# 3td party libs
include(src/qtsingleapplication/qtsingleapplication.pri)

# Anti-trash ;)
OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp

# Sources
SOURCES += src/main.cpp \
    src/wnd.cpp \
    src/aboutappwnd.cpp \
    src/googleproto.cpp \
    src/settingswnd.cpp \
    src/jsonstreamreader.cpp
HEADERS += src/wnd.h \
    src/aboutappwnd.h \
    src/googleproto.h \
    src/settingswnd.h \
    src/jsonstreamreader.h
FORMS += src/wnd.ui \
    src/settingswnd.ui
RESOURCES += src/resources.qrc

# Some defines for Mac OS X
mac: { 
    QMAKE_INFO_PLIST = res/mac/Info.plist
    RC_FILE = src/res/icon.icns
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
}

# Some defines for Windows
win:RC_FILE = src/res/win.rc

# Other
CODECFORTR = UTF-8
