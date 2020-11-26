## Embedded System practice

### Equipments
A development board. (Embedsky E9V3)
(OS: Ubuntu 16.04)
An RS-232 cable.
A power cable
An LCD screen. (TN92_7LCD_V1.02).
An RS-232 – USB cable. (Uptech UTN401A)
A miniUSB – USB cable*.
An Ethernet cable*.


### Task 1  'Hello World' in an embedded system
Prepare a host computer installed with Ubuntu 14.04
Install cross compiler in the host computer prepared above.
Install OS on the development board
Compile program
Use the RS-232 interface to transfer files from/to your embedded system

### Task 2-1 Using image output in an embedded system.
Prepare cmake gui
Configure building arguments of opencv with cmake.
Build opencv
Compile code using opencv
*framebuffer

### Task 2-2 Using video output and input on the embedded system.
Show camera stream on the embedded screen.
While reading the video input stream, capture and save the video frame to the SD card when pressing “c” (without “enter” ↵). It should capture and save multiple images after pressing multiples times “c”, saved images should not be overwritten. The image format is not restricted.
5.2 After bootup, start to recording the input stream to a video file automatically. The video format is not restricted.

### Task 2-3 Using video output and input on the embedded system.
Show camera stream on the HDMI output.
Make your board an electronic scroll board. Your board should automatically start to show some pictures on the HDMI output after bootup.
