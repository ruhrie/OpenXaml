project("xut")

set (CMAKE_CXX_STANDARD 17)
set(SOURCES "xut.cpp" "xml/ErrorReader.cpp" "xml/DomLoader.cpp" "xml/UID.cpp" "internal/XamlClass.cpp" "internal/XamlElement.cpp")

add_executable(xut ${SOURCES})

target_include_directories(xut PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CXXOPTS_INC} ${XERCES_INC} ${OPENXAML_INC})
target_link_libraries(xut OpenXaml xerces-c )