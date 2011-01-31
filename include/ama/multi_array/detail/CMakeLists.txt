file(GLOB ama_ma_d "*.hpp")
install(FILES ${ama_ma_d}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/multi_array/detail)