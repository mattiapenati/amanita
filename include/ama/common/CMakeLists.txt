file(GLOB ama_com "*.hpp")
install(FILES ${ama_com}
    DESTINATION ${CMAKE_INSTALL_DIR}/include/ama/common)