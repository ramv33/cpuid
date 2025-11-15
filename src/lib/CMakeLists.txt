add_library(libcpuid
	SHARED
	cpuid.c
)

target_include_directories(libcpuid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
