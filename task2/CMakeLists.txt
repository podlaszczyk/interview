find_package(Catch2 REQUIRED)

add_executable(determinePatternTests
        add-test.cpp)

target_link_libraries(determinePatternTests PRIVATE Catch2::Catch2WithMain)