find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

Python3_add_library(py_cpuid MODULE py_cpuid.c)

set_target_properties(py_cpuid PROPERTIES
	PREFIX ""
	OUTPUT_NAME "cpuid"
)

target_include_directories(py_cpuid PRIVATE ${Python3_INCLUDE_DIRS})

target_link_libraries(py_cpuid PRIVATE Python3::Python)
target_link_libraries(py_cpuid PRIVATE libcpuid)
