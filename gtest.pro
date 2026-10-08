QT += core

CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/lib -lgtest -lgtest_main

SOURCES += test_gtest.cpp \
	calculatorengine.cpp

HEADERS += calculatorengine.h
