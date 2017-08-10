QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WordLearningProgram
TEMPLATE = app

HEADERS += \
    database.h \
    encryption.h \
    user.h \
    word.h \
    panelmainmenu.h \
    registerwindow.h \
    loginwindow.h \
    editwordswindow.h \
    learningwindow.h \
    repeatwindow.h

SOURCES += \
    main.cpp \
    user.cpp \
    word.cpp \
    encryption.cpp \
    database.cpp \
    panelmainmenu.cpp \
    registerwindow.cpp \
    loginwindow.cpp \
    editwordswindow.cpp \
    learningwindow.cpp \
    repeatwindow.cpp
