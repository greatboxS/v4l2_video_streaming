#include "v4l2debug.h"
#include "linux/videodev2.h"
#include <stdio.h>
#include <string.h>

const char *v4l2debug_control_id(unsigned int control_id)
{
    static char control_id_str[DEBUG_BUFF_MAX_SIZE] = {0};
    switch (control_id)
    {
    case V4L2_CID_BRIGHTNESS:
        sprintf(control_id_str, "V4L2_CID_BRIGHTNESS");
        break;
    case V4L2_CID_USER_CLASS:
        sprintf(control_id_str, "V4L2_CID_USER_CLASS");
        break;
    case V4L2_CID_CONTRAST:
        sprintf(control_id_str, "V4L2_CID_CONTRAST");
        break;
    case V4L2_CID_SATURATION:
        sprintf(control_id_str, "V4L2_CID_SATURATION");
        break;
    case V4L2_CID_HUE:
        sprintf(control_id_str, "V4L2_CID_HUE");
        break;
    case V4L2_CID_AUDIO_VOLUME:
        sprintf(control_id_str, "V4L2_CID_AUDIO_VOLUME");
        break;
    case V4L2_CID_AUDIO_BALANCE:
        sprintf(control_id_str, "V4L2_CID_AUDIO_BALANCE");
        break;
    case V4L2_CID_AUDIO_BASS:
        sprintf(control_id_str, "V4L2_CID_AUDIO_BASS");
        break;
    case V4L2_CID_AUDIO_TREBLE:
        sprintf(control_id_str, "V4L2_CID_AUDIO_TREBLE");
        break;
    case V4L2_CID_AUDIO_MUTE:
        sprintf(control_id_str, "V4L2_CID_AUDIO_MUTE");
        break;
    case V4L2_CID_AUDIO_LOUDNESS:
        sprintf(control_id_str, "V4L2_CID_AUDIO_LOUDNESS");
        break;
    case V4L2_CID_BLACK_LEVEL:
        sprintf(control_id_str, "V4L2_CID_BLACK_LEVEL");
        break;
    case V4L2_CID_AUTO_WHITE_BALANCE:
        sprintf(control_id_str, "V4L2_CID_AUTO_WHITE_BALANCE");
        break;
    case V4L2_CID_DO_WHITE_BALANCE:
        sprintf(control_id_str, "V4L2_CID_DO_WHITE_BALANCE");
        break;
    case V4L2_CID_RED_BALANCE:
        sprintf(control_id_str, "V4L2_CID_RED_BALANCE");
        break;
    case V4L2_CID_BLUE_BALANCE:
        sprintf(control_id_str, "V4L2_CID_BLUE_BALANCE");
        break;
    case V4L2_CID_GAMMA:
        sprintf(control_id_str, "V4L2_CID_GAMMA || V4L2_CID_WHITENESS");
        break;
    case V4L2_CID_EXPOSURE:
        sprintf(control_id_str, "V4L2_CID_EXPOSURE");
        break;
    case V4L2_CID_AUTOGAIN:
        sprintf(control_id_str, "V4L2_CID_AUTOGAIN");
        break;
    case V4L2_CID_GAIN:
        sprintf(control_id_str, "V4L2_CID_GAIN");
        break;
    case V4L2_CID_HFLIP:
        sprintf(control_id_str, "V4L2_CID_HFLIP");
        break;
    case V4L2_CID_VFLIP:
        sprintf(control_id_str, "V4L2_CID_VFLIP");
        break;
    case V4L2_CID_POWER_LINE_FREQUENCY:
        sprintf(control_id_str, "V4L2_CID_POWER_LINE_FREQUENCY");
        break;
    case V4L2_CID_HUE_AUTO:
        sprintf(control_id_str, "V4L2_CID_HUE_AUTO");
        break;
    case V4L2_CID_WHITE_BALANCE_TEMPERATURE:
        sprintf(control_id_str, "V4L2_CID_WHITE_BALANCE_TEMPERATURE");
        break;
    case V4L2_CID_SHARPNESS:
        sprintf(control_id_str, "V4L2_CID_SHARPNESS");
        break;
    case V4L2_CID_BACKLIGHT_COMPENSATION:
        sprintf(control_id_str, "V4L2_CID_BACKLIGHT_COMPENSATION");
        break;
    case V4L2_CID_CHROMA_AGC:
        sprintf(control_id_str, "V4L2_CID_CHROMA_AGC");
        break;
    case V4L2_CID_COLOR_KILLER:
        sprintf(control_id_str, "V4L2_CID_COLOR_KILLER");
        break;
    case V4L2_CID_COLORFX:
        sprintf(control_id_str, "V4L2_CID_COLORFX");
        break;
    case V4L2_CID_AUTOBRIGHTNESS:
        sprintf(control_id_str, "V4L2_CID_AUTOBRIGHTNESS");
        break;
    case V4L2_CID_BAND_STOP_FILTER:
        sprintf(control_id_str, "V4L2_CID_BAND_STOP_FILTER");
        break;
    case V4L2_CID_ROTATE:
        sprintf(control_id_str, "V4L2_CID_ROTATE");
        break;
    case V4L2_CID_BG_COLOR:
        sprintf(control_id_str, "V4L2_CID_BG_COLOR");
        break;
    case V4L2_CID_CHROMA_GAIN:
        sprintf(control_id_str, "V4L2_CID_CHROMA_GAIN");
        break;
    case V4L2_CID_ILLUMINATORS_1:
        sprintf(control_id_str, "V4L2_CID_ILLUMINATORS_1");
        break;
    case V4L2_CID_ILLUMINATORS_2:
        sprintf(control_id_str, "V4L2_CID_ILLUMINATORS_2");
        break;
    case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
        sprintf(control_id_str, "V4L2_CID_MIN_BUFFERS_FOR_CAPTURE");
        break;
    case V4L2_CID_MIN_BUFFERS_FOR_OUTPUT:
        sprintf(control_id_str, "V4L2_CID_MIN_BUFFERS_FOR_OUTPUT");
        break;
    case V4L2_CID_ALPHA_COMPONENT:
        sprintf(control_id_str, "V4L2_CID_ALPHA_COMPONENT");
        break;
    case V4L2_CID_COLORFX_CBCR:
        sprintf(control_id_str, "V4L2_CID_COLORFX_CBCR");
        break;
    case V4L2_CID_LASTP1:
        sprintf(control_id_str, "V4L2_CID_LASTP1");
        break;
    case V4L2_CID_USER_MEYE_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_MEYE_BASE");
        break;
    case V4L2_CID_USER_S2255_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_S2255_BASE");
        break;
    case V4L2_CID_USER_SI476X_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_SI476X_BASE");
        break;
    case V4L2_CID_USER_TI_VPE_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_TI_VPE_BASE");
        break;
    case V4L2_CID_USER_SAA7134_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_SAA7134_BASE");
        break;
    case V4L2_CID_USER_ADV7180_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_ADV7180_BASE");
        break;
    case V4L2_CID_USER_TC358743_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_TC358743_BASE");
        break;
    case V4L2_CID_USER_MAX217X_BASE:
        sprintf(control_id_str, "V4L2_CID_USER_MAX217X_BASE");
        break;
    case V4L2_CID_MPEG_CLASS:
        sprintf(control_id_str, "V4L2_CID_MPEG_CLASS");
        break;
    case V4L2_CID_MPEG_STREAM_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_TYPE");
        break;
    case V4L2_CID_MPEG_STREAM_PID_PMT:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PID_PMT");
        break;
    case V4L2_CID_MPEG_STREAM_PID_AUDIO:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PID_AUDIO");
        break;
    case V4L2_CID_MPEG_STREAM_PID_VIDEO:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PID_VIDEO");
        break;
    case V4L2_CID_MPEG_STREAM_PID_PCR:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PID_PCR");
        break;
    case V4L2_CID_MPEG_STREAM_PES_ID_AUDIO:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PES_ID_AUDIO");
        break;
    case V4L2_CID_MPEG_STREAM_PES_ID_VIDEO:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_PES_ID_VIDEO");
        break;
    case V4L2_CID_MPEG_STREAM_VBI_FMT:
        sprintf(control_id_str, "V4L2_CID_MPEG_STREAM_VBI_FMT");
        break;
    case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ");
        break;
    case V4L2_CID_MPEG_AUDIO_ENCODING:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_ENCODING");
        break;
    case V4L2_CID_MPEG_AUDIO_L1_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_L1_BITRATE");
        break;
    case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_L2_BITRATE");
        break;
    case V4L2_CID_MPEG_AUDIO_L3_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_L3_BITRATE");
        break;
    case V4L2_CID_MPEG_AUDIO_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_MODE");
        break;
    case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_MODE_EXTENSION");
        break;
    case V4L2_CID_MPEG_AUDIO_EMPHASIS:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_EMPHASIS");
        break;
    case V4L2_CID_MPEG_AUDIO_CRC:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_CRC");
        break;
    case V4L2_CID_MPEG_AUDIO_MUTE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_MUTE");
        break;
    case V4L2_CID_MPEG_AUDIO_AAC_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_AAC_BITRATE");
        break;
    case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_AC3_BITRATE");
        break;
    case V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK");
        break;
    case V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK:
        sprintf(control_id_str, "V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK");
        break;
    case V4L2_CID_MPEG_VIDEO_ENCODING:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_ENCODING");
        break;
    case V4L2_CID_MPEG_VIDEO_ASPECT:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_ASPECT");
        break;
    case V4L2_CID_MPEG_VIDEO_B_FRAMES:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_B_FRAMES");
        break;
    case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_GOP_SIZE");
        break;
    case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_GOP_CLOSURE");
        break;
    case V4L2_CID_MPEG_VIDEO_PULLDOWN:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_PULLDOWN");
        break;
    case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_BITRATE_MODE");
        break;
    case V4L2_CID_MPEG_VIDEO_BITRATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_BITRATE");
        break;
    case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_BITRATE_PEAK");
        break;
    case V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION");
        break;
    case V4L2_CID_MPEG_VIDEO_MUTE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MUTE");
        break;
    case V4L2_CID_MPEG_VIDEO_MUTE_YUV:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MUTE_YUV");
        break;
    case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE");
        break;
    case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER");
        break;
    case V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB");
        break;
    case V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE");
        break;
    case V4L2_CID_MPEG_VIDEO_HEADER_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_HEADER_MODE");
        break;
    case V4L2_CID_MPEG_VIDEO_MAX_REF_PIC:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MAX_REF_PIC");
        break;
    case V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE");
        break;
    case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES");
        break;
    case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB");
        break;
    case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE");
        break;
    case V4L2_CID_MPEG_VIDEO_VBV_SIZE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VBV_SIZE");
        break;
    case V4L2_CID_MPEG_VIDEO_DEC_PTS:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_DEC_PTS");
        break;
    case V4L2_CID_MPEG_VIDEO_DEC_FRAME:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_DEC_FRAME");
        break;
    case V4L2_CID_MPEG_VIDEO_VBV_DELAY:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VBV_DELAY");
        break;
    case V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_REPEAT_SEQ_HEADER");
        break;
    case V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE");
        break;
    case V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE");
        break;
    case V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME");
        break;
    case V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H263_MIN_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H263_MIN_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H263_MAX_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H263_MAX_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_MIN_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_MAX_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_I_PERIOD");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_LEVEL");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_PROFILE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_SEI_FP_CURRENT_FRAME_0:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_SEI_FP_CURRENT_FRAME_0");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO_SLICE_GROUP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO_SLICE_GROUP");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_DIRECTION:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_DIRECTION");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_RATE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO_CHANGE_RATE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_FMO_RUN_LENGTH:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_FMO_RUN_LENGTH");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_ASO:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_ASO");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_ASO_SLICE_ORDER:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_ASO_SLICE_ORDER");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_TYPE");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER");
        break;
    case V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_H264_HIERARCHICAL_CODING_LAYER_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE");
        break;
    case V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_MPEG4_QPEL");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_MIN_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_MAX_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP");
        break;
    case V4L2_CID_MPEG_VIDEO_VPX_PROFILE:
        sprintf(control_id_str, "V4L2_CID_MPEG_VIDEO_VPX_PROFILE");
        break;
    case V4L2_CID_MPEG_CX2341X_BASE:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_BASE");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM");
        break;
    case V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP");
        break;
    case V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS:
        sprintf(control_id_str, "V4L2_CID_MPEG_CX2341X_STREAM_INSERT_NAV_PACKETS");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_PADDING:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_PADDING");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC");
        break;
    case V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P:
        sprintf(control_id_str, "V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P");
        break;
    case V4L2_CID_CAMERA_CLASS_BASE:
        sprintf(control_id_str, "V4L2_CID_CAMERA_CLASS_BASE");
        break;
    case V4L2_CID_CAMERA_CLASS:
        sprintf(control_id_str, "V4L2_CID_CAMERA_CLASS");
        break;
    case V4L2_CID_EXPOSURE_AUTO:
        sprintf(control_id_str, "V4L2_CID_EXPOSURE_AUTO");
        break;
    case V4L2_CID_EXPOSURE_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_EXPOSURE_ABSOLUTE");
        break;
    case V4L2_CID_EXPOSURE_AUTO_PRIORITY:
        sprintf(control_id_str, "V4L2_CID_EXPOSURE_AUTO_PRIORITY");
        break;
    case V4L2_CID_PAN_RELATIVE:
        sprintf(control_id_str, "V4L2_CID_PAN_RELATIVE");
        break;
    case V4L2_CID_TILT_RELATIVE:
        sprintf(control_id_str, "V4L2_CID_TILT_RELATIVE");
        break;
    case V4L2_CID_PAN_RESET:
        sprintf(control_id_str, "V4L2_CID_PAN_RESET");
        break;
    case V4L2_CID_TILT_RESET:
        sprintf(control_id_str, "V4L2_CID_TILT_RESET");
        break;
    case V4L2_CID_PAN_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_PAN_ABSOLUTE");
        break;
    case V4L2_CID_TILT_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_TILT_ABSOLUTE");
        break;
    case V4L2_CID_FOCUS_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_FOCUS_ABSOLUTE");
        break;
    case V4L2_CID_FOCUS_RELATIVE:
        sprintf(control_id_str, "V4L2_CID_FOCUS_RELATIVE");
        break;
    case V4L2_CID_FOCUS_AUTO:
        sprintf(control_id_str, "V4L2_CID_FOCUS_AUTO");
        break;
    case V4L2_CID_ZOOM_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_ZOOM_ABSOLUTE");
        break;
    case V4L2_CID_ZOOM_RELATIVE:
        sprintf(control_id_str, "V4L2_CID_ZOOM_RELATIVE");
        break;
    case V4L2_CID_ZOOM_CONTINUOUS:
        sprintf(control_id_str, "V4L2_CID_ZOOM_CONTINUOUS");
        break;
    case V4L2_CID_PRIVACY:
        sprintf(control_id_str, "V4L2_CID_PRIVACY");
        break;
    case V4L2_CID_IRIS_ABSOLUTE:
        sprintf(control_id_str, "V4L2_CID_IRIS_ABSOLUTE");
        break;
    case V4L2_CID_IRIS_RELATIVE:
        sprintf(control_id_str, "V4L2_CID_IRIS_RELATIVE");
        break;
    case V4L2_CID_AUTO_EXPOSURE_BIAS:
        sprintf(control_id_str, "V4L2_CID_AUTO_EXPOSURE_BIAS");
        break;
    case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
        sprintf(control_id_str, "V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE");
        break;
    case V4L2_CID_ISO_SENSITIVITY:
        sprintf(control_id_str, "V4L2_CID_ISO_SENSITIVITY");
        break;
    case V4L2_CID_SCENE_MODE:
        sprintf(control_id_str, "V4L2_CID_SCENE_MODE");
        break;
    case V4L2_CID_EXPOSURE_METERING:
        sprintf(control_id_str, "V4L2_CID_EXPOSURE_METERING");
        break;
    case V4L2_CID_3A_LOCK:
        sprintf(control_id_str, "V4L2_CID_3A_LOCK");
        break;
    case V4L2_LOCK_EXPOSURE:
        sprintf(control_id_str, "V4L2_LOCK_EXPOSURE");
        break;
    case V4L2_LOCK_WHITE_BALANCE:
        sprintf(control_id_str, "V4L2_LOCK_WHITE_BALANCE");
        break;
    case V4L2_LOCK_FOCUS:
        sprintf(control_id_str, "V4L2_LOCK_FOCUS");
        break;
    case V4L2_CID_AUTO_FOCUS_START:
        sprintf(control_id_str, "V4L2_CID_AUTO_FOCUS_START");
        break;
    case V4L2_CID_AUTO_FOCUS_STOP:
        sprintf(control_id_str, "V4L2_CID_AUTO_FOCUS_STOP");
        break;
    case V4L2_CID_AUTO_FOCUS_STATUS:
        sprintf(control_id_str, "V4L2_CID_AUTO_FOCUS_STATUS");
        break;
    case V4L2_AUTO_FOCUS_STATUS_IDLE:
        sprintf(control_id_str, "V4L2_AUTO_FOCUS_STATUS_IDLE");
        break;
    case V4L2_CID_PAN_SPEED:
        sprintf(control_id_str, "V4L2_CID_PAN_SPEED");
        break;
    case V4L2_CID_TILT_SPEED:
        sprintf(control_id_str, "V4L2_CID_TILT_SPEED");
        break;
    case V4L2_CID_FM_TX_CLASS_BASE:
        sprintf(control_id_str, "V4L2_CID_FM_TX_CLASS_BASE");
        break;
    case V4L2_CID_FM_TX_CLASS:
        sprintf(control_id_str, "V4L2_CID_FM_TX_CLASS");
        break;
    case V4L2_CID_RDS_TX_DEVIATION:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_DEVIATION");
        break;
    case V4L2_CID_RDS_TX_PI:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_PI");
        break;
    case V4L2_CID_RDS_TX_PTY:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_PTY");
        break;
    case V4L2_CID_RDS_TX_PS_NAME:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_PS_NAME");
        break;
    case V4L2_CID_RDS_TX_RADIO_TEXT:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_RADIO_TEXT");
        break;
    case V4L2_CID_RDS_TX_MONO_STEREO:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_MONO_STEREO");
        break;
    case V4L2_CID_RDS_TX_ARTIFICIAL_HEAD:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_ARTIFICIAL_HEAD");
        break;
    case V4L2_CID_RDS_TX_COMPRESSED:
        sprintf(control_id_str, "V4L2_CID_RDS_TX_COMPRESSED");
        break;
    default:
        sprintf(control_id_str, "UNKNOWN_CONTROL_ID");
        break;
    }
    return control_id_str;
}

const char *v4l2debug_ioctl_cmd(unsigned int cmd)
{
    static char cmd_str[DEBUG_BUFF_MAX_SIZE] = {0};
    switch (cmd)
    {
    case VIDIOC_QUERYCAP:
        sprintf(cmd_str, "VIDIOC_QUERYCAP");
        break;
    case VIDIOC_RESERVED:
        sprintf(cmd_str, "VIDIOC_RESERVED");
        break;
    case VIDIOC_ENUM_FMT:
        sprintf(cmd_str, "VIDIOC_ENUM_FMT");
        break;
    case VIDIOC_G_FMT:
        sprintf(cmd_str, "VIDIOC_G_FMT");
        break;
    case VIDIOC_S_FMT:
        sprintf(cmd_str, "VIDIOC_S_FMT");
        break;
    case VIDIOC_REQBUFS:
        sprintf(cmd_str, "VIDIOC_REQBUFS");
        break;
    case VIDIOC_QUERYBUF:
        sprintf(cmd_str, "VIDIOC_QUERYBUF");
        break;
    case VIDIOC_G_FBUF:
        sprintf(cmd_str, "VIDIOC_G_FBUF");
        break;
    case VIDIOC_S_FBUF:
        sprintf(cmd_str, "VIDIOC_S_FBUF");
        break;
    case VIDIOC_OVERLAY:
        sprintf(cmd_str, "VIDIOC_OVERLAY");
        break;
    case VIDIOC_QBUF:
        sprintf(cmd_str, "VIDIOC_QBUF");
        break;
    case VIDIOC_EXPBUF:
        sprintf(cmd_str, "VIDIOC_EXPBUF");
        break;
    case VIDIOC_DQBUF:
        sprintf(cmd_str, "VIDIOC_DQBUF");
        break;
    case VIDIOC_STREAMON:
        sprintf(cmd_str, "VIDIOC_STREAMON");
        break;
    case VIDIOC_STREAMOFF:
        sprintf(cmd_str, "VIDIOC_STREAMOFF");
        break;
    case VIDIOC_G_PARM:
        sprintf(cmd_str, "VIDIOC_G_PARM");
        break;
    case VIDIOC_S_PARM:
        sprintf(cmd_str, "VIDIOC_S_PARM");
        break;
    case VIDIOC_G_STD:
        sprintf(cmd_str, "VIDIOC_G_STD");
        break;
    case VIDIOC_S_STD:
        sprintf(cmd_str, "VIDIOC_S_STD");
        break;
    case VIDIOC_ENUMSTD:
        sprintf(cmd_str, "VIDIOC_ENUMSTD");
        break;
    case VIDIOC_ENUMINPUT:
        sprintf(cmd_str, "VIDIOC_ENUMINPUT");
        break;
    case VIDIOC_G_CTRL:
        sprintf(cmd_str, "VIDIOC_G_CTRL");
        break;
    case VIDIOC_S_CTRL:
        sprintf(cmd_str, "VIDIOC_S_CTRL");
        break;
    case VIDIOC_G_TUNER:
        sprintf(cmd_str, "VIDIOC_G_TUNER");
        break;
    case VIDIOC_S_TUNER:
        sprintf(cmd_str, "VIDIOC_S_TUNER");
        break;
    case VIDIOC_G_AUDIO:
        sprintf(cmd_str, "VIDIOC_G_AUDIO");
        break;
    case VIDIOC_S_AUDIO:
        sprintf(cmd_str, "VIDIOC_S_AUDIO");
        break;
    case VIDIOC_QUERYCTRL:
        sprintf(cmd_str, "VIDIOC_QUERYCTRL");
        break;
    case VIDIOC_QUERYMENU:
        sprintf(cmd_str, "VIDIOC_QUERYMENU");
        break;
    case VIDIOC_G_INPUT:
        sprintf(cmd_str, "VIDIOC_G_INPUT");
        break;
    case VIDIOC_S_INPUT:
        sprintf(cmd_str, "VIDIOC_S_INPUT");
        break;
    case VIDIOC_G_EDID:
        sprintf(cmd_str, "VIDIOC_G_EDID");
        break;
    case VIDIOC_S_EDID:
        sprintf(cmd_str, "VIDIOC_S_EDID");
        break;
    case VIDIOC_G_OUTPUT:
        sprintf(cmd_str, "VIDIOC_G_OUTPUT");
        break;
    case VIDIOC_S_OUTPUT:
        sprintf(cmd_str, "VIDIOC_S_OUTPUT");
        break;
    case VIDIOC_ENUMOUTPUT:
        sprintf(cmd_str, "VIDIOC_ENUMOUTPUT");
        break;
    case VIDIOC_G_AUDOUT:
        sprintf(cmd_str, "VIDIOC_G_AUDOUT");
        break;
    case VIDIOC_S_AUDOUT:
        sprintf(cmd_str, "VIDIOC_S_AUDOUT");
        break;
    case VIDIOC_G_MODULATOR:
        sprintf(cmd_str, "VIDIOC_G_MODULATOR");
        break;
    case VIDIOC_S_MODULATOR:
        sprintf(cmd_str, "VIDIOC_S_MODULATOR");
        break;
    case VIDIOC_G_FREQUENCY:
        sprintf(cmd_str, "VIDIOC_G_FREQUENCY");
        break;
    case VIDIOC_S_FREQUENCY:
        sprintf(cmd_str, "VIDIOC_S_FREQUENCY");
        break;
    case VIDIOC_CROPCAP:
        sprintf(cmd_str, "VIDIOC_CROPCAP");
        break;
    case VIDIOC_G_CROP:
        sprintf(cmd_str, "VIDIOC_G_CROP");
        break;
    case VIDIOC_S_CROP:
        sprintf(cmd_str, "VIDIOC_S_CROP");
        break;
    case VIDIOC_G_JPEGCOMP:
        sprintf(cmd_str, "VIDIOC_G_JPEGCOMP");
        break;
    case VIDIOC_S_JPEGCOMP:
        sprintf(cmd_str, "VIDIOC_S_JPEGCOMP");
        break;
    case VIDIOC_QUERYSTD:
        sprintf(cmd_str, "VIDIOC_QUERYSTD");
        break;
    case VIDIOC_TRY_FMT:
        sprintf(cmd_str, "VIDIOC_TRY_FMT");
        break;
    case VIDIOC_ENUMAUDIO:
        sprintf(cmd_str, "VIDIOC_ENUMAUDIO");
        break;
    case VIDIOC_ENUMAUDOUT:
        sprintf(cmd_str, "VIDIOC_ENUMAUDOUT");
        break;
    case VIDIOC_G_PRIORITY:
        sprintf(cmd_str, "VIDIOC_G_PRIORITY");
        break;
    case VIDIOC_S_PRIORITY:
        sprintf(cmd_str, "VIDIOC_S_PRIORITY");
        break;
    case VIDIOC_G_SLICED_VBI_CAP:
        sprintf(cmd_str, "VIDIOC_G_SLICED_VBI_CAP");
        break;
    case VIDIOC_LOG_STATUS:
        sprintf(cmd_str, "VIDIOC_LOG_STATUS");
        break;
    case VIDIOC_G_EXT_CTRLS:
        sprintf(cmd_str, "VIDIOC_G_EXT_CTRLS");
        break;
    case VIDIOC_S_EXT_CTRLS:
        sprintf(cmd_str, "VIDIOC_S_EXT_CTRLS");
        break;
    case VIDIOC_TRY_EXT_CTRLS:
        sprintf(cmd_str, "VIDIOC_TRY_EXT_CTRLS");
        break;
    case VIDIOC_ENUM_FRAMESIZES:
        sprintf(cmd_str, "VIDIOC_ENUM_FRAMESIZES");
        break;
    case VIDIOC_ENUM_FRAMEINTERVALS:
        sprintf(cmd_str, "VIDIOC_ENUM_FRAMEINTERVALS");
        break;
    case VIDIOC_G_ENC_INDEX:
        sprintf(cmd_str, "VIDIOC_G_ENC_INDEX");
        break;
    case VIDIOC_ENCODER_CMD:
        sprintf(cmd_str, "VIDIOC_ENCODER_CMD");
        break;
    case VIDIOC_TRY_ENCODER_CMD:
        sprintf(cmd_str, "VIDIOC_TRY_ENCODER_CMD");
        break;
    case VIDIOC_DBG_S_REGISTER:
        sprintf(cmd_str, "VIDIOC_DBG_S_REGISTER");
        break;
    case VIDIOC_DBG_G_REGISTER:
        sprintf(cmd_str, "VIDIOC_DBG_G_REGISTER");
        break;
    case VIDIOC_S_HW_FREQ_SEEK:
        sprintf(cmd_str, "VIDIOC_S_HW_FREQ_SEEK");
        break;
    case VIDIOC_S_DV_TIMINGS:
        sprintf(cmd_str, "VIDIOC_S_DV_TIMINGS");
        break;
    case VIDIOC_G_DV_TIMINGS:
        sprintf(cmd_str, "VIDIOC_G_DV_TIMINGS");
        break;
    case VIDIOC_DQEVENT:
        sprintf(cmd_str, "VIDIOC_DQEVENT");
        break;
    case VIDIOC_SUBSCRIBE_EVENT:
        sprintf(cmd_str, "VIDIOC_SUBSCRIBE_EVENT");
        break;
    case VIDIOC_UNSUBSCRIBE_EVENT:
        sprintf(cmd_str, "VIDIOC_UNSUBSCRIBE_EVENT");
        break;
    case VIDIOC_CREATE_BUFS:
        sprintf(cmd_str, "VIDIOC_CREATE_BUFS");
        break;
    case VIDIOC_PREPARE_BUF:
        sprintf(cmd_str, "VIDIOC_PREPARE_BUF");
        break;
    case VIDIOC_G_SELECTION:
        sprintf(cmd_str, "VIDIOC_G_SELECTION");
        break;
    case VIDIOC_S_SELECTION:
        sprintf(cmd_str, "VIDIOC_S_SELECTION");
        break;
    case VIDIOC_DECODER_CMD:
        sprintf(cmd_str, "VIDIOC_DECODER_CMD");
        break;
    case VIDIOC_TRY_DECODER_CMD:
        sprintf(cmd_str, "VIDIOC_TRY_DECODER_CMD");
        break;
    case VIDIOC_ENUM_DV_TIMINGS:
        sprintf(cmd_str, "VIDIOC_ENUM_DV_TIMINGS");
        break;
    case VIDIOC_QUERY_DV_TIMINGS:
        sprintf(cmd_str, "VIDIOC_QUERY_DV_TIMINGS");
        break;
    case VIDIOC_DV_TIMINGS_CAP:
        sprintf(cmd_str, "VIDIOC_DV_TIMINGS_CAP");
        break;
    case VIDIOC_ENUM_FREQ_BANDS:
        sprintf(cmd_str, "VIDIOC_ENUM_FREQ_BANDS");
        break;
    case VIDIOC_DBG_G_CHIP_INFO:
        sprintf(cmd_str, "VIDIOC_DBG_G_CHIP_INFO");
        break;
    case VIDIOC_QUERY_EXT_CTRL:
        sprintf(cmd_str, "VIDIOC_QUERY_EXT_CTRL");
        break;
    default:
        sprintf(cmd_str, "UNKNOWN_CMD");
        break;
    }
    return cmd_str;
}
