cmake_minimum_required(VERSION 3.10)
project(UnitTestingC)
set(CMAKE_C_STANDARD 99)

# Libraries
add_library(
        MainLib
        lib/minunit.h
        lib/library.c
        lib/library.h
        lib/Struct.c
        lib/Struct.h
)

add_library(
        ListLibrary
        lib/struct/List.c
        lib/struct/List.h
)

add_library(
        ArrayLibrary
        lib/struct/Array.c
        lib/struct/Array.h
)

add_library(
        NetworkLibrary
        lib/network/Download.c
        lib/network/Download.h
)

add_library(
        FileLibrary
        lib/File.c
        lib/File.h
)

add_library(
        ArgsLibrary
        lib/Args.c
        lib/Args.h
)

add_library(
        HashmapLibrary
        lib/struct/HashMap.c
        lib/struct/HashMap.h
)

add_library(
        TypeLessListLibrary
        lib/struct/TypeLessList.c
        lib/struct/TypeLessList.h
)

add_library(
        TypeLessHashMap
        lib/struct/TypeLessHashMap.c
        lib/struct/TypeLessHashMap.h
)
target_link_libraries(TypeLessHashMap TypeLessListLibrary)

add_library(
        ParallelLibrary
        lib/Parallel.c
        lib/Parallel.h
)
find_package(Threads)
target_link_libraries(ParallelLibrary TypeLessListLibrary ${CMAKE_THREAD_LIBS_INIT})

# Main
add_executable(PoolTests tests/main.c)
target_include_directories(PoolTests PRIVATE lib)
target_link_libraries(PoolTests MainLib ArgsLibrary HashmapLibrary ListLibrary)

# List
add_executable(ListTest tests/test_list.c)
target_include_directories(ListTest PRIVATE lib)
target_link_libraries(ListTest ListLibrary)

# Array
add_executable(ArrayTest tests/test_array.c)
target_include_directories(ArrayTest PRIVATE lib)
target_link_libraries(ArrayTest ArrayLibrary)

# Network
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(NetworkLibrary ${CURL_LIBRARIES})
add_executable(NetworkTest tests/test_network.c)
target_include_directories(NetworkTest PRIVATE lib)
target_link_libraries(NetworkTest NetworkLibrary)

# Files
add_executable(FileTest tests/test_file.c)
target_include_directories(FileTest PRIVATE lib)
target_link_libraries(FileTest FileLibrary)

# HashMap
add_executable(HashmapTest tests/test_hashmap.c)
target_include_directories(HashmapTest PRIVATE lib)
target_link_libraries(HashmapTest HashmapLibrary ListLibrary)

# Typeless HashMap
add_executable(TypelessHashmapTest tests/test_typelesshashmap.c)
target_include_directories(TypelessHashmapTest PRIVATE lib)
target_link_libraries(TypelessHashmapTest TypeLessHashMap)

# Async
add_executable(ParallelTest tests/test_parallel.c)
target_include_directories(ParallelTest PRIVATE lib)
target_link_libraries(ParallelTest ParallelLibrary)
