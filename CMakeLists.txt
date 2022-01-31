cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

project(ClearTemp)

find_package(nlohmann_json CONFIG REQUIRED)

add_executable(
    ClearTemp src/main.cpp 
    src/tools/api.cpp
    src/tools/flags.cpp
    src/tools/utils.cpp
    include/api.hpp
    include/flags.hpp
    include/utils.hpp
)

# file(COPY res/ DESTINATION "${CMAKE_BINARY_DIR}")

target_link_libraries(ClearTemp PRIVATE nlohmann_json::nlohmann_json)