cmake_minimum_required(VERSION 3.20)
project(progetto_PCS)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 CONFIG REQUIRED)

enable_testing()

add_executable(main main.cpp)
target_link_libraries(main PUBLIC Eigen3::Eigen)

add_executable(test_netlist test_netlist.cpp)

add_test(NAME test_netlist COMMAND test_netlist)

add_executable(test_grafi_netlist test_grafi_netlist.cpp)

add_test(NAME test_grafi_netlist COMMAND test_grafi_netlist)

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

add_executable (test_gc test_gradiente_coniugato.cpp)
target_link_libraries (test_gc PUBLIC Eigen3::Eigen)
add_test (NAME test_cg COMMAND test_gc)

add_executable (test_build_matrici test_build_matrici.cpp)
target_link_libraries(test_build_matrici PUBLIC Eigen3::Eigen)
add_test (NAME test_build_mat COMMAND test_build_matrici)