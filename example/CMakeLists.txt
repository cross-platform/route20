project(route20-example)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB srcs *.cpp)

add_executable(
    ${PROJECT_NAME}
    ${srcs}
)
