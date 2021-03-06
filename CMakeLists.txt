cmake_minimum_required(VERSION 2.8)
project(ttydisp)

set (CMAKE_CXX_STANDARD 17)

include("./cmake/ffmpeg-config.cmake")
include("./cmake/libvdpau-config.cmake")
find_package(X11)
find_package(Threads)
find_package(ZLIB)

if(MSVC)
	# Visual Studio -- /W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif(CMAKE_COMPILER_IS_GNUXX OR CMAKE_COMPILER_IS_GNUCC)
	# GCC -- -Wall -pedantic
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-implicit-fallthrough -g -Ofast -fno-stack-protector -fno-omit-frame-pointer")
endif()

add_executable(ttydisp ttydisp.cpp)
target_include_directories( ttydisp PRIVATE ${LIBAVFORMAT_INCLUDE_DIR} ${LIBAVCODEC_INCLUDE_DIR} ${LIBAVUTIL_INCLUDE_DIR} ${LIBSWSCALE_INCLUDE_DIR})
target_link_libraries(ttydisp ${LIBAVFORMAT_LIBRARY} ${LIBAVCODEC_LIBRARY} ${LIBAVUTIL_LIBRARY} ${LIBSWSCALE_LIBRARY} )
target_link_libraries(ttydisp ${LIBVDPAU_LIBRARY})
target_link_libraries(ttydisp ${X11_LIBRARIES})
target_link_libraries(ttydisp ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ttydisp ${ZLIB_LIBRARIES})

install(TARGETS ttydisp DESTINATION bin)
