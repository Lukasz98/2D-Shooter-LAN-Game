cmake_minimum_required(VERSION 3.0)

project(sfml-app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -fpermissive ")

#link_directories( ~/tests/cmakeTest/b/SFML-2.4.2/lib )
set ( PROJECT_LINK_LIBS  -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lpthread )
#set ( PROJECT_LINK_LIBS sfml-graphics sfml-window sfml-system )

#find_package(SFML 2 REQUIRED system window graphics network audio)

include_directories( "usr/include" "include")
#include_directories( ${SFML_INCLUDE_DIR} "include")



file(GLOB SOURCES "sources/*.cpp")
add_executable(sfml-app ${SOURCES})

target_link_libraries(sfml-app ${PROJECT_LINK_LIBS})
