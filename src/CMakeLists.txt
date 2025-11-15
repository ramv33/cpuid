# cmake_minimum_required(VERSION 3.23)
#
# project(cpuid)

add_executable(cpuid)
target_sources(cpuid
  PRIVATE
  cpuid.c
  main.c
)
