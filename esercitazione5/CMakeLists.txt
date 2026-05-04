cmake_minimum_required(VERSION 3.20)
project(esercitazione5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()

add_executable(measure_sorts measure_sorts.cpp timecounter.cpp)

## Bubble Sort
add_executable(test_bubblesort test_bubblesort.cpp timecounter.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

## Insertion Sort
add_executable(test_insertionsort test_insertionsort.cpp timecounter.cpp)
add_test(NAME insertionsort COMMAND test_insertionsort)

## Selection Sort
add_executable(test_selectionsort test_selectionsort.cpp timecounter.cpp)
add_test(NAME selectionsort COMMAND test_selectionsort)

## Quick Sort
add_executable(test_quicksort test_quicksort.cpp timecounter.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

## Merge Sort
add_executable(test_mergesort test_mergesort.cpp timecounter.cpp)
add_test(NAME mergesort COMMAND test_mergesort)


## quicksort_hybrid
add_executable(test_quicksorthybrid test_quicksorthybrid.cpp timecounter.cpp)
add_test(NAME quicksorthybrid COMMAND test_quicksorthybrid)
