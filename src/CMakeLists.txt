add_subdirectory(lib)
add_subdirectory(py)

add_executable(cpuid main.c dump.c)
target_link_libraries(cpuid libcpuid)

set_target_properties(cpuid
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (NOT DEFINED SKBUILD)
	INSTALL(TARGETS cpuid DESTINATION bin)
endif()
