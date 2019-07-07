if (BUILD_TESTING)
    add_subdirectory(test)
endif (BUILD_TESTING)

project(libspectacle VERSION ${PACKAGE_VERSION} LANGUAGES C)
set(sources src/args.c src/error.c src/util.c
    src/engine.c src/glfw.c src/glew.c src/io.c src/spmath.c)
configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h @ONLY)
add_library(libspectacle STATIC ${sources})
SET_TARGET_PROPERTIES(libspectacle PROPERTIES PREFIX "")
target_include_directories(libspectacle PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
target_link_libraries(libspectacle glfw GLEW m)
install(TARGETS libspectacle
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
