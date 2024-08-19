cmake_minimum_required(VERSION 3.0)
project(contacts_explorer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp AcceptanceTesting.cpp AcceptanceTesting.hpp)
add_executable(contacts_explorer_run ${SOURCE_FILES})

include_directories(project_lib)
add_subdirectory(project_lib)
target_link_libraries(contacts_explorer_run project_lib)

add_subdirectory(doctest_tests)
