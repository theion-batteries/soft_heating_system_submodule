include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(heatingTests
  main.cpp
)
target_link_libraries(heatingTests
  GTest::gtest_main
  GTest::gmock_main
  heatingSystemLib
)
target_include_directories(heatingTests
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../includes/
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
)
#add_test(NAME heatingTests COMMAND heatingTests)
#set_tests_properties(heatingTests PROPERTIES OUTPUT_ON_SUCCESS TRUE)

enable_testing()
include(GoogleTest)
gtest_discover_tests(heatingTests)