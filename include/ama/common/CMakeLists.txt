file(GLOB ama_com "*.hpp")
install(FILES ${ama_com}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/common)