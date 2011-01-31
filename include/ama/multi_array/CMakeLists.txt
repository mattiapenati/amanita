file(GLOB ama_ma "*.hpp")
install(FILES ${ama_ma}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/multi_array)

add_subdirectory(detail)