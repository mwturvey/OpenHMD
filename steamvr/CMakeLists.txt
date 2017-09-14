project (driver_openhmd)
set(TARGET_NAME driver_openhmd)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(${TARGET_NAME} SHARED
  driverlog.cpp
  driverlog.h
  driver_openhmd.cpp
)

#add_definitions(-DDRIVER_OPENHMD_EXPORTS)

target_link_libraries(${TARGET_NAME}
  ${OPENVR_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

# don't add lib prefix to driver_openhmd.so
SET_TARGET_PROPERTIES(driver_openhmd PROPERTIES PREFIX "")

set_target_properties( driver_openhmd
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/linux64"
)

configure_file(driver.vrdrivermanifest ${CMAKE_BINARY_DIR} COPYONLY)

#setTargetOutputDirectory(${TARGET_NAME})
