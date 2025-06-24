QT       += core gui network
QT += widgets
CONFIG  += c++17 cmdline
CONFIG   += console
SOURCES += \
    komunikacja.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    managerwindow.cpp \
    worker.cpp \
    workerwindow.cpp

HEADERS += \
    komunikacja.h \
    mainwindow.h \
    manager.h \
    managerwindow.h \
    worker.h \
    workerwindow.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libzip/build/lib/release/ -lzip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libzip/build/lib/debug/ -lzip
else:unix: LIBS += -L$$PWD/libzip/build/lib/ -lzip

INCLUDEPATH += $$PWD/libzip/lib
DEPENDPATH += $$PWD/libzip/lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libzip/build/lib/release/libzip.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libzip/build/lib/debug/libzip.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libzip/build/lib/release/zip.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libzip/build/lib/debug/zip.lib
else:unix: PRE_TARGETDEPS += $$PWD/libzip/build/lib/libzip.a
INCLUDEPATH += $$PWD/libzip/build

FORMS += \
    mainwindow.ui \
    managerwindow.ui \
    workerwindow.ui
