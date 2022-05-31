add_executable(test_from_example test_from_example.cpp)
target_link_libraries(test_from_example PRIVATE linalg)
configure_file(run_test.sh run_test.sh COPYONLY)
