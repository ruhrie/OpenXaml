file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/fragment.glsl" FRAGMENT_CODE)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/vertex.glsl" VERTEX_CODE)
configure_file("GL/GLConfig.cpp.in" "GL/GLConfig.cpp")

file(GLOB SOURCES "XamlObjects/*.cpp" "GL/*.cpp" "*.cpp" "XamlEvents/*.cpp" "Environment/*.cpp" "Animation/*.cpp")

set (OPENXAML_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/" PARENT_SCOPE)
set (LOCAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set (PLATFORM_LIBS "")
set (COMP_DEC "")
if (UNIX)
	list(APPEND PLATFORM_LIBS "-lstdc++fs")	
elseif (WIN32)
	list(APPEND COMP_DEC "_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING")
endif()

add_library(OpenXaml STATIC ${SOURCES} "${CMAKE_CURRENT_BINARY_DIR}/GL/GLConfig.cpp")
set_target_properties(OpenXaml 
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(OpenXaml PRIVATE ${LOCAL_INC})
target_link_libraries(OpenXaml PRIVATE ${PLATFORM_LIBS} unofficial::angle::libEGL unofficial::angle::libGLESv2 glfw Freetype::Freetype harfbuzz::harfbuzz)
#target_link_libraries(OpenXaml PRIVATE glad::glad)
if(WIN32)
	target_compile_definitions(OpenXaml PRIVATE ${COMP_DEC})
endif()

file(GLOB HEADERS "include/OpenXaml")

install(TARGETS OpenXaml EXPORT OpenXaml DESTINATION "lib")
install(DIRECTORY ${HEADERS} DESTINATION "include")











