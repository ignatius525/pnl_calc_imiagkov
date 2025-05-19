add_library(pnl_calc_src
    pnl_calculator.cpp
)

target_include_directories(pnl_calc_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})