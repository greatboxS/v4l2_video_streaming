
/*******************************************************************************
#             uvccapture: USB UVC Video Class Snapshot Software                #
#This package work with the Logitech UVC based webcams with the mjpeg feature  #
#                                                                              #
#       Orginally Copyright (C) 2005 2006 Laurent Pinchart &&  Michel Xhaard   #
#       Modifications Copyright (C) 2006 Gabriel A. Devenyi                    #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program; if not, write to the Free Software                  #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    #
#                                                                              #
*******************************************************************************/

#ifndef __V4L2UVC_H
#define __V4L2UVC_H

#define DHT_SIZE 420

// #define V4L2_CID_BACKLIGHT_COMPENSATION (V4L2_CID_PRIVATE_BASE + 0)
// #define V4L2_CID_POWER_LINE_FREQUENCY (V4L2_CID_PRIVATE_BASE + 1)
// #define V4L2_CID_SHARPNESS (V4L2_CID_PRIVATE_BASE + 2)
// #define V4L2_CID_HUE_AUTO (V4L2_CID_PRIVATE_BASE + 3)
// #define V4L2_CID_FOCUS_AUTO (V4L2_CID_PRIVATE_BASE + 4)
// #define V4L2_CID_FOCUS_ABSOLUTE (V4L2_CID_PRIVATE_BASE + 5)
// #define V4L2_CID_FOCUS_RELATIVE (V4L2_CID_PRIVATE_BASE + 6)

#define V4L2_CID_PANTILT_RELATIVE (V4L2_CID_PRIVATE_BASE + 7)
#define V4L2_CID_PANTILT_RESET (V4L2_CID_PRIVATE_BASE + 8)

#define USE_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <linux/videodev2.h>
#include <linux/v4l2-controls.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#if __cplusplus
extern "C"
{
#endif

#define DEFAULT_IMAGE_WIDTH 720
#define DEFAULT_IMAGE_HEIGHT 1280
#define DEFAULT_PIXEL_FORMAT  V4L2_PIX_FMT_MJPEG //V4L2_PIX_FMT_YUYV
#define DEFAULT_NUM_BUFFER 4
#define DEFAULT_GRAB_METHOD 1

// Quick initialize a default setting capture camera
#define CAMERA_INIT(x, device) v4l2_video_capture_init(&(x), device,         \
                                                       DEFAULT_IMAGE_WIDTH,  \
                                                       DEFAULT_IMAGE_HEIGHT, \
                                                       DEFAULT_PIXEL_FORMAT, \
                                                       DEFAULT_GRAB_METHOD,  \
                                                       DEFAULT_NUM_BUFFER)

    struct mem_buffer
    {
        void *start;   // pointer to requested buffer
        size_t length; // length of requested buffer
    };

    struct vdIn
    {
        int fd;
        char *videodevice;
        char *status;
        char *pictName;
        struct v4l2_capability cap;
        struct v4l2_format fmt;
        struct v4l2_buffer buf;
        struct v4l2_requestbuffers rb;
        struct mem_buffer *mem;
        unsigned char *tmpbuffer;
        unsigned char *framebuffer;
        int isstreaming;
        int grabmethod;
        int width;
        int height;
        int formatIn;
        int formatOut;
        int framesizeIn;
        int signalquit;
        int toggleAvi;
        int getPict;
        unsigned int currentGrabIndex;
    };

    int v4l2_video_capture_init(struct vdIn **videoIn, const char *device, int width, int height,
                                int format, int grabmethod, unsigned int n_buff);
    int v4l2_viceo_capture_remove(struct vdIn *vd);
    int v4l2_uvc_grab(struct vdIn *vd);
    int v4l2_write_image(struct vdIn *vd, const char *file);

    int v4l2_get_ctrl(struct vdIn *vd, int control);
    int v4l2_set_ctrl(struct vdIn *vd, int control, int value);

    int v4l2_dequeue_buffer(struct vdIn* vd);
    int v4l2_queue_buffer(struct vdIn*vd);

    struct mem_buffer* v4l2_get_buffer(struct vdIn* vd);

    int v4l2_up_ctrl(struct vdIn *vd, int control);
    int v4l2_down_ctrl(struct vdIn *vd, int control);
    int v4l2_toggle_ctrl(struct vdIn *vd, int control);
    int v4l2_reset_ctrl(struct vdIn *vd, int control);
    int v4l2_reset_pan_tilt(struct vdIn *vd, int pantilt);
    int v4L2_up_down_pan(struct vdIn *vd, short inc);
    int v4L2_up_down_tilt(struct vdIn *vd, short inc);

    int video_stream_on(struct vdIn *vd);
    int video_stream_off(struct vdIn *vd);
    int xioctl(int fh, int request, void *arg);

#if __cplusplus
}
#endif

#endif
