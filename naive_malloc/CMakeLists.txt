cmake_minimum_required (VERSION 2.6)
project (main)


ENABLE_TESTING()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )


include_directories(${main_SOURCE_DIR})


file(GLOB main_SRC
		    "*.h"
			 "*.c"
			)

SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


add_executable(main ${main_SRC})

TARGET_LINK_LIBRARIES(main PUBLIC pthread )

