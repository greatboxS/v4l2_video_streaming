
/*******************************************************************************
#             uvccapture: USB UVC Video Class Snapshot Software                #
#This package work with the Logitech UVC based webcams with the mjpeg feature  #
#.                                                                             #
# 	Orginally Copyright (C) 2005 2006 Laurent Pinchart &&  Michel Xhaard   #
#       Modifications Copyright (C) 2006  Gabriel A. Devenyi                   #
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

#include "v4l2uvc.h"
#include "v4l2debug.h"
union pantilt
{
    struct
    {
        short pan;
        short tilt;
    } s16;
    int value;
} pantilt;

static unsigned char dht_data[DHT_SIZE] = {
    0xff, 0xc4, 0x01, 0xa2, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x01, 0x00, 0x03,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0a, 0x0b, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05,
    0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04,
    0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22,
    0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15,
    0x52, 0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
    0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95,
    0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
    0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2,
    0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5,
    0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
    0xfa, 0x11, 0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05,
    0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04,
    0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22,
    0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33,
    0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25,
    0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
    0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94,
    0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba,
    0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa};

static unsigned int n_buffer = DEFAULT_NUM_BUFFER;
static unsigned int currenGrabtIndex = 0;
static int v4l2_set_configuration(struct vdIn *vd);
/**/

int v4l2_video_capture_init(struct vdIn **videoIn, const char *device, int width,
                            int height, int format, int grabmethod, unsigned int n_buff)
{
    *videoIn = (struct vdIn *)calloc(1, sizeof(struct vdIn));

    if ((*videoIn) == NULL || device == NULL)
        return -1;
    if (width == 0 || height == 0)
        return -1;
    if (grabmethod < 0 || grabmethod > 1)
        grabmethod = 1; //mmap by default;

    n_buffer = n_buff;
    if (n_buffer > 60 || n_buffer == 0)
        n_buffer = DEFAULT_NUM_BUFFER;

    struct vdIn *vd = *videoIn;
    vd->videodevice = NULL;
    vd->status = NULL;
    vd->pictName = NULL;
    vd->videodevice = (char *)calloc(1, 16 * sizeof(char));
    vd->status = (char *)calloc(1, 100 * sizeof(char));
    vd->pictName = (char *)calloc(1, 80 * sizeof(char));
    vd->mem = (struct mem_buffer *)calloc(n_buffer, sizeof(*vd->mem));
    snprintf(vd->videodevice, 12, "%s", device);
    vd->toggleAvi = 0;
    vd->getPict = 0;
    vd->signalquit = 1;
    vd->width = width;
    vd->height = height;
    vd->formatIn = format;
    vd->grabmethod = grabmethod;
    if (v4l2_set_configuration(vd) < 0)
    {
        fprintf(stderr, " Init v4L2 failed !! exit fatal \n");
        v4l2_viceo_capture_remove(*videoIn);
        return -1;
    }

    /* alloc a temp buffer to reconstruct the pict */
    vd->framesizeIn = (vd->width * vd->height << 1);
    switch (vd->formatIn)
    {
    case V4L2_PIX_FMT_MJPEG:
        vd->tmpbuffer = (unsigned char *)calloc(1, (size_t)vd->framesizeIn);
        if (!vd->tmpbuffer)
            goto error;
        vd->framebuffer = (unsigned char *)calloc(1, (size_t)vd->width * (vd->height + 8) * 2);
        break;
    case V4L2_PIX_FMT_YUYV:
        vd->framebuffer = (unsigned char *)calloc(1, (size_t)vd->framesizeIn);
        break;
    default:
        fprintf(stderr,  " should never arrive exit fatal !!\n");
        goto error;
        break;
    }
    if (!vd->framebuffer)
        goto error;
    return 0;
error:
//    free(vd->videodevice);
//    free(vd->status);
//    free(vd->pictName);
//    close(vd->fd);
    return -1;
}

static int v4l2_set_configuration(struct vdIn *vd)
{
    int i;
    int ret = 0;

    if(!vd)
        return -1;

    if ((vd->fd = open(vd->videodevice, O_RDWR)) == -1)
    {
        perror("ERROR opening V4L interface\n");
        fprintf(stderr,  stderr, "%s\n",  vd->videodevice);
        return -1;
    }
    memset(&vd->cap, 0, sizeof(struct v4l2_capability));
    ret = xioctl(vd->fd, VIDIOC_QUERYCAP, &vd->cap);
    if (ret < 0)
    {
        fprintf(stderr,  "Error opening device %s: unable to query device.\n", vd->videodevice);
        return -1;
    }

    if ((vd->cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
    {
        fprintf(stderr,  "Error opening device %s: video capture not supported.\n", vd->videodevice);
        return -1;
    }

    if (vd->grabmethod)
    {
        if (!(vd->cap.capabilities & V4L2_CAP_STREAMING))
        {
            fprintf(stderr,  "%s does not support streaming i/o\n", vd->videodevice);
            return -1;
        }
    }
    else
    {
        if (!(vd->cap.capabilities & V4L2_CAP_READWRITE))
        {
            fprintf(stderr,  "%s does not support read i/o\n", vd->videodevice);
            return -1;
        }
    }

#ifdef USE_DEBUG
    fprintf(stderr,  "Driver Caps:\n"
                     "  Driver: \"%s\"\n"
                     "  Card: \"%s\"\n"
                     "  Bus: \"%s\"\n"
                     "  Version: %d.%d\n"
                     "  Capabilities: %08x\n",
            vd->cap.driver,
            vd->cap.card,
            vd->cap.bus_info,
            (vd->cap.version >> 16) && 0xff,
            (vd->cap.version >> 24) && 0xff,
            vd->cap.capabilities);

    struct v4l2_cropcap cropcap = {0};
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (xioctl(vd->fd, VIDIOC_CROPCAP, &cropcap) < 0)
    {
        fprintf(stderr,  "Querying Cropping Capabilities");
        return -1;
    }
    fprintf(stderr,  "Camera Cropping:\n"
                     "  Bounds: %dx%d+%d+%d\n"
                     "  Default: %dx%d+%d+%d\n"
                     "  Aspect: %d/%d\n",
            cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
            cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
            cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);

    int support_grbg10 = 0;

    struct v4l2_fmtdesc fmtdesc = {0};
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    char fourcc[5] = {0};
    char c, e;
    fprintf(stderr,  "  FMT : CE Desc\n--------------------\n");
    while (0 == xioctl(vd->fd, VIDIOC_ENUM_FMT, &fmtdesc))
    {
        strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
        if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
            support_grbg10 = 1;
        c = fmtdesc.flags & 1 ? 'C' : ' ';
        e = fmtdesc.flags & 2 ? 'E' : ' ';
        fprintf(stderr,  "  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
        fmtdesc.index++;
    }
#endif

    /* set format in */
    memset(&vd->fmt, 0, sizeof(struct v4l2_format));
    vd->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->fmt.fmt.pix.width = vd->width;
    vd->fmt.fmt.pix.height = vd->height;
    vd->fmt.fmt.pix.pixelformat = vd->formatIn;
    vd->fmt.fmt.pix.field = V4L2_FIELD_ANY;

    ret = xioctl(vd->fd, VIDIOC_S_FMT, &vd->fmt);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to set format: %d.\n", errno);
        return -1;
    }

    struct v4l2_format fmt = vd->fmt;
    char *buff = (char *)malloc(256);
    strncpy(buff, (char *)&fmt.fmt.pix.pixelformat, 4);
    fprintf(stderr,  "Selected Camera Mode:\n"
                     "  Width: %d\n"
                     "  Height: %d\n"
                     "  PixFmt: %s\n"
                     "  Field: %d\n",
            fmt.fmt.pix.width,
            fmt.fmt.pix.height,
            buff,
            fmt.fmt.pix.field);
    free(buff);

    if ((vd->fmt.fmt.pix.width != vd->width) ||
            (vd->fmt.fmt.pix.height != vd->height))
    {
        fprintf(stderr,  " format asked unavailable get width %d height %d \n",
                vd->fmt.fmt.pix.width, vd->fmt.fmt.pix.height);
        vd->width = vd->fmt.fmt.pix.width;
        vd->height = vd->fmt.fmt.pix.height;
        /* look the format is not part of the deal ??? */
        //vd->formatIn = vd->fmt.fmt.pix.pixelformat;
    }
    /* request buffers */
    memset(&vd->rb, 0, sizeof(struct v4l2_requestbuffers));
    vd->rb.count = n_buffer;
    vd->rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->rb.memory = V4L2_MEMORY_MMAP;

    ret = xioctl(vd->fd, VIDIOC_REQBUFS, &vd->rb);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to allocate buffers: %d.\n", errno);
        return -1;
    }
    /* map the buffers */
    for (i = 0; i < n_buffer; i++)
    {
        memset(&vd->buf, 0, sizeof(struct v4l2_buffer));
        vd->buf.index = i;
        vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        vd->buf.memory = V4L2_MEMORY_MMAP;
        ret = xioctl(vd->fd, VIDIOC_QUERYBUF, &vd->buf);
        if (ret < 0)
        {
            fprintf(stderr,  "Unable to query buffer (%d).\n", errno);
            return -1;
        }

        vd->mem[i].length = vd->buf.length;

        vd->mem[i].start = mmap(NULL, vd->buf.length,
                                PROT_READ | PROT_WRITE, /* recommended */
                                MAP_SHARED,             /* recommended */
                                vd->fd, vd->buf.m.offset);
        if (vd->mem[i].start == MAP_FAILED)
        {
            fprintf(stderr,  "Unable to map buffer (%d)\n", errno);
            return -1;
        }
#ifdef USE_DEBUG
        fprintf(stderr,  "index: %-3d length: %-10u offset: %-10u", i, vd->buf.length, vd->buf.m.offset);
        fprintf(stderr,  "- mapped at address %p (%lu) \n", vd->mem[i].start, vd->mem[i].start);
#endif
    }

    /* Queue the buffers. */
    for (i = 0; i < n_buffer; ++i)
    {
        memset(&vd->buf, 0, sizeof(struct v4l2_buffer));
        vd->buf.index = i;
        vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        vd->buf.memory = V4L2_MEMORY_MMAP;
        ret = xioctl(vd->fd, VIDIOC_QBUF, &vd->buf);
        if (ret < 0)
        {
            fprintf(stderr,  "Unable to queue buffer (%d).\n", errno);
            return -1;
        }
    }
    return 0;
}

int video_stream_on(struct vdIn *vd)
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret;

    ret = xioctl(vd->fd, VIDIOC_STREAMON, &type);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to %s capture: %d.\n", "start", errno);
        return ret;
    }
    vd->isstreaming = 1;
    return 0;
}

int video_stream_off(struct vdIn *vd)
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret;

    ret = xioctl(vd->fd, VIDIOC_STREAMOFF, &type);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to %s capture: %d.\n", "stop", errno);
        return ret;
    }
    vd->isstreaming = 0;
    return 0;
}

int v4l2_dequeue_buffer(struct vdIn* vd)
{
    memset(&vd->buf, 0, sizeof(struct v4l2_buffer));
    vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->buf.memory = V4L2_MEMORY_MMAP;
    int ret = xioctl(vd->fd, VIDIOC_DQBUF, &vd->buf);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to dequeue buffer (%d).\n", errno);
        return -1;
    }
    return 0;
}

int v4l2_queue_buffer(struct vdIn* vd)
{
    int ret = xioctl(vd->fd, VIDIOC_QBUF, &vd->buf);
    if (ret < 0)
    {
        fprintf(stderr,  "Unable to requeue buffer (%d).\n", errno);
        return -1;
    }

    return 0;
}

int v4l2_uvc_grab(struct vdIn *vd)
{
    int ret = -1;

#define HEADERFRAME1 0xaf
    /* Camera start streaming */
    if (!vd->isstreaming)
    {
        if (video_stream_on(vd))
            goto err;
    }

    if(ret = v4l2_dequeue_buffer(vd) < 0)
        goto err;

    vd->currentGrabIndex = vd->buf.index;

    switch (vd->formatIn)
    {
    case V4L2_PIX_FMT_MJPEG:

        memcpy(vd->tmpbuffer, vd->mem[vd->buf.index].start, HEADERFRAME1);
        memcpy(vd->tmpbuffer + HEADERFRAME1, dht_data, DHT_SIZE);
        memcpy(vd->tmpbuffer + HEADERFRAME1 + DHT_SIZE,
               vd->mem[vd->buf.index].start + HEADERFRAME1,
                (vd->buf.bytesused - HEADERFRAME1));

#ifdef USE_DEBUG
        fprintf(stderr,  "V4L2_PIX_FMT_MJPEG: index %d, framezieIn %lu, byte used %lu\n",
                vd->buf.index,
                (size_t)vd->framesizeIn,
                (size_t)vd->buf.bytesused);
#endif
        break;

    case V4L2_PIX_FMT_YUYV:
        if (vd->buf.bytesused > vd->framesizeIn)
            memcpy(vd->framebuffer, vd->mem[vd->buf.index].start, (size_t)vd->framesizeIn);
        else
            memcpy(vd->framebuffer, vd->mem[vd->buf.index].start, (size_t)vd->buf.bytesused);

#ifdef USE_DEBUG
        fprintf(stderr,  "V4L2_PIX_FMT_YUYV: index %d, framezieIn %lu, byte used %lu\n",
                vd->buf.index,
                (size_t)vd->framesizeIn,
                (size_t)vd->buf.bytesused);
#endif
        break;

    default:
        goto err;
        break;
    }
#ifdef USE_DEBUG
    v4l2_write_image(vd, "snap.jpeg");
#endif

    if(ret = v4l2_queue_buffer(vd) < 0)
        goto err;

    return 0;

err:
    vd->signalquit = 0;
    return -1;
}

struct mem_buffer *v4l2_get_buffer(struct vdIn *vd)
{
    if (!vd)
        return NULL;
    if (!vd->mem)
        return NULL;

    if (vd->currentGrabIndex >= n_buffer)
        vd->currentGrabIndex = 0;

    return &vd->mem[vd->currentGrabIndex];
}

int v4l2_write_image(struct vdIn *vd, const char *file)
{
    int fd;
    if ((fd = open(file, O_WRONLY | O_CREAT, 0660)) < 0)
    {
        perror("open");
        return -1;
    }

    write(fd, vd->mem[vd->buf.index].start, vd->mem[vd->buf.index].length);
    close(fd);
    return 0;
}

int v4l2_viceo_capture_remove(struct vdIn *vd)
{
    int i;
    if(!vd)
        return 0;

    if (vd->isstreaming)
        video_stream_off(vd);

    /* If the memory maps are not released the device will remain opened even
     after a call to close(); */
    for (i = 0; i < n_buffer; i++)
    {
        if(vd->mem[i].start)
            munmap(vd->mem[i].start, vd->mem[i].length);
    }

    if (vd->tmpbuffer)
        free(vd->tmpbuffer);
    vd->tmpbuffer = NULL;
    free(vd->framebuffer);
    vd->framebuffer = NULL;
    free(vd->videodevice);
    free(vd->status);
    free(vd->pictName);
    vd->videodevice = NULL;
    vd->status = NULL;
    vd->pictName = NULL;
    close(vd->fd);
    free(vd->mem);
    free(vd);
    vd = NULL;
    return 0;
}

/* return >= 0 ok otherwhise -1 */
static int v4l2_verify_ctrl(struct vdIn *vd, int control, struct v4l2_queryctrl *queryctrl)
{
    int err = 0;

    queryctrl->id = control;
    if ((err = xioctl(vd->fd, VIDIOC_QUERYCTRL, queryctrl)) < 0)
    {
        fprintf(stderr,  "ioctl querycontrol error %d \n", errno);
    }
    else if (queryctrl->flags & V4L2_CTRL_FLAG_DISABLED)
    {
        fprintf(stderr,  "control %s disabled \n", (char *)queryctrl->name);
    }
    else if (queryctrl->flags & V4L2_CTRL_TYPE_BOOLEAN)
    {
        return 1;
    }
    else if (queryctrl->type & V4L2_CTRL_TYPE_INTEGER)
    {
        return 0;
    }
    else
    {
        fprintf(stderr,  "contol %s unsupported  \n", (char *)queryctrl->name);
    }
    return -1;
}

int v4l2_get_ctrl(struct vdIn *vd, int control)
{
    struct v4l2_queryctrl queryctrl;
    struct v4l2_control control_s;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    control_s.id = control;
    if ((err = xioctl(vd->fd, VIDIOC_G_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl get control error\n");
        return -1;
    }
    return control_s.value;
}

int v4l2_set_ctrl(struct vdIn *vd, int control, int value)
{
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int min, max, step, val_def;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    min = queryctrl.minimum;
    max = queryctrl.maximum;
    step = queryctrl.step;
    val_def = queryctrl.default_value;
    if ((value >= min) && (value <= max))
    {
        control_s.id = control;
        control_s.value = value;
        if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
        {
            fprintf(stderr,  "ioctl set control error\n");
            return -1;
        }
    }
    return 0;
}

int v4l2_up_ctrl(struct vdIn *vd, int control)
{
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int min, max, current, step, val_def;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    min = queryctrl.minimum;
    max = queryctrl.maximum;
    step = queryctrl.step;
    val_def = queryctrl.default_value;
    current = v4l2_get_ctrl(vd, control);
    current += step;
    if (current <= max)
    {
        control_s.id = control;
        control_s.value = current;
        if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
        {
            fprintf(stderr,  "ioctl set control error\n");
            return -1;
        }
    }
    return control_s.value;
}

int v4l2_down_ctrl(struct vdIn *vd, int control)
{
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int min, max, current, step, val_def;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    min = queryctrl.minimum;
    max = queryctrl.maximum;
    step = queryctrl.step;
    val_def = queryctrl.default_value;
    current = v4l2_get_ctrl(vd, control);
    current -= step;
    if (current >= min)
    {
        control_s.id = control;
        control_s.value = current;
        if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
        {
            fprintf(stderr,  "ioctl set control error\n");
            return -1;
        }
    }
    return control_s.value;
}

int v4l2_toggle_ctrl(struct vdIn *vd, int control)
{
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int current;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) != 1)
        return -1;
    current = v4l2_get_ctrl(vd, control);
    control_s.id = control;
    control_s.value = !current;
    if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl toggle control error\n");
        return -1;
    }
    return control_s.value;
}

int v4l2_reset_ctrl(struct vdIn *vd, int control)
{
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int val_def;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    val_def = queryctrl.default_value;
    control_s.id = control;
    control_s.value = val_def;

    if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl reset control error\n");
        return -1;
    }

    return 0;
}

int v4l2_reset_pan_tilt(struct vdIn *vd, int pantilt)
{
    int control = V4L2_CID_PANTILT_RESET;
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    unsigned char val;
    int err;

    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;
    val = (unsigned char)pantilt;
    control_s.id = control;
    control_s.value = val;
    if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl reset Pan control error\n");
        return -1;
    }

    return 0;
}

int v4l2_up_down_pan(struct vdIn *vd, short inc)
{
    int control = V4L2_CID_PANTILT_RELATIVE;
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int err;

    union pantilt pan;

    control_s.id = control;
    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;

    pan.s16.pan = inc;
    pan.s16.tilt = 0;

    control_s.value = pan.value;
    if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl pan updown control error\n");
        return -1;
    }
    return 0;
}

int v4l2_up_down_tilt(struct vdIn *vd, short inc)
{
    int control = V4L2_CID_PANTILT_RELATIVE;
    struct v4l2_control control_s;
    struct v4l2_queryctrl queryctrl;
    int err;
    union pantilt pan;

    control_s.id = control;
    if (v4l2_verify_ctrl(vd, control, &queryctrl) < 0)
        return -1;

    pan.s16.pan = 0;
    pan.s16.tilt = inc;

    control_s.value = pan.value;
    if ((err = xioctl(vd->fd, VIDIOC_S_CTRL, &control_s)) < 0)
    {
        fprintf(stderr,  "ioctl tiltupdown control error\n");
        return -1;
    }
    return 0;
}

int xioctl(int fh, int request, void *arg)
{
    int r;
    do
    {
        r = ioctl(fh, request, arg);
    } while (r == -1 && ((errno == EINTR) || (errno == EAGAIN)));

#ifdef USE_DEBUG
    if (r == -1)
    {
        fprintf(stderr,  "Error: %d, %-20s", errno, strerror(errno));
        fprintf(stderr,  "Cmd: %-20s", v4l2debug_ioctl_cmd(request));
        switch (request)
        {
        case VIDIOC_QUERYCTRL:
            fprintf(stderr,  "Ctrl_Id: %-20s", v4l2debug_control_id(((struct v4l2_queryctrl *)arg)->id));
            break;
        case VIDIOC_S_CTRL:
            fprintf(stderr,  "Ctrl_Id: %-20s, Value: %d",
                    v4l2debug_control_id(((struct v4l2_control *)arg)->id),
                    ((struct v4l2_control *)arg)->value);
            break;
        case VIDIOC_G_CTRL:
            fprintf(stderr,  "Ctrl_Id: %-20s, Value: %d",
                    v4l2debug_control_id(((struct v4l2_control *)arg)->id),
                    ((struct v4l2_control *)arg)->value);
            break;
        default:
            break;
        }
        fprintf(stderr,  "\r\n");
    }
#endif

    return r;
}
