include(AddCatch2)

# Add executable for unit tests
set(TEST_SOURCES
    mining_truck_metrics_test.cpp
    mining_truck_test.cpp
    mining_unload_station_test.cpp
    unload_station_metrics_test.cpp
)
add_executable(unit_tests ${TEST_SOURCES})

# Link against your library and Catch2
target_link_libraries(unit_tests PRIVATE mining_lib Catch2::Catch2WithMain)

# Discover and add tests using Catch2
include(CTest)
include(Catch)
catch_discover_tests(unit_tests)