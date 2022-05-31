add_executable(
  unit_tests
  main.cpp tests_data.cpp tests_matrix.cpp tests_inversed.cpp
)
target_link_libraries(unit_tests PRIVATE linalg)
