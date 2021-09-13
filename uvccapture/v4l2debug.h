#ifndef __V4L2DEBUG_H__
#define __V4L2DEBUG_H__

#if __cpluscplus
extern "C"
#endif

#define DEBUG_BUFF_MAX_SIZE 256

const char* v4l2debug_ioctl_cmd(unsigned int cmd);
const char* v4l2debug_control_id(unsigned int control_id);

#if __cpluscplus
}
#endif


#endif // __V4L2DEBUG_H__