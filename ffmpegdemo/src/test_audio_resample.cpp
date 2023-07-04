#include "main.h"

using namespace std;

void test_audio_resample()
{
    int ret = 0;
    string url = "/mnt/d/Resources/media/aac/Nightglow.aac";
    string pcmFile1Url = "/mnt/d/Resources/media/pcm/Nightglow.pcm";
    string pcmFile2Url = "/mnt/d/Resources/media/pcm/Nightglow2.pcm";
    string pcmFile3Url = "/mnt/d/Resources/media/pcm/Nightglow3.pcm";

    FILE *pcmFile1 = fopen(pcmFile1Url.c_str(), "wb");
    FILE *pcmFile2 = fopen(pcmFile2Url.c_str(), "wb");
    FILE *pcmFile3 = fopen(pcmFile3Url.c_str(), "wb");

    AVFormatContext *inFmtCtx = avformat_alloc_context();
    if (inFmtCtx == NULL)
    {
        std::cout << "avformat_alloc_context fail:" << ret << endl;
        return;
    }
    std::cout << "avformat_alloc_context ok" << endl;
    ret = avformat_open_input(&inFmtCtx, url.c_str(), NULL, NULL);
    if (ret != 0)
    {
        std::cout << "avformat_open_input fail:" << ret << endl;
        return;
    }
    std::cout << "avformat_open_input ok" << endl;
    avformat_find_stream_info(inFmtCtx, NULL);
    av_dump_format(inFmtCtx, 0, url.c_str(), 0);

    int audio_stream_index = -1;
    const AVCodec *audioCodec;
    audio_stream_index = av_find_best_stream(inFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, &audioCodec, 0);
    if (audio_stream_index < 0 || !audioCodec)
    {
        std::cout << "av_find_best_stream fail:" << audio_stream_index << endl;
        return;
    }
    std::cout << "find audio stream: " << audio_stream_index << ":" << avcodec_get_name(audioCodec->id) << endl;

    AVCodecParameters *inputCodecParam = inFmtCtx->streams[audio_stream_index]->codecpar;
    AVCodecContext *decodeCtx = avcodec_alloc_context3(audioCodec);
    avcodec_parameters_to_context(decodeCtx, inputCodecParam);
    decodeCtx->time_base.num = inFmtCtx->streams[audio_stream_index]->time_base.num;
    decodeCtx->time_base.den = inFmtCtx->streams[audio_stream_index]->time_base.den;
    ret = avcodec_open2(decodeCtx, audioCodec, NULL);
    if (ret < 0)
    {
        std::cout << "avcodec_open2 fail:" << ret << endl;
        return;
    }

    std::cout << "timebase:" << inFmtCtx->streams[audio_stream_index]->time_base.num << "/" << inFmtCtx->streams[audio_stream_index]->time_base.den << endl;

    int64_t dst_ch_layout = AV_CH_LAYOUT_STEREO, src_ch_layout = inputCodecParam->channel_layout;
    int src_rate = inputCodecParam->sample_rate, dst_rate = 48000;
    AVSampleFormat src_sample_fmt = (AVSampleFormat)inputCodecParam->format, dst_sample_fmt = (AVSampleFormat)inputCodecParam->format;
    int src_nb_samples = inputCodecParam->frame_size, dst_nb_samples, max_dst_nb_samples;
    int src_nb_channels = av_get_channel_layout_nb_channels(src_ch_layout), dst_nb_channels = 2;
    int src_linesize = 0, dst_linesize = 0;
    int dst_bufsize = 0;
    uint8_t **dst_data = NULL;

    SwrContext *swrCtx = swr_alloc();
    if (!swrCtx)
    {
        std::cout << "swr_alloc fail:" << ret << endl;
        return;
    }

    av_opt_set_int(swrCtx, "in_channel_layout", src_ch_layout, 0);
    av_opt_set_int(swrCtx, "in_sample_rate", inputCodecParam->sample_rate, 0);
    av_opt_set_sample_fmt(swrCtx, "in_sample_fmt", src_sample_fmt, 0);

    av_opt_set_int(swrCtx, "out_channel_layout", dst_ch_layout, 0);
    av_opt_set_int(swrCtx, "out_sample_rate", dst_rate, 0);
    av_opt_set_sample_fmt(swrCtx, "out_sample_fmt", dst_sample_fmt, 0);

    ret = swr_init(swrCtx);
    if (ret < 0)
    {
        std::cout << "swr_init fail:" << ret << endl;
        return;
    }

    max_dst_nb_samples = dst_nb_samples = av_rescale_rnd(src_nb_samples, dst_rate, src_rate, AV_ROUND_UP);
    max_dst_nb_samples = dst_nb_samples = 960;

    /* buffer is going to be directly written to a rawaudio file, no alignment */
    dst_nb_channels = av_get_channel_layout_nb_channels(dst_ch_layout);
    ret = av_samples_alloc_array_and_samples(&dst_data, &dst_linesize, dst_nb_channels, dst_nb_samples, dst_sample_fmt, 0);
    if (ret < 0)
    {
        std::cout << "av_samples_alloc_array_and_samples fail:" << ret << endl;
        return;
    }
    std::cout << "dst_nb_samples:" << dst_nb_samples << endl;
    std::cout << "dst_linesize:" << dst_linesize << endl;
    std::cout << "av_samples_alloc_array_and_samples:" << ret << endl;

    AVPacket *readPacket = av_packet_alloc();
    AVFrame *decodedFrame = av_frame_alloc();
    uint32_t pcmPlanarBuf[10000] = {0};
    uint32_t pcmPackedBuf[10000] = {0};
    uint32_t pcmConvertPlanarBuf[10000] = {0};
    uint32_t pcmConvertPackedBuf[10000] = {0};
    int readPktCnt = 0;
    int convertSize = 0;
    while (true)
    {
        ret = av_read_frame(inFmtCtx, readPacket);
        if (ret < 0)
        {
            std::cout << "av_read_frame fail:" << ret << endl;
            break;
        }

        ret = avcodec_send_packet(decodeCtx, readPacket);
        av_packet_unref(readPacket);
        if (ret == AVERROR(EAGAIN))
        {
            continue;
        }
        else if (ret < 0)
        {
            std::cout << "avcodec_send_packet fail:" << ret << endl;
            break;
        }

        while (ret == 0)
        {
            ret = avcodec_receive_frame(decodeCtx, decodedFrame);
            if (ret == AVERROR(EAGAIN))
            {
                break;
            }
            else if (ret < 0)
            {
                std::cout << "avcodec_receive_frame fail:" << ret << endl;
                break;
            }

            int pcmSize = decodedFrame->linesize[0];
            bzero(pcmPlanarBuf, 10000 * sizeof(uint32_t));
            bzero(pcmPackedBuf, 10000 * sizeof(uint32_t));
            memcpy(pcmPlanarBuf, decodedFrame->data[0], pcmSize / 2);
            memcpy(pcmPlanarBuf + pcmSize / 2 / sizeof(uint32_t), decodedFrame->data[1], pcmSize / 2);

            for (auto i = 0; i < pcmSize / 2 / sizeof(uint32_t); i++)
            {
                pcmPackedBuf[2 * i] = pcmPlanarBuf[i];
                pcmPackedBuf[2 * i + 1] = pcmPlanarBuf[pcmSize / 2 / sizeof(uint32_t) + i];
            }
            fwrite(pcmPackedBuf, 1, pcmSize, pcmFile1);

            // 重采样
            // int delayUints = swr_get_delay(swrCtx, src_rate);
            // dst_nb_samples = av_rescale_rnd(delayUints + src_nb_samples, dst_rate, src_rate, AV_ROUND_DOWN);
            // if (dst_nb_samples > max_dst_nb_samples)
            // {
            //     av_freep(&dst_data[0]);
            //     ret = av_samples_alloc(dst_data, &dst_linesize, dst_nb_channels, dst_nb_samples, dst_sample_fmt, 1);
            //     if (ret < 0)
            //     {
            //         std::cout << "av_samples_alloc fail:" << ret << endl;
            //         break;
            //     }
            //     std::cout << "max_dst_nb_samples:" << max_dst_nb_samples << "=>" << dst_nb_samples << endl;
            //     max_dst_nb_samples = dst_nb_samples;
            // }

            convertSize = swr_convert(swrCtx, dst_data, dst_nb_samples, (const uint8_t **)decodedFrame->data, src_nb_samples);
            if (ret < 0)
            {
                std::cout << "swr_convert fail:" << ret << endl;
                break;
            }

            bzero(pcmConvertPlanarBuf, 10000 * sizeof(uint32_t));
            bzero(pcmConvertPackedBuf, 10000 * sizeof(uint32_t));
            memcpy(pcmConvertPlanarBuf, dst_data[0], convertSize * 4);

            fwrite(dst_data[0] + (convertSize * 4), 1, convertSize * 4, pcmFile3);
            std::cout << "1.convertSize:" << convertSize << endl;

            while ((convertSize = swr_convert(swrCtx, dst_data, dst_nb_samples, NULL, 0)) > 0)
            {
                bzero(pcmConvertPlanarBuf, 10000 * sizeof(uint32_t));
                bzero(pcmConvertPackedBuf, 10000 * sizeof(uint32_t));
                memcpy(pcmConvertPlanarBuf, dst_data[0], convertSize * 4);

                fwrite(dst_data[0] + (convertSize * 4), 1, convertSize * 4, pcmFile3);
                std::cout << "2.convertSize:" << convertSize << endl;
            }

            continue;

            dst_bufsize = av_samples_get_buffer_size(&dst_linesize, dst_nb_channels, ret, dst_sample_fmt, 1);
            if (dst_bufsize < 0)
            {
                std::cout << "av_samples_get_buffer_size fail:" << ret << endl;
                break;
            }
            if (dst_bufsize != convertSize * 8)
            {
                std::cout << "convertSize:" << convertSize * 8 << " dst_bufsize:" << dst_bufsize << endl;
            }

            int pcmSize2 = dst_bufsize;

            memcpy(pcmConvertPlanarBuf, dst_data[0], pcmSize2);

            int mid = pcmSize2 / sizeof(uint32_t) / 2;

            fwrite(dst_data[0] + (pcmSize2 / 2), 1, pcmSize2 / 2, pcmFile3);

            for (auto i = 0; i < mid; i++)
            {
                pcmConvertPackedBuf[2 * i] = pcmConvertPlanarBuf[i];
                pcmConvertPackedBuf[2 * i + 1] = pcmConvertPlanarBuf[mid + i];
            }
            fwrite(pcmConvertPackedBuf, 1, pcmSize2, pcmFile2);

            // fwrite(dst_data[0], 1, dst_bufsize, pcmFile2);
            av_frame_unref(decodedFrame);
        }

        readPktCnt++;
    }
    fclose(pcmFile1);
    fclose(pcmFile2);
    fclose(pcmFile3);
    avio_close(inFmtCtx->pb);
    // avformat_close_input(&inFmtCtx);
    // avformat_free_context(inFmtCtx);
}