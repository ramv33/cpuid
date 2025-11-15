add_subdirectory(lib)
add_subdirectory(py)

add_executable(cpuid main.c)
target_link_libraries(cpuid libcpuid)
