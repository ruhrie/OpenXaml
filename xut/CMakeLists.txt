project("xut")

set (CMAKE_CXX_STANDARD 17)

set (SOURCES "xut.cpp")

add_executable(xut ${SOURCES})

target_include_directories(xut PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CXXOPTS_INC})