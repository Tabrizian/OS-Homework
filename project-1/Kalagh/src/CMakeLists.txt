add_executable(Kalagh.out main.c
    child.c child.h
    mother.c mother.h
    dish.c dish.h
    )

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -g -Wall")
