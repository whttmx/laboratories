cmake_minimum_required(VERSION 3.10)
project(ProductCommission VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME product_app)

set(SOURCES
    Product.cpp
    product_library.cpp
    main.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
