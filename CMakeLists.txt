project(code-aw)
set (CMAKE_CXX_STANDARD 17)


add_executable(main main.cpp)
add_executable(main_p parallel.cpp)
add_executable(test test.cpp)