#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/fb.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

struct framebuffer_info 
{
    uint32_t bits_per_pixel;    // depth of framebuffer
    uint32_t xres_virtual;      // how many pixel in a row in virtual screen
    uint32_t yres_virtual;      // how many pixel in a col in virtual screen
};
struct framebuffer_info get_framebuffer_info(const char *framebuffer_device_path);
int getch(void);
void* key_tsk(void* data);
static bool capVideo;

int main(int argc, const char *argv[])
{
    // variable to store the frame get from video stream
    cv::Mat frame, frameDst;
    cv::Size2f frame_size;
	const char border[160] = {0};
	char fileName[128] = {0};
	pthread_t t;

    // get info of the framebuffer
    framebuffer_info fb_info = get_framebuffer_info("/dev/fb0");

    // open the framebuffer device
    std::ofstream ofs("/dev/fb0");
    if (!ofs) 
    { 
        printf("Can't open ofs!\r\n");
        return -1;
    } 

    // open video stream device
    cv::VideoCapture camera(2);
    // check if video stream device is opened success or not
	int deviceID = 2;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    int cnt = 0;
	camera.open(deviceID, apiID);
    if (!camera.isOpened()) 
    {
        printf("ERROR! Unable to open camera.\n");
        return -1;
    }

    // set propety of the frame
	camera.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  	char s1[] = "This is first thread!";
    pthread_create(&t, NULL, key_tsk, s1);

    // Video output
	cv::VideoWriter output;
    output.open("/run/media/mmcblk1p1/test.avi", CV_FOURCC('M', 'J', 'P', 'G'), 5.0, cv::Size(640, 480), true);

    while (true) 
    {
        // get video frame from stream
        camera.read(frame);
        // check if we succeeded
        if (frame.empty()) 
        {
            printf("ERROR! Can't get video frame.\n");
            break;
        }

		if (capVideo) 
        {
			sprintf(fileName, "%s%d.png", "/run/media/mmcblk1p1/",cnt);
            bool rslt = cv::imwrite(fileName, frame);
	        printf("save %s %d\n", fileName, rslt);
			cnt++;
			capVideo = false;		
        }

        // get size of the video frame
        frame_size = frame.size();

        // transfer color space from BGR to BGR565 (16-bit image) to fit the requirement of the LCD
	    cv::cvtColor(frame, frameDst, cv::COLOR_BGR2BGR565);
		output << frame;

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
    // the command you would need is "FBIOGET_VSCREENINFO"
    if (ioctl(fd, FBIOGET_VSCREENINFO, &screen_info) != 0) {
        printf("error read screen_info");
    }

    // put the required attributes in variable "fb_info" you found with "ioctl() and return it."
    fb_info.xres_virtual =  screen_info.xres_virtual;     // 8
    fb_info.yres_virtual =  screen_info.yres_virtual;     // 8
	fb_info.bits_per_pixel = screen_info.bits_per_pixel;    // 16
    printf("res %d %d %d\r\n", fb_info.xres_virtual, fb_info.yres_virtual, fb_info.bits_per_pixel );
    return fb_info;
};


int getch(void) 
{ 
    struct termios oldattr, newattr; 
    int ch; 
    tcgetattr(STDIN_FILENO, &oldattr); 
    newattr = oldattr; 
    newattr.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
    ch = getchar(); 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
    return ch; 
}

void* key_tsk(void* data) 
{
    while(1) 
    {
  	    char c;
        printf("wait key\r\n");
        c = getch();
        printf("get key %c\r\n", c);
        if (c == 'c')
            capVideo = true;
        if (c == 'e')
            break;
    }
    pthread_exit(NULL);
}

