project(ffmpegdemo)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS -pthread)

set(FFMPEG_DIR /opt/ffmpeg)
set(FFMPEG_INCLUDE ${FFMPEG_DIR}/include)
set(FFMPEG_LIB ${FFMPEG_DIR}/lib)

find_library(AVCODEC_LIB avcodec PATHS ${FFMPEG_LIB})
find_library(AVDEVICE_LIB avdevice PATHS ${FFMPEG_LIB})
find_library(AVFILTER_LIB avfilter PATHS ${FFMPEG_LIB})
find_library(AVFORMAT_LIB avformat PATHS ${FFMPEG_LIB})
find_library(AVUTIL_LIB avutil PATHS ${FFMPEG_LIB})
find_library(AVPOSTPROC_LIB postproc PATHS ${FFMPEG_LIB})
find_library(SWRESAMPLE_LIB swresample PATHS ${FFMPEG_LIB})
find_library(SWSCALE_LIB swscale PATHS ${FFMPEG_LIB})

message("load: AVCODEC_LIB:${AVCODEC_LIB}")
message("load: AVDEVICE_LIB:${AVDEVICE_LIB}")
message("load: AVFILTER_LIB:${AVFILTER_LIB}")
message("load: AVFORMAT_LIB:${AVFORMAT_LIB}")
message("load: AVUTIL_LIB:${AVUTIL_LIB}")
message("load: AVPOSTPROC_LIB:${AVPOSTPROC_LIB}")
message("load: SWRESAMPLE_LIB:${SWRESAMPLE_LIB}")
message("load: SWSCALE_LIB:${SWSCALE_LIB}")

include_directories(${FFMPEG_INCLUDE} ${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)
message("SRCS: ${SRCS}")

add_executable(ffmpegdemo ${SRCS})

target_include_directories(
    ffmpegdemo PUBLIC
    ${FFMPEG_INCLUDE}
)

target_link_libraries(
    ffmpegdemo PUBLIC
    ${AVCODEC_LIB}
    ${AVDEVICE_LIB}
    ${AVFILTER_LIB}
    ${AVFORMAT_LIB}
    ${AVUTIL_LIB}
    ${AVPOSTPROC_LIB}
    ${SWRESAMPLE_LIB}
    ${SWSCALE_LIB}
)