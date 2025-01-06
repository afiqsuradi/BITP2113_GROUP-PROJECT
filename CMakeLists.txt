cmake_minimum_required(VERSION 3.10)
project(aa_project)

file(GLOB SOURCES
        src/controllers/*.cpp
        src/models/*.cpp
        src/libs/*.cpp
        src/utils/*.cpp
)

add_executable(aa_project src/main.cpp ${SOURCES})

target_include_directories(aa_project
        PRIVATE
        src/utils
        src/static
        src/models
        src/libs
        src/controllers
        external/nlohmann
)