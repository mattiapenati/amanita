project(amanita CXX)
cmake_minimum_required(VERSION 2.6)

# module and package
include(CTest)
find_package(Boost REQUIRED)

# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

# sub directories
add_subdirectory(include)
add_subdirectory(test)