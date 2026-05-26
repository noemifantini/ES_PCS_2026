cmake_minimum_required(VERSION 3.20)
project(esercitazione10)
 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
 
# Trova Eigen3
find_package(Eigen3 REQUIRED)
 
# Compila il test
add_executable(test_gradiente_coniugato test_gradiente.cpp)
 
# Collega Eigen
target_link_libraries(test_gradiente_coniugato Eigen3::Eigen)
 
# Test
enable_testing()
add_test(NAME gradiente_coniugato COMMAND test_gradiente_coniugato)