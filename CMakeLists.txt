cmake_minimum_required(VERSION 2.8)

project(localization)

# add cxx flags
add_definitions(-std=c++11 -fPIC)
set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")

aux_source_directory(src SRCS)
include_directories(
  include
)

add_library(hlog SHARED ${SRCS})
target_link_libraries(hlog
  glog
)

add_library(hlog_static ${SRCS})
target_link_libraries(hlog_static
  glog
)
SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build)
IF (BUILD_EXAMPLE)
  add_executable(hlog_example example/main.cpp)

  add_dependencies(hlog_example
    hlog
  )

  target_link_libraries(hlog_example
    hlog
    pthread
    glog
  )

  install(TARGETS hlog_example DESTINATION ${CMAKE_INSTALL_PREFIX}/example)
ENDIF (BUILD_EXAMPLE)



install(FILES include/hlog.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS hlog hlog_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
