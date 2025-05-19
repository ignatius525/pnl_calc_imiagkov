add_executable(test_pnl_calc pnl_calc.t.cpp)

target_link_libraries(test_pnl_calc PRIVATE pnl_calc_src)

target_include_directories(test_pnl_calc PRIVATE ../src)

find_package(GTest REQUIRED)
target_link_libraries(test_pnl_calc PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_pnl_calc)