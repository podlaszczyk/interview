find_package(Catch2 REQUIRED)

add_subdirectory(DeterminePattern)

add_executable(determinePatternTests
        add-test.cpp)

target_link_libraries(determinePatternTests PUBLIC DeterminePattern)

target_link_libraries(determinePatternTests PRIVATE Catch2::Catch2WithMain)