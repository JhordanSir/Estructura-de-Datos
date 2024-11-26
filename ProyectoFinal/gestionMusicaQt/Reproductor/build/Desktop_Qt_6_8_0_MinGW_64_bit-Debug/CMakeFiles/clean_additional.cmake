# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Reproductor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Reproductor_autogen.dir\\ParseCache.txt"
  "Reproductor_autogen"
  )
endif()
