file(GLOB ama_tenm "*.hpp")
install(FILES ${ama_tenm}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/tensor/mul)