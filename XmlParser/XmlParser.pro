TEMPLATE = app
TARGET = XmlParser

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

SOURCES += main.cpp \
    delivery.cpp \
    urls.cpp \
    shopitem.cpp \
    lexer.cpp \
    parser.cpp

HEADERS += \
    delivery.h \
    urls.h \
    shopitem.h \
    lexer.h \
    parser.h

