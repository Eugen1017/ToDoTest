# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ToDoTest_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ToDoTest_autogen.dir/ParseCache.txt"
  "ToDoTest_autogen"
  )
endif()
