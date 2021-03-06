project("xut")

set (CMAKE_CXX_STANDARD 17)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Schema/XamlStandard.xsd" XAML_STANDARD_XSD)
configure_file("Schema/XamlStandard.cpp.in" "Schema/XamlStandard.cpp")
file (GLOB SOURCES "*.cpp" "xml/*.cpp" "internal/*.cpp" "${CMAKE_CURRENT_BINARY_DIR}/Schema/*.cpp" "Formatter/*.cpp")
add_executable(xut ${SOURCES})

set_target_properties(xut
	PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" 
)

target_include_directories(xut PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENXAML_INC})
target_link_libraries(xut PRIVATE OpenXaml  xerces_xerces-c XercesC::XercesC cxxopts::cxxopts)

install(TARGETS xut EXPORT OpenXaml DESTINATION "bin")

set(xutLocation $<TARGET_FILE:xut> PARENT_SCOPE)