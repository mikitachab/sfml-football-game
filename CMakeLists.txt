cmake_minimum_required(VERSION 3.13)

project(sfml-app)

add_executable(sfml-app main.cpp)
target_link_libraries(sfml-app PRIVATE sfml-graphics
                               PRIVATE sfml-window 
                               PRIVATE sfml-system
)
