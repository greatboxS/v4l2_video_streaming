
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
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <jpeglib.h>
#include <time.h>
#include <linux/videodev2.h>
#include "v4l2uvc.h"

// #include <opencv4/opencv2/core/core.hpp>
// #include <opencv4/opencv2/highgui/highgui.hpp>

// #define VERSION "v.1.0"
static const char version[] = VERSION;
int run = 1;

void sigcatch(int sig)
{
    printf("Exiting...\n");
    run = 0;
}

void usage(void)
{
    printf("uvccapture version %s\n", version);
    printf("Usage is: uvccapture [options]\n");
    printf("Options:\n");
    printf("-v\t\tVerbose\n");
    printf("-o<filename>\tOutput filename(default: snap.jpg)\n");
    printf("-d<device>\tV4L2 Device(default: /dev/video0)\n");
    printf(
        "-x<width>\tImage Width(must be supported by device)(>960 activates YUYV capture)\n");
    printf(
        "-y<height>\tImage Height(must be supported by device)(>720 activates YUYV capture)\n");
    printf(
        "-c<command>\tCommand to run after each image capture(executed as <command> <output_filename>)\n");
    printf(
        "-t<integer>\tTake continuous shots with <integer> seconds between them (0 for single shot)\n");
    printf(
        "-q<percentage>\tJPEG Quality Compression Level (activates YUYV capture)\n");
    printf("-r\t\tUse read instead of mmap for image capture\n");
    printf(
        "-w\t\tWait for capture command to finish before starting next capture\n");
    printf("-m\t\tToggles capture mode to YUYV capture\n");
    printf("Camera Settings:\n");
    printf("-B<integer>\tBrightness\n");
    printf("-C<integer>\tContrast\n");
    printf("-S<integer>\tSaturation\n");
    printf("-G<integer>\tGain\n");
    exit(8);
}

int spawn(char *argv[], int wait, int verbose)
{
    pid_t pid;
    int rv;

    switch (pid = fork())
    {
    case -1:
        return -1;
    case 0:
        // CHILD
        execvp(argv[0], argv);
        printf("Error executing command '%s'\n", argv[0]);
        exit(1);
    default:
        // PARENT
        if (wait == 1)
        {
            if (verbose >= 1)
                printf("Waiting for command to finish...");
            waitpid(pid, &rv, 0);
            if (verbose >= 1)
                printf("\n");
        }
        else
        {
            // Clean zombies
            waitpid(-1, &rv, WNOHANG);
            rv = 0;
        }
        break;
    }

    return rv;
}

int compress_yuyv_to_jpeg(struct vdIn *vd, FILE *file, int quality)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    unsigned char *line_buffer, *yuyv;
    int z;

    line_buffer = (unsigned char *)calloc(vd->width * 3, 1);
    yuyv = vd->framebuffer;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file);

    cinfo.image_width = vd->width;
    cinfo.image_height = vd->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    z = 0;
    while (cinfo.next_scanline < cinfo.image_height)
    {
        int x;
        unsigned char *ptr = line_buffer;

        for (x = 0; x < vd->width; x++)
        {
            int r, g, b;
            int y, u, v;

            if (!z)
                y = yuyv[0] << 8;
            else
                y = yuyv[2] << 8;
            u = yuyv[1] - 128;
            v = yuyv[3] - 128;

            r = (y + (359 * v)) >> 8;
            g = (y - (88 * u) - (183 * v)) >> 8;
            b = (y + (454 * u)) >> 8;

            *(ptr++) = (r > 255) ? 255 : ((r < 0) ? 0 : r);
            *(ptr++) = (g > 255) ? 255 : ((g < 0) ? 0 : g);
            *(ptr++) = (b > 255) ? 255 : ((b < 0) ? 0 : b);

            if (z++)
            {
                z = 0;
                yuyv += 4;
            }
        }

        row_pointer[0] = line_buffer;
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    free(line_buffer);

    return (0);
}

char *videodevice = "/dev/video0";
char *outputfile = "snap.jpg";
int format = V4L2_PIX_FMT_MJPEG;
int grabmethod = 1;
int width = 1280;
int height = 720;
int brightness = 100, contrast = 50, saturation = 0, gain = 0;
int verbose = 10;
int delay = 1;
int quality = 95;
time_t ref_time;
FILE *file;
struct vdIn *videoIn;

int main(int argc, char *argv[])
{
    // Option

    // Options Parsing (FIXME)
    // if ((width > 960) || (height > 720) || (quality != 95))
    //     format = V4L2_PIX_FMT_YUYV;

    if (v4l2_video_capture_init(&videoIn, (char *)videodevice, width, height, format, grabmethod) < 0)
        goto app_exit;

    //Reset all camera controls
    // v4l2_reset_ctrl(videoIn, V4L2_CID_BRIGHTNESS);
    // v4l2_reset_ctrl(videoIn, V4L2_CID_CONTRAST);
    // v4l2_reset_ctrl(videoIn, V4L2_CID_SATURATION);
    // v4l2_reset_ctrl(videoIn, V4L2_CID_GAIN);

    //Setup Camera Parameters

    if (brightness != 0)
    {
        if (verbose >= 1)
            printf("Setting camera brightness to %d\n", brightness);
        v4l2_set_ctrl(videoIn, V4L2_CID_BRIGHTNESS, brightness);
    }
    // else if (verbose >= 1)
    // {
    //     printf( "Camera brightness level is %d\n",
    //             v4l2_get_ctrl(videoIn, V4L2_CID_BRIGHTNESS));
    // }
    // if (contrast != 0)
    // {
    //     if (verbose >= 1)
    //         printf( "Setting camera contrast to %d\n", contrast);
    //     v4l2_set_ctrl(videoIn, V4L2_CID_CONTRAST, contrast);
    // }
    // else if (verbose >= 1)
    // {
    //     printf( "Camera contrast level is %d\n",
    //             v4l2_get_ctrl(videoIn, V4L2_CID_CONTRAST));
    // }
    // if (saturation != 0)
    // {
    //     if (verbose >= 1)
    //         printf( "Setting camera saturation to %d\n", saturation);
    //     v4l2_set_ctrl(videoIn, V4L2_CID_SATURATION, saturation);
    // }
    // else if (verbose >= 1)
    // {
    //     printf( "Camera saturation level is %d\n",
    //             v4l2_get_ctrl(videoIn, V4L2_CID_SATURATION));
    // }
    // if (gain != 0)
    // {
    //     if (verbose >= 1)
    //         printf( "Setting camera gain to %d\n", gain);
    //     v4l2_set_ctrl(videoIn, V4L2_CID_GAIN, gain);
    // }
    // else if (verbose >= 1)
    // {
    //     printf( "Camera gain level is %d\n",
    //             v4l2_get_ctrl(videoIn, V4L2_CID_GAIN));
    // }

    ref_time = time(NULL);

    while (run)
    {
        if (v4l2_uvc_grab(videoIn) < 0)
        {
            printf("Error grabbing\n");
            goto app_exit;
        }

        if ((difftime(time(NULL), ref_time) > delay) || delay == 0)
        {
            if (verbose >= 1)
                printf("Saving image to: %s\n", outputfile);
            file = fopen(outputfile, "wb");
            if (!file)
                printf("Can not open image to write\n");

            if (file != NULL)
            {
                switch (videoIn->formatIn)
                {
                case V4L2_PIX_FMT_YUYV:
                    compress_yuyv_to_jpeg(videoIn, file, quality);
                    printf("convert V4L2_PIX_FMT_YUYV to JPEG\n");
                    break;
                default:
                    fwrite(videoIn->tmpbuffer, videoIn->buf.bytesused + DHT_SIZE, 1, file);
                    break;
                }
                fclose(file);
                videoIn->getPict = 0;
            }

            ref_time = time(NULL);
        }
        if (delay == 0)
            break;
    }

app_exit:
    v4l2_viceo_capture_remove(videoIn);
    return 0;
}