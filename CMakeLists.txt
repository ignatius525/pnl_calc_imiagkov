cmake_minimum_required(VERSION 3.10)
project(pnl_calc)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(pnl_calc main.cpp)
target_link_libraries(pnl_calc PRIVATE pnl_calc_src)

enable_testing()
add_subdirectory(test)

configure_file(${CMAKE_SOURCE_DIR}/data/moretickers.csv
               ${CMAKE_BINARY_DIR}/data/moretickers.csv COPYONLY)