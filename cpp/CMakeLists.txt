cmake_minimum_required(VERSION 3.7.2)

project(FurnaceXX VERSION 1.0)

file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/*.cpp 
    ${PROJECT_SOURCE_DIR}/../include/*.hpp
    )

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "${CMAKE_SYSTEM}")
    set(SDL2_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12;
    ${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/SDL2")

    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIBRARIES 
            "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x64/SDL2.lib;
            ${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x64/SDL2main.lib")
        set(SDL2_IMAGE_LIBRARIES 
            "${PROJECT_SOURCE_DIR}/../external/SDL2_image-2.0.5/lib/x64/SDL2_image.lib")
        set(SDL2_MIXER_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_mixer-2.0.4/lib/x64/SDL2_mixer.lib") 
        set(SDL2_TTF_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_ttf-2.0.15/lib/x64/SDL2_ttf.lib")
        set(SDL2_NET_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_net-2.0.1/lib/x64/SDL2_net.lib")
    else ()
        set(SDL2_LIBRARIES 
            "${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x86/SDL2.lib;
            ${PROJECT_SOURCE_DIR}/../external/SDL2-2.0.12/lib/x86/SDL2main.lib")
        set(SDL2_IMAGE_LIBRARIES 
            "${PROJECT_SOURCE_DIR}/../external/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
        set(SDL2_MIXER_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib") 
        set(SDL2_TTF_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
        set(SDL2_NET_LIBRARIES  
            "${PROJECT_SOURCE_DIR}/../external/SDL2_net-2.0.1/lib/x86/SDL2_net.lib")
      
    endif ()

elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "${CMAKE_SYSTEM}")
    message(STATUS "${CMAKE_CURRENT_LIST_DIR}")
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

    INCLUDE(FindPkgConfig)
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0.0)
    PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
    #PKG_SEARCH_MODULE(GLM REQUIRED glm)
endif()

add_executable(FurnaceXX ${SOURCES})

include_directories(
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${SDL2_MIXER_INCLUDE_DIRS} 
    ../include
    )

target_link_libraries(
    FurnaceXX 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_MIXER_LIBRARIES}
    )
