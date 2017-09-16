include(ExternalProject)
ExternalProject_Add(
  openvr
  URL https://github.com/ValveSoftware/openvr/archive/v1.0.10.tar.gz
  URL_MD5 6ab903a6ff347f133fb7754e5fbb64f6
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD 1
)
ExternalProject_Get_Property(openvr SOURCE_DIR)
set(OPENVR_INCLUDE_DIRS ${SOURCE_DIR}/headers CACHE TYPE INTERNAL)
#MESSAGE("OpenVR include path: ${OPENVR_INCLUDE_DIRS}")

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

set_target_properties( driver_openhmd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/linux64"
)

file(COPY driver.vrdrivermanifest DESTINATION ${CMAKE_BINARY_DIR})
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

#setTargetOutputDirectory(${TARGET_NAME})
