cmake_minimum_required(VERSION 3.10)

project(BMP_reader)

set(SRC_LIST 
    src/bmp.c 
    src/stego.c      
    src/main.c)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set_target_properties(${PROJECT_NAME} 
            PROPERTIES 
            C_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Werror")

target_include_directories(${PROJECT_NAME} PRIVATE include)
