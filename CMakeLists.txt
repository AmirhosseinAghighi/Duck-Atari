cmake_minimum_required(VERSION 3.21)
project(final_project_lab C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/Users/Asus/Desktop/quera/ce-class/BP/[SDL]/SDL2-2.28.5/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:/Users/Asus/Desktop/quera/ce-class/BP/[SDL]/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/Users/Asus/Desktop/quera/ce-class/BP/[SDL]/SDL2_ttf-2.20.2/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "C:/Users/Asus/Desktop/quera/ce-class/BP/[SDL]/SDL2_mixer-2.8.0/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDLMIXER_INCLUDE_DIR})


add_executable(final_project_lab main.c cmake-build-debug/Duckatari.rc)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDLMIXER_LIBRARY})
