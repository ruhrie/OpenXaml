configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Test.xaml ${CMAKE_CURRENT_BINARY_DIR}/Test.xaml)

add_executable(TestApplication "App.xaml.cpp")