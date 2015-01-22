//HPAVIOC.h
#ifndef __HPAVIOC_H__
#define __HPAVIOC_H__

typedef enum {
	HP_VIDEO_CODEC_H263P=0,
	HP_VIDEO_CODEC_H264_VBR_SOFTWARE,
	HP_VIDEO_CODEC_H264_CBR_SOFTWARE,
	HP_VIDEO_CODEC_H264_VBR_HARDWARE,
	HP_VIDEO_CODEC_H264_CBR_HARDWARE,
	HP_VIDEO_CODEC_X264_VBR,
	HP_VIDEO_CODEC_X264_CBR,
	HP_VIDEO_CODEC_H263P_CBR,
	HP_VIDEO_CODEC_AVC10_VBR,
	HP_VIDEO_CODEC_AVC10_CBR,
	HP_VIDEO_CODEC_COUNT
}HP_VIDEO_CODEC_TYPE;
#define HP_VIDEO_CODEC_H263P_VBR	HP_VIDEO_CODEC_H263P


typedef enum{
	HP_VIDEO_QUALITY_WORST=0,	//64
	HP_VIDEO_QUALITY_WORSE,		//128
	HP_VIDEO_QUALITY_BAD,		//384
	HP_VIDEO_QUALITY_GOOD,		//768
	HP_VIDEO_QUALITY_BETTER,	//2048
	HP_VIDEO_QUALITY_BEST,		//8192
	HP_VIDEO_QUALITY_COUNT
}HP_VIDEO_QUALITY_TYPE;

typedef enum {
	HP_VIDEO_SIZE_176X144=0,
	HP_VIDEO_SIZE_240X176,
	HP_VIDEO_SIZE_320X240,
	HP_VIDEO_SIZE_352X288,
	HP_VIDEO_SIZE_640X480,
	HP_VIDEO_SIZE_704X576,
	HP_VIDEO_SIZE_COUNT
}HP_VIDEO_SIZE_TYPE;

#define HP_VIDEO_SIZE_QCIF	HP_VIDEO_SIZE_176X144
#define HP_VIDEO_SIZE_CIF	HP_VIDEO_SIZE_352X288
#define HP_VIDEO_SIZE_DCIF	HP_VIDEO_SIZE_640X480
#define HP_VIDEO_SIZE_4CIF	HP_VIDEO_SIZE_704X576


typedef enum {
	HP_MAX_BITRATE_UNLIMITED=0,
	HP_MAX_BITRATE_64,
	HP_MAX_BITRATE_128,
	HP_MAX_BITRATE_256,
	HP_MAX_BITRATE_384,
	HP_MAX_BITRATE_512,
	HP_MAX_BITRATE_768,
	HP_MAX_BITRATE_1024,
	HP_MAX_BITRATE_2048,
	HP_MAX_BITRATE_COUNT
}HP_MAX_BITRATE_TYPE;

typedef enum {
	HP_FRAME_RATE_5=0,
	HP_FRAME_RATE_10,
	HP_FRAME_RATE_15,
	HP_FRAME_RATE_20,
	HP_FRAME_RATE_25,
	HP_FRAME_RATE_30,
	HP_FRAME_RATE_COUNT
}HP_FRAME_RATE_TYPE;

typedef enum {
	HP_AUDIO_CODEC_G7231=0,		//8000hz	6.3kbps
	HP_AUDIO_CODEC_G711ULAW,	//8000hz	64kbps
	HP_AUDIO_CODEC_WB,			//16000hz	32kbps
	HP_AUDIO_CODEC_G729,		//8000hz	8kbps
	HP_AUDIO_CODEC_AMR,			//16000hz	8-24kbps
	HP_AUDIO_CODEC_COUNT
}HP_AUDIO_CODEC_TYPE;


#define HPAV_PACKET_AV				0x01
#define HPAV_PACKET_SUB				0x02
#define HPAV_PACKET_KEY				0x04
#define HPAV_PACKET_MASK			~(0x07)

#define IS_VALID_PACKET(p)			(HPAV_PACKET_MASK==(HPAV_PACKET_MASK&~(*(unsigned char*)p)))
#define IS_AUDIO_PACKET(p)			(HPAV_PACKET_AV!=(HPAV_PACKET_AV&(*(unsigned char*)p)))
#define IS_VIDEO_PACKET(p)			(HPAV_PACKET_AV==(HPAV_PACKET_AV&(*(unsigned char*)p)))
#define IS_SUB_PACKET(p)			(HPAV_PACKET_SUB==(HPAV_PACKET_SUB&(*(unsigned char*)p)))
#define VIDEC_HEADER_EXT_GET_KEYFRAME(p)			(HPAV_PACKET_KEY==(HPAV_PACKET_KEY&(*(unsigned char*)p)))

#define HPIO_PACKET_HEADER_SIZE		8

enum {
	HPAV_ONAC_DECREASE_QUALITY=0,
	HPAV_ONAC_KEEP_QUALITY,
	HPAV_ONAC_INCREASE_QUALITY
};

AFX_EXT_CLASS bool HPVideoSizeConvert(HP_VIDEO_SIZE_TYPE HPVideoSize,unsigned short&nWidth,unsigned short&nHeight);
AFX_EXT_CLASS bool HPVideoFrameRateConvert(HP_FRAME_RATE_TYPE HPFrameRate,unsigned char&ucFrameRate);
AFX_EXT_CLASS bool HPMaxBitrateConvert(HP_MAX_BITRATE_TYPE HPMaxBitrate,int&nMaxBitrate);



#endif