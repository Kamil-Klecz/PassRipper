QT       = core
CONFIG  += c++17 cmdline

INCLUDEPATH += $$PWD/minizip-ng

SOURCES += \
    komunikacja.cpp \
    main.cpp \
    manager.cpp \
    worker.cpp

HEADERS += \
    komunikacja.h \
    manager.h \
    worker.h

LIBS = $$PWD/minizip.lib
win32:LIBS += -lbcrypt -ladvapi32
