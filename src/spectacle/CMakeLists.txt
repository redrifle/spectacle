set(sources src/spectacle.c)
add_executable(spectacle ${sources})
target_link_libraries(spectacle libspectacle OpenGL glfw)
install(TARGETS spectacle
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
