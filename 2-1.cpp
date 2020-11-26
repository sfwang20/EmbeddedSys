#include <fcntl.h> 
#include <fstream>
#include <linux/fb.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/ioctl.h>

struct framebuffer_info
{
    uint32_t bits_per_pixel;    // framebuffer depth
    uint32_t xres_virtual;      // how many pixel in a row in virtual screen
};

struct framebuffer_info get_framebuffer_info(const char *framebuffer_device_path);

int main(int argc, const char *argv[])
{
    cv::Mat image, imageDst;
    cv::Size2f image_size;
    
    framebuffer_info fb_info = get_framebuffer_info("/dev/fb0");
    std::ofstream ofs("/dev/fb0");
    if (!ofs) { 
        printf("can't open ofs\r\n");
        return 1; 
    } 
    // read image file (sample.bmp) from opencv libs.
    image = cv::imread(argv[1]);

    // get image size of the image.
    image_size = image.size();

    // transfer color space from BGR to BGR565 (16-bit image) to fit the requirement of the LCD
    printf("cvtColor %f %f, \r\n", image_size.width, image_size.height);
    cv::cvtColor(image, imageDst, cv::COLOR_BGR2BGR565);
   
	// output to framebufer row by row
    for (int y = 0; y < image_size.height; y++)
    {
        // move to the next written position of output device framebuffer by "std::ostream::seekp()".
		ofs.seekp(y*fb_info.xres_virtual*fb_info.bits_per_pixel/8);
		
        // write to the framebuffer by "std::ostream::write()".
        ofs.write(reinterpret_cast<char*>(imageDst.ptr(y)), image_size.width*2);
    }
    return 0;
}

struct framebuffer_info get_framebuffer_info(const char *framebuffer_device_path)
{
    struct framebuffer_info fb_info;        // Used to return the required attrs.
    struct fb_var_screeninfo screen_info;   // Used to get attributes of the device from OS kernel.

    // open device with linux system call "open()"
	int fd = open(framebuffer_device_path, O_RDWR);
	
    // get attributes of the framebuffer device thorugh linux system call "ioctl()"
    if (ioctl(fd, FBIOGET_VSCREENINFO, &screen_info) != 0)
    {
        printf("error read screen_info");
    }

    // put the required attributes in variable "fb_info" you found with ioctl() and return it
    fb_info.xres_virtual =  screen_info.xres_virtual;     // 8
    fb_info.bits_per_pixel = screen_info.bits_per_pixel;    // 16
    printf("res %d %d\r\n", fb_info.xres_virtual, fb_info.bits_per_pixel);

    return fb_info;
};