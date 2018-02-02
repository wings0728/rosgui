#ifndef DECODER_H
#define DECODER_H
#include <stdio.h>
#include <QString>
#include <QImage>
#include <QObject>
#include "t3_af_config.hpp"
#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include "libavutil/opt.h"
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
#include <libswscale/swscale.h>


#ifdef __cplusplus
}
#endif
#endif

#define USE_SWSCALE 0

//test different codec
#define TEST_H264  1
#define TEST_HEVC  0


class Decoder : public QObject
{
    Q_OBJECT
public:
    static Decoder* getDecoder();
    int initDecoder();
    int decoderFrame(char * data,int dataSize);
    int closeDecoder();
     ~Decoder();

signals:
     void newFrame(QImage image);
private:
    Decoder();

    int yuv2rgb();
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx= NULL;
    AVCodecParserContext *pCodecParserCtx=NULL;

    FILE *fp_in;
    FILE *fp_out;
    FILE *_outFile;
    AVFrame	*pFrame;
    AVFrame *pFrameRGB;
    uint8_t * out_buffer;

    const int in_buffer_size=4096;
    //uint8_t in_buffer[in_buffer_size + AV_INPUT_BUFFER_PADDING_SIZE]={0};
    uint8_t *cur_ptr;
    int cur_size;
    AVPacket packet;
    int ret, got_picture;
    int y_size;


#if TEST_HEVC
    enum AVCodecID codec_id=AV_CODEC_ID_HEVC;
    char filepath_in[]="bigbuckbunny_480x272.hevc";
#elif TEST_H264
    AVCodecID codec_id=AV_CODEC_ID_H264;
   // char filepath_in[]="bigbuckbunny_480x272.h264";
#else
    AVCodecID codec_id=AV_CODEC_ID_MPEG2VIDEO;
    char filepath_in[]="bigbuckbunny_480x272.m2v";
#endif

    //QString filepath_out="bigbuckbunny_480x272.yuv";
    int first_time=1;

#if USE_SWSCALE
    struct SwsContext *img_convert_ctx;
    AVFrame	*pFrameYUV;
    uint8_t *out_buffer;

#endif
    bool fl = true;
    int in_w=640,in_h=480;
    AVPixelFormat src_pixfmt=AV_PIX_FMT_YUV420P;
    int src_bpp;
    AVPixelFormat dst_pixfmt=AV_PIX_FMT_RGB32;

    int dst_bpp;
    uint8_t *src_data[4];
    int src_linesize[4];

    uint8_t *dst_data[4];
    int dst_linesize[4];

    int rescale_method=SWS_BICUBIC;
    struct SwsContext *img_convert_ctx;
    uint8_t *temp_buffer;
    int frame_idx=0;


};

#endif // DECODER_H
