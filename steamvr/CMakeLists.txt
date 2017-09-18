project (driver_openhmd)
set(TARGET_NAME driver_openhmd)

include_directories(${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${OPENVR_INCLUDE_DIRS})

add_library(${TARGET_NAME} SHARED
  driverlog.cpp
  driverlog.h
  driver_openhmd.cpp
)

#add_definitions(-DDRIVER_OPENHMD_EXPORTS)

target_link_libraries(${TARGET_NAME}
  ${CMAKE_DL_LIBS}
  openhmd-static
)

# don't add lib prefix to driver_openhmd.so
SET_TARGET_PROPERTIES(driver_openhmd PROPERTIES PREFIX "")

if (WIN32)
  # FIXME need to account for different architectures
  if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(PLUGINDIR_LIBRARIES ${CMAKE_BINARY_DIR}/bin/win64 CACHE TYPE INTERNAL)
  else()
    set(PLUGINDIR ${CMAKE_BINARY_DIR}/bin/win32 CACHE TYPE INTERNAL)
  endif()
elseif(APPLE)
  if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(PLUGINDIR_LIBRARIES ${CMAKE_BINARY_DIR}/bin/osx64 CACHE TYPE INTERNAL)
  else()
    set(PLUGINDIR ${CMAKE_BINARY_DIR}/bin/osx32 CACHE TYPE INTERNAL)
  endif()
elseif(NOT ANDROID)
  if ("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(PLUGINDIR_LIBRARIES ${CMAKE_BINARY_DIR}/bin/linux64 CACHE TYPE INTERNAL)
  else()
    set(PLUGINDIR ${CMAKE_BINARY_DIR}/bin/linux32 CACHE TYPE INTERNAL)
  endif()

endif()

set_target_properties( driver_openhmd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/linux64"
)

file(COPY driver.vrdrivermanifest DESTINATION ${CMAKE_BINARY_DIR})
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

#setTargetOutputDirectory(${TARGET_NAME})
