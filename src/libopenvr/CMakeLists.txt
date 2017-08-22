project (openvr_api)
include_directories(${CMAKE_BINARY_DIR}/include)
link_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})
set(openvr_source_files
	${CMAKE_CURRENT_LIST_DIR}/openvr_api_public.cpp
	${CMAKE_CURRENT_LIST_DIR}/hmderrors_public.cpp
)
add_library(openvr_api SHARED ${openvr_source_files})
target_link_libraries(openvr_api PRIVATE openhmd-shared m)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_DIR}/)


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
string(REPLACE "libGLEWd.so" "libGLEW.so" GLEW_LIBRARIES "${GLEW_LIBRARIES}")
include_directories(${SDL2_INCLUDE_DIR})
add_definitions(-DLINUX -DPOSIX)
file(GLOB SHARED_SRC_FILES
  ./shared/*.cpp
  ./shared/*.h
)
add_executable(hellovr_opengl
  ${SHARED_SRC_FILES}
  hellovr_opengl_main.cpp
)
target_link_libraries(hellovr_opengl
  openvr_api
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARY}
  ${EXTRA_LIBS}
  dl
)
install (FILES cube_texture.png DESTINATION ${CMAKE_BINARY_DIR}) #TODO
