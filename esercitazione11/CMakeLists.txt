cmake_minimum_required(VERSION 3.20)
project(ese_cicli_min)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")


enable_testing()

add_executable(main main.cpp)



add_executable(test_dijkstra test_dijkstra_path_generico.cpp)

add_test(NAME test_dijkstra COMMAND test_dijkstra)

add_executable(test_ausil_dfs test_dfs_ausil.cpp)
add_test(NAME test_ausil_dfs COMMAND test_ausil_dfs)

add_executable(test_fund_cycles_dfs test_fund_cycles_dfs.cpp)

add_test(NAME test_cicli_dfs COMMAND test_fund_cycles_dfs)

add_executable(test_ausil_dp test_ausil_de_pina.cpp)

add_test(NAME test_ausil_de_pina COMMAND test_ausil_dp)

add_executable(test_de_pina test_de_pina.cpp)

add_test(NAME de_pina COMMAND test_de_pina)

add_executable(test_conv_dp test_de_pina_conv.cpp)

add_test(NAME de_pina_conv COMMAND test_conv_dp)

