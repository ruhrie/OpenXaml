configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Test.xaml ${CMAKE_CURRENT_BINARY_DIR}/Test.xaml)

add_executable(TestApplication "App.xaml.cpp" "MainPage.xaml.cpp")

set_target_properties(TestApplication
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" 
)