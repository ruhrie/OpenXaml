configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Test.xaml ${CMAKE_CURRENT_BINARY_DIR}/Test.xaml)

add_executable(TestApplication "App.xaml.cpp" "MainPage.xaml.cpp")
target_include_directories(TestApplication PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${OPENXAML_INC}" ${XERCES_INC} ${FREETYPE_INC} ${GLAD_INC} ${GLFW_INC})
target_link_libraries(TestApplication OpenXaml)
set_target_properties(TestApplication
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" 
)

AddXamlSources(TestApplication MainPage.xaml)