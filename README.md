# ttgo-projects
My favorite esp32 ttgo display projects
# TTGO BOARD FACTS

- To work with the display you will need SPI and TFT_eSPI arduino libraries
- Images, fonts and animation should be converted to bytes using programs like those specified under 'Resources for Developement' (below) and saved as header files `.h` (check Necklace project as reference)
- Keep in mind that each pixel requires 2 bytes of memory = 16 bit color since RGB565
- c array must be const to be read from flash otherwise it is stored in RAM

From Bodmer himself:

    For the ESP32 and ESP8266 there are quite a few ways that an image file can be stored locally, for example:

    - A "C" array, example here with the online image-> c array converter link.
    - SPIFFS, a flash filing system - (recently deprecated in favour of the faster LittleFS)
    - LittleFS, a flash filing system - faster than SPIFFS, now supported in board packages for ESP8266 (LittleFS) and ESP32 (LITTLEFS)
    - SD card

    It is also possible via WiFi to fetch images from the web, but this needs more complex code and is slower.

    The C array in FLASH memory has best performance as there is no filing system overhead.
    SPIFFS and LittleFS are more convenient for multiple images, extra upload tools must be installed in the IDE
    SD cards are good for multiple images but is less convenient and typically slower

## T-Display (1.14 inches) Facts

- pin 0 is left built-in button & pin 35 right built-in button 
- display size in pixel is 135 width and 240 height

## S3 (1.9 inches) Facts
- display size in pixel is 170 width and 320 height

# How to upload GIF to ttgo display (Tutorial: Fastest & Easiest)
I highly recomend watching VolosProjects' [Programming Tutorials series](https://www.youtube.com/watch?v=WFVjsxFMbSM&t=6s&ab_channel=VolosProjects). However, for just uploading GIFs the easiest method is [ShotokuTech's tutorial](https://www.youtube.com/watch?v=dPathl6HrCY&ab_channel=ShotokuTech). (If you are a total beginner and have not set up your machine please go to Setup Section below first then return to this section)

- Choose a gif and edit it to the right size, time length, and speed of choice at [EZGIF](https://ezgif.com/) (or equivalent GIF Editor)
- Convert GIF to C array using [bitbank2 C Converter from terminal](https://github.com/bitbank2/image_to_c) (it will be saved as `.h` file, e.g., `myGIF.h`)
- Install `<AnimatedGIF.h>` library
- Open example code from `File/Examples/AnimatedGIF/TFT_eSPI_memory` and grab `GIFDraw.ino` helper function for your projects.
- Create project: say `myMainProject.ino` accompanied by `GIFDraw.ino` and `myGIF.h` at the same level directory.
- Include in `myMainProject.ino` the following code:

```
#include <AnimatedGIF.h>
#include <SPI.h>
#include <TFT_eSPI.h>

//USER CUSTOM PARAMETERS
#include "myGIF.h" // edited at EZGIF and converted to C array                                 
#define GIF_IMAGE   myGIF //the name of array inside myGIF.h               

//Code object variables
AnimatedGIF gif;
TFT_eSPI tft = TFT_eSPI();

void setup() 
{
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  gif.begin(BIG_ENDIAN_PIXELS);
}

void loop()
{ 
  if (gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw))
  {
    tft.startWrite(); // The TFT chip slect is locked low
    while (gif.playFrame(true, NULL))
    {
      yield();
    }
    gif.close();
    tft.endWrite(); // Release TFT chip select for other SPI devices
  }
}
```

# Setup
[![Intro Tutorial](https://img.youtube.com/vi/b8254--ibmM/0.jpg)](https://youtu.be/b8254--ibmM?t=150 "Click to watch in YouTube")

Summary from video:

- Install Arduino
- Enable/Set ESP32 Board url reference address: `https://dl.espressif.com/dl/package_esp32_index.json` in Preferences
- Import/Install ESP32 boards: `esp32 by Espressif` in Board Manager
- Choose your board: T-Display (`TTGO LoRa32 OLED V1` has equivalent settings)
- Install libraries: `TFT_eSPI by Bodmer`
- Edit `User_Setup_Select.h` from the TFT_eSPI library to enable T-Display setup

# Resources for Developement

- [Online Font C Converter](http://oleddisplay.squix.ch/#/home) ([Tutorial](https://www.youtube.com/watch?v=R-qFKemDFyM&ab_channel=VolosProjects))
- [Online Image C Converter](http://www.rinkydinkelectronics.com/t_imageconverter565.php) ([Tutorial](https://www.youtube.com/watch?v=R-qFKemDFyM&ab_channel=VolosProjects))
- [Gif Editor](https://ezgif.com/) ([Tutorial](https://www.youtube.com/watch?v=-h9Vm0Ow_Is&list=RDCMUCit2rVgOvhyuAD-VH5H_IHg&index=25&ab_channel=VolosProjects))
- [Offline Gif C Converter for Windows by Volos](https://github.com/VolosR/AnimationTFT) ([Tutorial](https://www.youtube.com/watch?v=-h9Vm0Ow_Is&list=RDCMUCit2rVgOvhyuAD-VH5H_IHg&index=25&ab_channel=VolosProjects))
- [Offline Gif C Converter from terminal](https://github.com/bitbank2/image_to_c) ([Tutorial](https://www.youtube.com/watch?v=dPathl6HrCY&ab_channel=ShotokuTech))
- Seems interesting -> https://retro-esp32.github.io/Convert-Image-To-Byte-Array/
