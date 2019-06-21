#-------------------------------------------------
#
# Файл для подключения к qmake-файлу всех проектов
#
#-------------------------------------------------

# каталоги для поиска подключаемых файлов:
INCLUDEPATH *= $${PWD}/inc
INCLUDEPATH *= $${PWD}/src

# заголовочные:
HEADERS *= \
    $${PWD}/inc/crypto.h \
    $${PWD}/inc/log.h \
    $${PWD}/inc/system_utils.h \
    $${PWD}/inc/hw_utils.h \
    $${PWD}/inc/filesys.h \
    $${PWD}/inc/http.h \
    $${PWD}/inc/http_server.h \
    $${PWD}/inc/convert.h \
    $${PWD}/inc/geo.h

# исходники:
SOURCES *= \
    $${PWD}/src/crypto.cpp \
    $${PWD}/src/system_utils.cpp \
    $${PWD}/src/hw_utils.cpp \
    $${PWD}/src/filesys.cpp \
    $${PWD}/src/log.cpp \
    $${PWD}/src/http_server.cpp \
    $${PWD}/src/convert.cpp \
    $${PWD}/src/geo.cpp

# если подключен драйвер сети:
contains( QT, network ) {
    HEADERS *= $${PWD}/inc/http_client.h
    SOURCES *= $${PWD}/src/http_client.cpp
}

# если подключены виджеты:
contains( QT, widgets ) {
    HEADERS *= \
        $${PWD}/inc/highlighter.h \
        $${PWD}/inc/gui_utils.h \
        $${PWD}/inc/ex_controls.h \
        $${PWD}/inc/graph.h

    SOURCES *= \
        $${PWD}/src/highlighter.cpp \
        $${PWD}/src/gui_utils.cpp \
        $${PWD}/src/ex_controls.cpp \
        $${PWD}/src/graph.cpp
}

# если подключен драйвер com-порта:
contains( QT, serialport ) {
    HEADERS *= $${PWD}/inc/com_port.h
    SOURCES *= $${PWD}/src/com_port.cpp
}

# если подключен sql:
contains( QT, sql ) {
    HEADERS *= $${PWD}/inc/db_client.h
    SOURCES *= $${PWD}/src/db_client.cpp
}

# если подключены charts:
contains( QT, charts ) {
    HEADERS *= $${PWD}/inc/diagram.h
    SOURCES *= $${PWD}/src/diagram.cpp
}

contains( CONFIG, console ) {
    HEADERS *= $${PWD}/inc/console.h
    SOURCES *= $${PWD}/src/console.cpp
}

unix:BUILD_DATE = '$(shell date +%Y-%m-%d)'
win32:BUILD_DATE = '$(shell echo %DATE:~6,4%-%DATE:~3,2%-%DATE:~0,2%)'
DEFINES += APP_BUILD_DATE=\\\"$$BUILD_DATE\\\"

# для HWUtils:
win32:LIBS += -lKernel32 -lPsapi
