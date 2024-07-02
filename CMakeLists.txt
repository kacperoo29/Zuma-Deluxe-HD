cmake_minimum_required(VERSION 3.15)
project(
    ZumaHD
    LANGUAGES C
    VERSION 0.1.0
)

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.c")

add_executable(
    ZumaHD
    ${SOURCES}
)


if(USE_VENDORED_LIBS)
  set(SDL2IMAGE_SAMPLES OFF)
  set(SDL2IMAGE_VENDORED ON)
  add_subdirectory(3rdparty/libexpat/expat)
  add_subdirectory(3rdparty/SDL)
  add_subdirectory(3rdparty/SDL_image)
else()
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(expat REQUIRED)
endif()

target_link_libraries(
    ZumaHD PRIVATE

    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image

    expat

    -lm
)

target_compile_options(
  ZumaHD PRIVATE -Wall -Wextra -Werror
)
