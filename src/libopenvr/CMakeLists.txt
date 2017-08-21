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
