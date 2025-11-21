add_subdirectory(lib)
add_subdirectory(py)

add_executable(cpuid main.c)
target_link_libraries(cpuid libcpuid)

set_target_properties(cpuid
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
