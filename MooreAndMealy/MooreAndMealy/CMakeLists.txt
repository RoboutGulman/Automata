cmake_minimum_required(VERSION 3.20)

project(convert)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

set(ENTRY_POINT
               "main.cpp")
set(HEADERS_ROOT_PATH
                     "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_ROOT_PATH
                 "${CMAKE_CURRENT_SOURCE_DIR}")
file(
    GLOB_RECURSE SOURCE_LIST
    "${SRC_ROOT_PATH}/*.c*"
)

file(
    GLOB_RECURSE HEADERS_LIST
    "${HEADERS_ROOT_PATH}/*.h*"
)

find_package(Boost 1.80.0)

if(Boost_FOUND)

    include_directories( ${Boost_INCLUDE_DIRS} )

    add_executable(
              ${PROJECT_NAME}
              ${ENTRY_POINT}
              ${SOURCE_LIST}
              ${HEADERS_LIST}
    )

    target_link_libraries( ${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )

endif()

source_group(
            TREE "${SRC_ROOT_PATH}"
            PREFIX "Source Files"
            FILES ${SOURCE_LIST}
)
source_group(
            TREE "${HEADERS_ROOT_PATH}"
            PREFIX "Header Files"
            FILES ${HEADERS_LIST}
)