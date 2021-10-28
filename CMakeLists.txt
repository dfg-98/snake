cmake_minimum_required(VERSION 3.0.0)
project(snake 
        VERSION 0.1.0
        DESCRIPTION "Snake game"
        LANGUAGES C)

include(CTest)
enable_testing()

add_executable(snake main.c
                    typedef.h
                    typedef.c
                    board.h
                    board.c
                    snake.h
                    snake.c
                    utils.h )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


