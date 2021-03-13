cmake_minimum_required(VERSION 3.15)
project(nPlayerConnect4)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

include_directories(/home/dan/CLionProjects/Game2D)
link_directories(/home/dan/CLionProjects/Game2D/cmake-build-debug/)

add_executable(nPlayerConnect4 main.cpp Engine.cpp Engine.h Server.cpp Server.h Client.cpp Client.h MainMenu.cpp MainMenu.h ImageLoder.cpp ImageLoder.h FontInfo.h ConnectMenu.cpp ConnectMenu.h Lobby.cpp Lobby.h Board.cpp Board.h Version.h SinglePlayerMenu.cpp SinglePlayerMenu.h Options.cpp Options.h)

INCLUDE(FindPkgConfig)

find_package(X11 REQUIRED)
find_package(Threads)
find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)#was glfw3
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)

include_directories("~/CLionProjects/asio/")
include_directories(${X11_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
#target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${PNG_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} /home/dan/CLionProjects/Game2D/cmake-build-debug/libGame2D.so)

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})