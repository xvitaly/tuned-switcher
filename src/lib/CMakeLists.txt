set(CMAKE_AUTOMOC ON)

set(SOURCES
    tunedmanager/tunedmanager.cpp
)

set(HEADERS
    tunedmanager/tunedmanager.h
)

set(INTERNAL_LIBS
    ${SOURCES}
    ${HEADERS}
    ${MOC_HEADERS}
)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::DBus
)

add_library(tuned-lib STATIC
    ${INTERNAL_LIBS}
)

target_link_libraries(tuned-lib PRIVATE ${EXTERNAL_LIBS})
