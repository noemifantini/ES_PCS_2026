cmake_minimum_required(VERSION 3.20)
project(esercitazione6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

enable_testing()

add_executable(main main.cpp)

add_executable(test_add_edges test_add_adges.cpp)
add_test(NAME add_edges COMMAND test_add_edges)

add_executable(test_alledges test_alledges.cpp)
add_test(NAME alledges COMMAND test_alledges)

add_executable(test_allnodes test_allnodes.cpp)
add_test(NAME allnodes COMMAND test_allnodes)

add_executable(test_differenza test_differenza.cpp)
add_test(NAME differenza COMMAND test_differenza)

add_executable(test_edge_at test_edge_at.cpp)
add_test(NAME edge_at COMMAND test_edge_at)

add_executable(test_edge_disuguaglianza test_edge_disuguaglianza.cpp)
add_test(NAME edge_disuguaglianza COMMAND test_edge_disuguaglianza)

add_executable(test_edge_minoreab test_edge_minoreab.cpp)
add_test(NAME edge_minoreab COMMAND test_edge_minoreab)

add_executable(test_edge_number test_edge_number.cpp)
add_test(NAME edge_number COMMAND test_edge_number)

add_executable(test_edge_uguali test_edge_uguali.cpp)
add_test(NAME edge_uguali COMMAND test_edge_uguali)

add_executable(test_neighbour test_neighbour.cpp)
add_test(NAME neighbour COMMAND test_neighbour)

add_executable(test_ordinecanonico test_ordinecanonico.cpp)
add_test(NAME ordinecanonico COMMAND test_ordinecanonico)