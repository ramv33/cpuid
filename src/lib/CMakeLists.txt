add_library(libcpuid
	STATIC
	cpuid.c
)

set_target_properties(libcpuid PROPERTIES PREFIX "")
set_target_properties(libcpuid PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(libcpuid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
