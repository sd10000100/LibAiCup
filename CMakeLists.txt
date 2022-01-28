# project(LibAiCup)

# set(LIBAICUP_SRC_LIST main)

# add_executable(LibAiCup ${LIBAICUP_SRC_LIST})
# add_subdirectory(raicHelper)
# target_link_libraries(LibAiCup raicHelper)



cmake_minimum_required(VERSION 3.14)

project("LibAiCup"
    VERSION 0.9.1
    DESCRIPTION "A project with nested library"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(helper)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE helper)
