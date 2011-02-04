file(GLOB ama_ten "*.hpp")
install(FILES ${ama_ten}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ama/tensor)

add_subdirectory(detail)
add_subdirectory(iexp)
add_subdirectory(mul)