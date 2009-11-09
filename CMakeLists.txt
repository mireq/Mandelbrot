PROJECT(mandelbrot C CXX)

cmake_minimum_required(VERSION 2.4)
cmake_policy(SET CMP0003 NEW)

SET (GMP_REQUIRED)
FIND_PATH(GMP_INCLUDE_DIR NAMES gmp.h)

FIND_LIBRARY(GMP_LIBRARY NAMES gmp)

IF (GMP_INCLUDE_DIR AND GMP_LIBRARY)
   SET(GMP_FOUND TRUE)
ENDIF (GMP_INCLUDE_DIR AND GMP_LIBRARY)

IF (GMP_FOUND)
  IF (NOT GMP_FIND_QUIETLY)
    MESSAGE(STATUS "Found GMP: ${GMP_LIBRARY}")
  ENDIF (NOT GMP_FIND_QUIETLY)
ELSE (GMP_FOUND)
  IF (GMP_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find GMP")
  ENDIF (GMP_FIND_REQUIRED)
ENDIF (GMP_FOUND)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -Wall -fexceptions -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "-O3 -ffast-math -g3 -ggdb -Wall -Wextra -fexceptions -DDEBUG")

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "Configured to compile including full debug information in the executables")
	add_definitions(-DQT_DEBUG)
else(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "Configured to compile including debug information in the executables")
	set(CMAKE_BUILD_TYPE Release)
	add_definitions(-DQT_NO_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_BINARY_DIR}/src"
	${QT_INCLUDES}
)

set(mandelbrot_SRCS
	main.cpp
	MainWindow.cpp
	MandelbrotWidget.cpp
	RenderThread.cpp
	SettingsWidget.cpp
)

set(mandelbrot_MOC_HDRS
	MainWindow.h
	MandelbrotWidget.h
	RenderThread.h
	SettingsWidget.h
)

set(mandelbrot_TRANS
	locale/mandelbrot_sk_SK.ts)

qt4_wrap_cpp(mandelbrot_MOC_SRCS ${mandelbrot_MOC_HDRS})
#qt4_wrap_ui(mandelbrot_UIS_SRCS ${mandelbrot_UIS})
#qt4_add_resources(mandelbrot_QRC_SRCS ${mandelbrot_QRC})
qt4_add_translation(lrelease_outputs ${mandelbrot_TRANS})

add_executable(mandelbrot
	${mandelbrot_SRCS}
	${mandelbrot_MOC_SRCS}
	${lrelease_outputs}
)

target_link_libraries(mandelbrot ${QT_LIBRARIES} ${GMP_LIBRARY})

