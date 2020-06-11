project(DBSCAN_test)
cmake_minimum_required(VERSION 3.5)

add_subdirectory(DBSCAN)

add_executable( dbscantest
    dbscan_test.cpp
)

target_link_libraries(dbscantest DBSCAN)
