file(GLOB ama_teni "*.hpp")
install(FILES ${ama_teni}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/tensor/iexp)