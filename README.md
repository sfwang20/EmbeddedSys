## Embedded System practice

### Equipments
A development board. (Embedsky E9V3) (OS: Ubuntu 16.04) &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/0-1.png)

An LCD screen. (TN92_7LCD_V1.02).  &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/0-2.png)

An RS-232 cable.  &emsp;

A power cable.  &emsp;

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

### 2-1. Using image output (framebuffer) in an embedded system
==> Prepare a development environment with OpenCV &emsp;

Prepare cmake-gui. &emsp;

Configure building arguments of opencv with cmake. &emsp;

Build opencv. &emsp;

Program coding: use frambuffer (/dev/fb0 or /dev/fb1) show image on LCD screen. &emsp;

Compile code using opencv. &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/2-1.jpg)
&emsp;

### 2-2. Using video output and input on the embedded system
Show camera stream on the embedded screen. &emsp;

While reading the video input stream, capture and save the video frame to the SD card when pressing “c” (without “enter” ↵).  &emsp;

It should capture and save multiple images after pressing multiples times “c”, saved images should not be overwritten. &emsp;

Bonus:
While reading the video input stream, capture and save the video frame to the SD card when pressing “c” (without “enter” ↵). It should capture and save multiple images after pressing multiples times “c”, saved images should not be overwritten.  &emsp;

After bootup, start to recording the input stream to a video file automatically. The video format is not restricted. &emsp;

![image](https://github.com/sfwang20/EmbeddedSys/blob/master/images/2-2.jpg)
&emsp

### 2-3. Using video output and input on the embedded system (HDMI output)

Show camera stream on the HDMI output (by modifying some bootup arguments). &emsp;

Make your board an electronic scroll board. Your board should automatically start to show some pictures on the HDMI output after bootup. &emsp;

### Term project - embedded application development: face recognition task

1 Take a video input from the video camera which is connected to the board, so the video can be displayed on the monitor(HDMI or LCD is both fine). &emsp;
2 Detect a human face, which can be done by using public domain algorithms. &emsp;
3 Extract features from the detected human face, it can also be done by using public domain algorithms. &emsp;
4 Based on the detected features, try to design an algorithm that can identify an individual, such as yourself. The algorithm has to extract certain features which can be processed for identification purpose. The processed result should be stored as the individual record so that it can be used later to identify that person. &emsp;
