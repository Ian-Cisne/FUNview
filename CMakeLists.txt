cmake_minimum_required (VERSION 3.1)
project (curdbis)

add_executable(main
  src/main.cpp
  src/render.cpp
  src/window.cpp
  src/global.cpp
  src/config.cpp
)
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_compile_options(main PRIVATE -Wall)

# glfw
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)
 
# glad
add_subdirectory(lib/glad EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glad)
