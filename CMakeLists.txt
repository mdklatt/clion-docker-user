cmake_minimum_required(VERSION 3.15)
project(clion_docker_user)

add_executable(clion_docker_user main.cpp)
target_compile_features(clion_docker_user PRIVATE cxx_std_17)
