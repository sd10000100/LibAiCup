project(LibAiCup)

set(LIBAICUP_SRC_LIST main)

add_executable(LibAiCup ${LIBAICUP_SRC_LIST})
add_subdirectory(helper)
target_link_libraries(LibAiCup helper)