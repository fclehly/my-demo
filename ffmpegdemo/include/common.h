#ifndef COMMON_H
#define COMMON_H

#include<iostream>
#include<string>
#include<cstring>
#include<cstdint>
#include<thread>
#include<vector>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavfilter/avfilter.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavutil/avstring.h"
#include "libavutil/channel_layout.h"
#include "libavutil/error.h"
#include "libavutil/fifo.h"
#include "libavutil/buffer.h"
#include "libpostproc/postprocess.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
}

#endif