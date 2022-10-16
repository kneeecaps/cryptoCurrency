cmake_minimum_required(VERSION 3.21.0)

project(cryptoCurrency)

file(GLOB cryptoCurrency_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(cryptoCurrency ${cryptoCurrency_SRC})
