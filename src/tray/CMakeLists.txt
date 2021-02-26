set(CMAKE_AUTOMOC ON)

set(SOURCES
    trayicon/trayicon.cpp
    main.cpp
)

set(HEADERS
    trayicon/trayicon.h
)

qt5_add_resources(QRES
    ../../resources/tuned-switcher.qrc)

set(INTERNAL_LIBS
    ${SOURCES}
    ${HEADERS}
    ${MOC_HEADERS}
    ${QRES}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
    tuned-lib
)

add_executable(tuned-tray ${INTERNAL_LIBS})
target_link_libraries(tuned-tray PRIVATE ${EXTERNAL_LIBS})
