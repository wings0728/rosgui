#include "../../include/rosgui/qt/t3_face_decoder.hpp"

#include <QImage>
Decoder::Decoder()
{

}
Decoder::~Decoder()
{

}
Decoder* Decoder::getDecoder()
{
  static Decoder decoder;
  return &decoder;
}


int Decoder::initDecoder()
{
    avcodec_register_all();

        pCodec = avcodec_find_decoder(codec_id);

        pCodecCtx = avcodec_alloc_context3(pCodec);

        pCodecParserCtx=av_parser_init(codec_id);

        if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
            printf("Could not open codec\n");
            return -1;
        }

        //Output File
        fp_out = fopen("bigbuckbunny_480x272.yuv", "wb");
        if (!fp_out) {
            printf("Could not open output YUV file\n");
            return -1;
        }

        pFrame = av_frame_alloc();
        pFrameRGB = av_frame_alloc();
        av_init_packet(&packet);

        //yuyvToyuvInit

        src_bpp=av_get_bits_per_pixel(av_pix_fmt_desc_get(src_pixfmt));
        dst_bpp=av_get_bits_per_pixel(av_pix_fmt_desc_get(dst_pixfmt));
        temp_buffer=(uint8_t *)malloc(in_w*in_h*src_bpp/8);
        ret= av_image_alloc(src_data, src_linesize,in_w, in_h, src_pixfmt, 1);
            if (ret< 0) {
                printf( "Could not allocate source image\n");
                return -1;
            }
        ret = av_image_alloc(dst_data, dst_linesize,in_w, in_h, dst_pixfmt, 1);
            if (ret< 0) {
                printf( "Could not allocate destination image\n");
                return -1;
            }

            //-----------------------------
                //Init Method 1

                img_convert_ctx =sws_alloc_context();

                //Show AVOption
                //av_opt_show2(img_convert_ctx,stdout,AV_OPT_FLAG_VIDEO_PARAM,0);
                //Set Value


                av_opt_set_int(img_convert_ctx,"sws_flags",SWS_BICUBIC|SWS_PRINT_INFO,0);
                av_opt_set_int(img_convert_ctx,"srcw",in_w,0);
                av_opt_set_int(img_convert_ctx,"srch",in_h,0);
                av_opt_set_int(img_convert_ctx,"src_format",src_pixfmt,0);
                //'0' for MPEG (Y:0-235);'1' for JPEG (Y:0-255)
                av_opt_set_int(img_convert_ctx,"src_range",1,0);
                av_opt_set_int(img_convert_ctx,"dstw",in_w,0);
                av_opt_set_int(img_convert_ctx,"dsth",in_h,0);
                av_opt_set_int(img_convert_ctx,"dst_format",dst_pixfmt,0);
                av_opt_set_int(img_convert_ctx,"dst_range",1,0);
                sws_init_context(img_convert_ctx,NULL,NULL);

                //Init Method 2
                //img_convert_ctx = sws_getContext(in_w, in_h,src_pixfmt, in_w, in_h, dst_pixfmt,
                //    rescale_method, NULL, NULL, NULL);
                //-----------------------------
                int numBytes = avpicture_get_size(AV_PIX_FMT_RGB32,in_w,in_h);
                out_buffer = (uint8_t *)av_malloc(numBytes *sizeof(uint8_t));
                avpicture_fill((AVPicture *)pFrameRGB,out_buffer,AV_PIX_FMT_RGB32,in_w,in_h);


}


int Decoder::decoderFrame(char *data, int dataSize)
{

    cur_ptr = (uint8_t *)data;
    cur_size = dataSize;

    while (cur_size>0){

               int len = av_parser_parse2(
                   pCodecParserCtx, pCodecCtx,
                   &packet.data, &packet.size,
                   cur_ptr , cur_size ,
                   AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);

               cur_ptr += len;
               cur_size -= len;

               if(packet.size==0)
                   continue;

               //Some Info from AVCodecParserContext

               //switch(pCodecParserCtx->pict_type){
                   //case AV_PICTURE_TYPE_I: T3LOG <<"Type:I\t";break;
                   //case AV_PICTURE_TYPE_P: T3LOG <<"Type:P\t";break;
                   //case AV_PICTURE_TYPE_B: T3LOG <<"Type:B\t";break;
                   //default: printf("Type:Other\t");break;
               //}


               ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
               if (ret < 0) {
                   printf("Decode Error.\n");
                   return ret;
               }
               if (got_picture) {

                   //*dst_linesize = 640;

                   sws_scale(img_convert_ctx, (uint8_t const * const *) pFrame->data, pFrame->linesize, 0, in_h, pFrameRGB->data,pFrameRGB->linesize);
                   QImage image((unsigned char *)out_buffer,in_w,in_h,QImage::Format_RGB32);
                    //image.mirrored (true,false);
                   emit newFrame(image);







               }
           }




}

int Decoder::closeDecoder()
{

        packet.data = NULL;
        packet.size = 0;
        while(1){
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
            if (ret < 0) {
                printf("Decode Error.\n");
                return ret;
            }
            if (!got_picture)
                break;
            if (got_picture) {

    #if USE_SWSCALE
                sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
                    pFrameYUV->data, pFrameYUV->linesize);

                fwrite(pFrameYUV->data[0],1,y_size,fp_out);     //Y
                fwrite(pFrameYUV->data[1],1,y_size/4,fp_out);   //U
                fwrite(pFrameYUV->data[2],1,y_size/4,fp_out);   //V
    #else
                int i=0;
                unsigned char* tempptr=NULL;
                tempptr=pFrame->data[0];
                for(i=0;i<pFrame->height;i++){
                    fwrite(tempptr,1,pFrame->width,fp_out);     //Y
                    tempptr+=pFrame->linesize[0];
                }
                tempptr=pFrame->data[1];
                for(i=0;i<pFrame->height/2;i++){
                    fwrite(tempptr,1,pFrame->width/2,fp_out);   //U
                    tempptr+=pFrame->linesize[1];
                }
                tempptr=pFrame->data[2];
                for(i=0;i<pFrame->height/2;i++){
                    fwrite(tempptr,1,pFrame->width/2,fp_out);   //V
                    tempptr+=pFrame->linesize[2];
                }
    #endif
               T3LOG ("Flush Decoder: Succeed to decode 1 frame!");
            }
        }

        fclose(fp_in);
        fclose(fp_out);

    #if USE_SWSCALE
        sws_freeContext(img_convert_ctx);
        av_frame_free(&pFrameYUV);
    #endif

        av_parser_close(pCodecParserCtx);

        av_frame_free(&pFrame);
        avcodec_close(pCodecCtx);
        av_free(pCodecCtx);

        return 0;
}


int Decoder::yuv2rgb()
{
    memcpy(src_data[0],pFrame->data[0],in_w*in_h);                    //Y
    memcpy(src_data[1],pFrame->data[1],in_w*in_h/4);      //U
    memcpy(src_data[2],pFrame->data[2],in_w*in_h/4);  //V

    sws_scale(img_convert_ctx, src_data, src_linesize, 0, in_h, dst_data, dst_linesize);
    QImage image((unsigned char *)dst_data,in_w,in_h,QImage::Format_RGB32);
    emit newFrame(image);
    if(fl){
      fl = false;
      QImage image((unsigned char *)dst_data,in_w,in_h,QImage::Format_RGB32);
       image.save("dd.png");
      }

            frame_idx++;
}
