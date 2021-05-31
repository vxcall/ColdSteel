cmake_minimum_required(VERSION 3.17)
project(ColdSteel)

set(CMAKE_CXX_STANDARD 17)

#root dir
FILE(GLOB_RECURSE MAIN_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ColdSteel/*.cpp)
FILE(GLOB_RECURSE MAIN_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ColdSteel/*.h)

#Minhook
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/include)
FILE(GLOB_RECURSE MINHOOK_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/src/*.c)
FILE(GLOB_RECURSE MINHOOK_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/minhook/src/*.h)

#ImGui
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/include)
FILE(GLOB_RECURSE IMGUI_SOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/include/*.cpp)
FILE(GLOB_RECURSE IMGUI_HEADER CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Dependencies/imgui/include/*.h)

#Directx
link_directories($ENV{DXSDK_DIR}/Lib/x64)

add_library(${PROJECT_NAME} SHARED ${MAIN_SOURCE} ${MAIN_HEADER}
         ${MINHOOK_SOURCE} ${MINHOOK_HEADER}
         ${IMGUI_SOURCE} ${IMGUI_HEADER})
target_link_libraries(${PROJECT_NAME} d3d11 d3dcompiler )