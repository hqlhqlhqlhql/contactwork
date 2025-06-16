# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\contactwork_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\contactwork_autogen.dir\\ParseCache.txt"
  "contactwork_autogen"
  )
endif()
