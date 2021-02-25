cmake_minimum_required(VERSION 3.10)

project(tuned-switcher CXX)

find_package(Qt5 5.7.0 COMPONENTS Widgets Core Gui DBus REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SRC_FILES
    # Sources
    src/mainwindow.cpp
    src/main.cpp
    src/tunedmanager.cpp

    # Headers
    src/mainwindow.h
    src/tunedmanager.h
)

qt5_wrap_ui(UI_HEADERS
    # Dialogs
    src/mainwindow.ui)

qt5_add_resources(QRES
    resources/tuned-switcher.qrc)

set(APP_DEPS
    ${SRC_FILES}
    ${UI_HEADERS}
    ${MOC_HEADERS}
    ${QRES})

set(QT_LIBS
    Qt5::Widgets
    Qt5::DBus)

add_executable(tuned-switcher ${APP_DEPS})
target_link_libraries(tuned-switcher ${QT_LIBS})
