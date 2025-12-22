add_subdirectory(lib)
add_subdirectory(py)

set(SOURCE_FILES
	main.c
	dump.c
	dump_intel.c
	dump_amd.c
)
add_executable(cpuid ${SOURCE_FILES})
target_link_libraries(cpuid libcpuid)

set_target_properties(cpuid
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (NOT DEFINED SKBUILD)
	INSTALL(TARGETS cpuid DESTINATION bin)
endif()
