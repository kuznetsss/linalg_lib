add_executable(
  unit_tests
  main.cpp tests_data.cpp
)
target_link_libraries(test_from_example PRIVATE linalg)
