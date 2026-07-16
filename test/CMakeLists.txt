add_executable(test-main test-main.cpp)
target_link_libraries(test-main PRIVATE Boost::unit_test_framework)
target_compile_features(test-main PRIVATE cxx_std_17)
set_target_properties(test-main PROPERTIES CXX_EXTENSIONS OFF)

add_executable(test-far test-far.cpp)
target_link_libraries(
    test-far
    PRIVATE
    file-manager-core
    Boost::unit_test_framework
)
target_compile_features(test-far PRIVATE cxx_std_17)
set_target_properties(test-far PROPERTIES CXX_EXTENSIONS OFF)

add_test(NAME test-main COMMAND test-main)
add_test(NAME test-far COMMAND test-far)
