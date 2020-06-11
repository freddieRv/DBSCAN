cmake_minimum_required(VERSION 3.9)
project(DBSCAN VERSION 1.0.1 DESCRIPTION "A C++ implementation of DBSCAN")

add_library(
    DBSCAN SHARED
    src/DBSCAN.cpp
)

set_target_properties(
    DBSCAN PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/DBSCAN.h
)

target_include_directories(DBSCAN PUBLIC include)

target_link_libraries(DBSCAN ${DBSCAN_LIBRARIES})

install(
    TARGETS DBSCAN
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES ${CMAKE_BINARY_DIR}/DBSCAN.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
