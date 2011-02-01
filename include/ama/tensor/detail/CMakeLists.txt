file(GLOB ama_tend "*.hpp")
install(FILES ${ama_tend}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/tensor/detail)