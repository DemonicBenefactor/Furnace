cmake_minimum_required(VERSION 3.7.2)

project(FurnaceXX VERSION 1.0)

file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/*.cpp 
    ${PROJECT_SOURCE_DIR}/../include/*.hpp
    )
find_package(OpenGL REQUIRED)
set(TINYXML2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/tinyxml2")
set(TINYGLTF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/tinygltf")
set(COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS};GLEW_STATIC")
    add_compile_definitions(${COMPILE_DEFINITIONS})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows" AND NOT MINGW)
    message(STATUS "${CMAKE_SYSTEM}")

    set(SDL2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12;${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/SDL2")
    set(SDL2_IMAGE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2_image-2.0.5")
    set(SDL2_MIXER_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2_mixer-2.0.4")
    set(SDL2_TTF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2_ttf-2.0.15")
    set(SDL2_NET_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2_net-2.0.1")
    set(GLM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/glm")
    set(GLEW_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/glew-2.1.0/include")

    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)

            set(SDL2_LIBRARIES 
            "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x64/SDL2.lib;${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x64/SDL2main.lib")
            set(SDL2_IMAGE_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_image-2.0.5/lib/x64/SDL2_image.lib")
            set(SDL2_MIXER_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_mixer-2.0.4/lib/x64/SDL2_mixer.lib") 
            set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_ttf-2.0.15/lib/x64/SDL2_ttf.lib")
            set(SDL2_NET_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_net-2.0.1/lib/x64/SDL2_net.lib")
            set(GLEW_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/glew-2.1.0/lib/Release/x64/glew32s.lib")
    else ()
	        set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x86/SDL2.lib;${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x86/SDL2main.lib")
            set(SDL2_IMAGE_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
            set(SDL2_MIXER_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib") 
            set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
            set(SDL2_NET_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/SDL2_net-2.0.1/lib/x86/SDL2_net.lib")
            set(GLEW_LIBRARIES "${PROJECT_SOURCE_DIR}/../external/glew-2.1.0/lib/Release/Win32/glew32s.lib")
    endif ()

elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "${CMAKE_SYSTEM}")
    message(STATUS "${CMAKE_CURRENT_LIST_DIR}")
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0.0)
    PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
    PKG_SEARCH_MODULE(GLEW glew) #not required for gles2 on arm

elseif (MINGW)
    message(STATUS "Starting MinGW setup")
	set(COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS};SDL_MAIN_HANDLED;MINGW")
    add_compile_definitions(${COMPILE_DEFINITIONS})
	set(GLM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/glm")
	set(GLEW_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/glew-2.1.0/include")
	set(GLEW_SOURCE "${PROJECT_SOURCE_DIR}/../external/glew-2.1.0/src/glew.c")
	link_directories(D:/MinGW/lib)
	
endif ()




include_directories(
    ${TINYXML2_INCLUDE_DIRS}
    ${TINYGLTF_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ../include
    )

add_library(TINYXML2_LIBRARIES STATIC "${TINYXML2_INCLUDE_DIRS}/tinyxml2.cpp")
add_executable(FurnaceXX ${SOURCES})
	
if (MINGW)
	#This assumes you have installed all the sdl libs manually to the mingw lib folder
	
	add_library(GLEW32 STATIC "${GLEW_SOURCE}")
	set(GLEW_LIBRARIES "${PROJECT_SOURCE_DIR}/../libGLEW32.a")
	target_link_libraries(FurnaceXX "-Wl,--no-undefined -Wl,--dynamicbase -Wl,--nxcompat \
        ${GLEW_LIBRARIES} ${TINYXML2_LIBRARIES} \
        -lSDL2main -lSDL2 -lSDL2_image -lopengl32 \
        -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 \
        -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid \
        -static-libgcc -static-libstdc++")

else()
target_link_libraries(
    FurnaceXX 
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${TINYXML2_LIBRARIES}
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}  
    ${SDL2_MIXER_LIBRARIES}    
    )
endif()
