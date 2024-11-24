cmake_minimum_required(VERSION 3.15)
project(JSONServerCLient_Task)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/conan/build/Release/generators/conan_toolchain.cmake")
include(${CMAKE_TOOLCHAIN_FILE})

include_directories(include)
set(SOURCES src/main.cpp src/Author.cpp src/Blog.cpp src/JsonServerClient.cpp src/AuthorCRUD.cpp src/BlogCRUD.cpp)

find_package(nlohmann_json REQUIRED)
find_package(cpr REQUIRED)
find_package(Boost REQUIRED)
add_executable(JSONServerCLient_Task ${SOURCES})

target_include_directories(JSONServerCLient_Task PRIVATE ${CONAN_INCLUDE_DIRS})
target_link_libraries(JSONServerCLient_Task nlohmann_json::nlohmann_json)
target_link_libraries(JSONServerCLient_Task cpr::cpr)
target_link_libraries(JSONServerCLient_Task Boost::boost)

add_custom_target(run
    COMMAND JSONServerCLient_Task
    DEPENDS JSONServerCLient_Task
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
