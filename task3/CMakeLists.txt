cmake_minimum_required(VERSION 3.4)
project(task3_rational_)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES rational.cpp)
set(HEADERS rational.h)
add_library(rational ${SOURCES} ${HEADERS})
install (TARGETS rational DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES rational.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install (FILES rational.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
