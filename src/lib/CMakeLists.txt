add_library(libcpuid
	SHARED
	cpuid.c
)

set_target_properties(libcpuid PROPERTIES PREFIX "")

target_include_directories(libcpuid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
