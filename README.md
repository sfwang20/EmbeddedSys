## Embedded System practice

### Equipments
A development board. (Embedsky E9V3) (OS: Ubuntu 16.04) &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/0-1.png)

An RS-232 cable.  &emsp;

A power cable.  &emsp;

An LCD screen. (TN92_7LCD_V1.02).  &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/0-2.png)

An RS-232 – USB cable. (Uptech UTN401A).  &emsp;

A miniUSB – USB cable*.  &emsp;

An Ethernet cable*.  &emsp;
&emsp;

### 1. 'Hello World' in an embedded system
Prepare a host computer installed with Ubuntu 14.04. &emsp;

Install cross compiler in the host computer prepared above. &emsp;

Install OS on the development board. &emsp;

Compile program. &emsp;

Use the RS-232 interface to transfer files from/to your embedded system. &emsp;

==>We used minicom in host computer to finish it. &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/1.jpg)
&emsp;

### 2-1. Using image output (framebuffer) in an embedded system.
Prepare cmake gui. &emsp;

Configure building arguments of opencv with cmake. &emsp;

Build opencv. &emsp;

Compile code using opencv. &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/2-1.png)
&emsp;

### 2-2. Using video output and input on the embedded system.
Show camera stream on the embedded screen. &emsp;

While reading the video input stream, capture and save the video frame to the SD card when pressing “c” (without “enter” ↵).  &emsp;

It should capture and save multiple images after pressing multiples times “c”, saved images should not be overwritten. &emsp;

5.2 After bootup, start to recording the input stream to a video file automatically. The video format is not restricted. &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/2-2.png)
&emsp

### 2-3. Using video output and input on the embedded system.
Show camera stream on the HDMI output. &emsp;

Make your board an electronic scroll board. Your board should automatically start to show some pictures on the HDMI output after bootup. &emsp;

