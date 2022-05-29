add_executable(
  unit_tests
  main.cpp tests_data.cpp
)
target_link_libraries(unit_tests PRIVATE linalg)
