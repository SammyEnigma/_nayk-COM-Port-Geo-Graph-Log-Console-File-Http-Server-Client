QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_teststdalg.cpp

INCLUDEPATH *= $${PWD}/../../inc \
        $${PWD}/../../src

HEADERS *= $${PWD}/../../inc/std_alg.h

SOURCES *= $${PWD}/../../src/std_alg.cpp
