find_package(glfw3 CONFIG REQUIRED)

find_package(XercesC CONFIX REQUIRED)

find_package(Freetype CONFIG REQUIRED)

find_package(harfbuzz CONFIG REQUIRED)

set(GLAD_INC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include PARENT_SCOPE)

find_package(cxxopts CONFIG REQUIRED)
