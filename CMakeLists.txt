CMAKE_MINIMUM_REQUIRED(VERSION 3.16.0)

PROJECT(image_process)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

FIND_PACKAGE( PkgConfig REQUIRED )

PKG_CHECK_MODULES(VLC_PLUGIN REQUIRED vlc-plugin)

EXECUTE_PROCESS( COMMAND pkg-config --variable=pluginsdir vlc-plugin
                 COMMAND tr -d '\n'
                 OUTPUT_VARIABLE VLC_PLUGINS_DIR
)
EXECUTE_PROCESS( COMMAND pkg-config --cflags vlc-plugin
                 COMMAND tr -d '\n'
                 OUTPUT_VARIABLE VLC_PLUGIN_CPP_FLAGS
)
MESSAGE( STATUS "VLC_PLUGINS_DIR: ${VLC_PLUGINS_DIR}" )
MESSAGE( STATUS "VLC_PLUGIN_CPP_FLAGS: ${VLC_PLUGIN_CPP_FLAGS}" )

SET( IMAGE_PROCESS_INSTALL_DIR "${VLC_PLUGINS_DIR}/video_filter" )

# vlc module preprocessor flags
SET( MODULE_CPPFLAGS
  "-DPIC -DMODULE_NAME=${CMAKE_PROJECT_NAME} -DMODULE_NAME_IS_${CMAKE_PROJECT_NAME} -DMODULE_STRING=\\\"${CMAKE_PROJECT_NAME}\\\" ${VLC_PLUGIN_CPP_FLAGS}"
)
# vlc module C flags
SET( MODULE_CFLAGS
  "-std=gnu99 -fPIC -Wall"
)
# vlc module additional optimization C flags
SET( MODULE_CFLAGS_OPTIMIZE
  "-pipe -fvisibility=hidden -ffast-math -funroll-loops -fomit-frame-pointer"
)

IF(CMAKE_BUILD_TYPE STREQUAL "Release")
  SET( MODULE_CFLAGS_ALL "${MODULE_CPPFLAGS} ${MODULE_CFLAGS} ${MODULE_CFLAGS_OPTIMIZE}" )
ELSE()
  SET( MODULE_CFLAGS_ALL "${MODULE_CPPFLAGS} ${MODULE_CFLAGS}" )
ENDIF()

INCLUDE_DIRECTORIES( ${VLC_PLUGIN_INCLUDE_DIRS} "." )
LINK_DIRECTORIES( ${VLC_PLUGIN_LIBRARY_DIRS} )

ADD_LIBRARY( image_process_plugin SHARED image_process.c image_aamr.c image_aamr.h)
SET_TARGET_PROPERTIES( image_process_plugin PROPERTIES COMPILE_FLAGS ${MODULE_CFLAGS_ALL} )
TARGET_LINK_LIBRARIES( image_process_plugin ${VLC_PLUGIN_LIBRARIES}  "m" )
if (WIN32)
  TARGET_LINK_LIBRARIES( image_process_plugin "ws2_32" "kernel32")
endif (WIN32)

ADD_SUBDIRECTORY(aamr)
INCLUDE_DIRECTORIES(aamr/include)

INSTALL( TARGETS image_process_plugin DESTINATION ${IMAGE_PROCESS_INSTALL_DIR} )