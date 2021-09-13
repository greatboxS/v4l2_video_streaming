#ifndef __V4L2_CAPTURE_H__
#define __V4L2_CAPTURE_H__

/*
 *  V4L2 video capture example
 *
 *  This program can be used and distributed without restrictions.
 *
 *      This program is provided with the V4L2 API
 * see https://linuxtv.org/docs.php for more information
 */
#if __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdlib.h>

    typedef enum 
    {
        IO_METHOD_READ,
        IO_METHOD_MMAP,
        IO_METHOD_USERPTR,
    }io_method;

    struct buffer
    {
        void *start;
        size_t length;
    };

    // int xioctl(int fh, int request, void *arg);
    // void v4l2_process_image(const void *p, int size);
    // int v4l2_read_frame(void);
    // void v4l2_stop_capturing(void);
    // void v4l2_start_capturing(void);

    // void v4l2_uninit_device(void);
    // void v4l2_init_mmap(void);
    // void v4l2_init_userp(unsigned int buffer_size);

    // void v4l2_init_device(const char* device_name, io_method method, unsigned int num_frame);
    // void v4l2_close_device(void);
    // void v4l2_open_device(void);

#if __cplusplus
}
#endif

#endif // __V4L2_CAPTURE_H__