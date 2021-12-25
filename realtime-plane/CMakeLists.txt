cmake_minimum_required (VERSION 2.8)
project(OgreTutorialsSample)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lfreetype -lcurl -lOIS -ljsoncpp")

## [discover_ogre]
# specify which version and components you need
find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)

# copy resource.cfg next to our binaries where OGRE looks for it
file(COPY resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY content DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add the source files as usual

add_library(MovingObject src/MovingObject.cpp)
target_link_libraries(MovingObject ${OGRE_LIBRARIES})

add_library(LiveTraffic src/LiveTraffic.cpp)
target_link_libraries(LiveTraffic)

add_library(ThreadData src/ThreadData.cpp)
target_link_libraries(ThreadData LiveTraffic)

add_library(InputHandler src/InputHandler.cpp)
target_link_libraries( InputHandler ${OGRE_LIBRARIES})

add_library(World src/World.cpp) 
target_link_libraries(World ThreadData MovingObject ${OGRE_LIBRARIES})

add_library(Camera src/Camera.cpp)
target_link_libraries(Camera ${OGRE_LIBRARIES})


add_library(MainListener src/MainListener.cpp)
target_link_libraries(MainListener Camera ${OGRE_LIBRARIES})

add_library(MainSimulator src/MainSimulator.cpp)
target_link_libraries(MainSimulator MainListener World ${OGRE_LIBRARIES})


# this also sets the includes and pulls third party dependencies
## [discover_ogre]

add_executable(1_FirstScene src/main.cpp)

target_link_libraries(1_FirstScene MainSimulator InputHandler ${OGRE_LIBRARIES} curl jsoncpp) 