project(DBSCAN_test)
cmake_minimum_required(VERSION 3.5)

find_package(OpenCV REQUIRED)

add_subdirectory(DBSCAN)

add_executable(
    dbscantest
    dbscan_test.cpp
)

target_link_libraries(dbscantest ${OpenCV_LIBS})
target_link_libraries(dbscantest DBSCAN)
