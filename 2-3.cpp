#include <fcntl.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <linux/fb.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct framebuffer_info
{
    uint32_t bits_per_pixel;    // depth of framebuffer
    uint32_t xres_virtual;      // how many pixel in a row in virtual screen
    uint32_t yres_virtual;      // how many pixel in a col in virtual screen
};
struct framebuffer_info get_framebuffer_info ( const char *framebuffer_device_path );
static bool capVideo;
static bool end;

int main (int argc, const char *argv[])
{
    // variable to store the frame get from video stream
    cv::Mat frame, frameDst, frameResize;
    cv::Size2f frame_size;
	const char border[320] = {0};
	char fileName[128] = {0};
    
    // open video stream device
    cv::VideoCapture camera(2);

    // get info of the framebuffer
    framebuffer_info fb_info = get_framebuffer_info("/dev/fb0");

    // open the framebuffer device
    std::ofstream ofs("/dev/fb0");
    if (!ofs) 
    { 
        printf("can't open ofs\r\n");
        return 1; 
    } 

    // check if video stream device is opened success or not
	int deviceID = 2;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    int cnt = 0;
	camera.open(deviceID, apiID);
    // check if we succeeded
    if (!camera.isOpened()) 
    {
        printf("ERROR! Unable to open camera\n");
        return -1;
    }

    // set propety of the frame
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

	cv::VideoWriter output;
    output.open("/run/media/mmcblk1p1/test.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5.0, cv::Size( 640, 480 ), true);
    int count = 0;

    while ( end == false )
    {
        // get video frame from stream
        printf("count %d\r\n", count);
        if (count == 0)
           frame = cv::imread("/root/sEG1.png");
        else if (count == 1)
           frame = cv::imread("/root/sEG2.png");
        else if (count == 2)
           frame = cv::imread("/root/sEG3.png");
        else if (count == 3)
           frame = cv::imread("/root/sEG4.png");
        else if (count == 4)
           frame = cv::imread("/root/sEG5.png");
        else if (count == 5)
           frame = cv::imread("/root/sEG6.png");
        else if (count == 6)
           frame = cv::imread("/root/sEG7.png");
        else if (count == 7)
           frame = cv::imread("/root/sEG8.png");
        else if (count == 8)
           frame = cv::imread("/root/sEG9.png");
        else if (count == 8)
           frame = cv::imread("/root/sEG10.png");
        else    
            camera.read(frame);
        count ++;

        if (frame.empty()) 
        {
            printf("ERROR! blank frame grabbed\n");
            break;
        }
		if (capVideo) 
        {
			sprintf(fileName, "%s%d.png","/run/media/mmcblk1p1/",cnt);
            bool rslt = cv::imwrite(fileName, frame);
	        printf("save %s %d\n",fileName, rslt);
			cnt++;
			capVideo = false;
		
        }        
        // get size of the video frame
        cv::Size targetSize = cv::Size(960,720);
        cv::resize(frame, frameResize, targetSize, 0, 0, cv::INTER_AREA); 
        // transfer color space from BGR to BGR565 (16-bit image) to fit the requirement of the LCD
	    cv::cvtColor(frameResize, frameDst, cv::COLOR_BGR2BGR565);
		output << frame;
        frame_size = frameDst.size();
        // output the video frame to framebufer row by row
        for ( int y = 0; y < frame_size.height; y++ )
        {
            // move to the next written position of output device framebuffer by "std::ostream::seekp()"
			ofs.seekp(y*fb_info.xres_virtual*fb_info.bits_per_pixel/8);
			ofs.write(border, sizeof(border));

            // write to the framebuffer by "std::ostream::write()"
            ofs.write(reinterpret_cast<char*>(frameDst.ptr(y)), frame_size.width*2);
			ofs.write(border, sizeof(border));
		}
    }
    // closing video stream
    camera.release();
    return 0;
}

struct framebuffer_info get_framebuffer_info(const char *framebuffer_device_path)
{
    struct framebuffer_info fb_info;        // Used to return the required attrs.
    struct fb_var_screeninfo screen_info;   // Used to get attributes of the device from OS kernel.

    // open device with linux system call "open()"
	int fd = open(framebuffer_device_path, O_RDWR);
	
    // get attributes of the framebuffer device thorugh linux system call "ioctl()".
    if (ioctl(fd, FBIOGET_VSCREENINFO, &screen_info) != 0)
    {
        printf("error read screen_info");
    }

    // put the required attributes in variable "fb_info" you found with "ioctl() and return it."
    fb_info.xres_virtual =  screen_info.xres_virtual;     // 8
    fb_info.yres_virtual =  screen_info.yres_virtual;     // 8
	fb_info.bits_per_pixel = screen_info.bits_per_pixel;    // 16
    printf("res %d %d %d\r\n", fb_info.xres_virtual, fb_info.yres_virtual, fb_info.bits_per_pixel );
    return fb_info;
};
