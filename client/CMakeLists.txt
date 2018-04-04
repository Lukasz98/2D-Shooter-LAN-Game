cmake_minimum_required(VERSION 3.0)

project(sfml-app)

set ( PROJECT_LINK_LIBS  -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lpthread )

include_directories( "usr/include" "include")

add_compile_options(-std=c++11 -w -fpermissive)

file(GLOB SOURCES "sources/*.cpp")
add_executable(sfml-app ${SOURCES})

target_link_libraries(sfml-app ${PROJECT_LINK_LIBS})









#SET(GCC_COVERAGE_COMPILE_FLAGS -std=c++11 -w -fpermissive -Wdeprecated-declarations -Wsign-compare)
#SET(GCC_COVERAGE_COMPILE_FLAGS -std=c++11 -W)
#set (CMAKE_CXX_FLAGS "-std=c++11 -W -fpermissive -Wdeprecated-declarations")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -fpermissive -Wdeprecated-declarations"
#set ( PROJECT_LINK_LIBS sfml-graphics sfml-window sfml-system )
#find_package(SFML 2 REQUIRED system window graphics network audio)
#link_directories( ~/tests/cmakeTest/b/SFML-2.4.2/lib )
#include_directories( ${SFML_INCLUDE_DIR} "include")
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
#SET( CMAKE_CXX_FLAGS  "${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${GCC_COVERAGE_LINK_FLAGS}" )
#add_compile_options(-std=c++11 -W -fpermissive -Wdeprecated-declarations -Wsign-compare)
