file(GLOB ama "*.hpp")
install(FILES ${ama}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama)

add_subdirectory(common)
add_subdirectory(multi_array)
add_subdirectory(tensor)