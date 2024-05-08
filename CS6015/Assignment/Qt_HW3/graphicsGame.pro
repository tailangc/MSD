SOURCES += \
    bucket.cpp \
    droplet.cpp \
    game1scene.cpp \
    main.cpp

RESOURCES += \
    background.qrc \
    projectRes.qrc \
    rainingMen.qrc

HEADERS += \
    bucket.h \
    cloud.h \
    droplet.h \
    game1scene.h

QT += core gui widgets
QT += multimedia


QMAKE_LFLAGS += -v
