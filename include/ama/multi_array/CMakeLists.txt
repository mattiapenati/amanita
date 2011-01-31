file(GLOB ama_ma "*.hpp")
install(FILES ${ama_ma}
    DESTINATION ${CMAKE_INSTALL_DIR}/include/ama/multi_array)