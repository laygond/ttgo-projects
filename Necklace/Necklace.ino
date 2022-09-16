// Display multiple GIFs with a press of a button (Carousel style)
// by Laygond (laygond.com)
//
// DESCRIPTION: Carousel method for displaying GIFs. Pressing right or left
// button switches to next or previous GIF. If you press both buttons it shows
// battery level and then goes into deep sleep until either button is pressed
// again.
//  
// NOTE:
// - There are more animations to choose from under `animations_h`
// - The AnimatedGIF class doesn't allocate or free any memory, but the
// instance data occupies about 22.5K of RAM. 


#include <AnimatedGIF.h>
#include <SPI.h>
#include <TFT_eSPI.h>

//Board Pins
#define RIGHT_BUTTON_PIN 35
#define LEFT_BUTTON_PIN 0

//USER CUSTOM PARAMETERS
#include "animations_h/bolt.h"                                 
#include "animations_h/asta.h"
#include "animations_h/eye.h"
#include "animations_h/tunnel.h"
#include "animations_h/sun.h"

#define GIF_IMAGE_0   bolt                             
#define GIF_IMAGE_1   asta                            
#define GIF_IMAGE_2   eye         
#define GIF_IMAGE_3   tunnel     
#define GIF_IMAGE_4   sun                        
int total_gif = 5;

//Code variables
int button_option = 0; //changes when button is pressed
int debounce_left = 0;
int debounce_right= 0;
AnimatedGIF gif;
TFT_eSPI tft = TFT_eSPI();

//Forward declarations
void updateButtonOption();
void showGIF(const uint8_t[]);


void setup() 
{
  //Serial.begin(115200);
  pinMode(RIGHT_BUTTON_PIN,INPUT_PULLUP); 
  pinMode(LEFT_BUTTON_PIN,INPUT_PULLUP);  
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  gif.begin(BIG_ENDIAN_PIXELS);
}

void loop()
{ 
  //Check Button is pressed
  updateButtonOption();

  //Choose Media based on button option
  if (button_option == 0){
    if (gif.open((uint8_t *)GIF_IMAGE_0, sizeof(GIF_IMAGE_0), GIFDraw))
    {
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  }//end option
  if (button_option == 1)
  {
    if (gif.open((uint8_t *)GIF_IMAGE_1, sizeof(GIF_IMAGE_1), GIFDraw))
    {
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  }//end option
  if (button_option == 2)
  {
    if (gif.open((uint8_t *)GIF_IMAGE_2, sizeof(GIF_IMAGE_2), GIFDraw))
    {
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  }//end option
  if (button_option == 3)
  {
    if (gif.open((uint8_t *)GIF_IMAGE_3, sizeof(GIF_IMAGE_3), GIFDraw))
    {
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  }//end option
  if (button_option == 4)
  {
    if (gif.open((uint8_t *)GIF_IMAGE_4, sizeof(GIF_IMAGE_4), GIFDraw))
    {
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  }//end option
}//end loop


 /**
 * Increases or decreases button_option by pressing left or right board buttons 
 */
void updateButtonOption()
{
  if(digitalRead(RIGHT_BUTTON_PIN)==0 )
  {
    if(debounce_right==0)
    {
        debounce_right=1;
        tft.fillScreen(TFT_BLACK);
        button_option++;
        if (button_option >= total_gif){
            button_option = 0;
        }
    }
  }
  else debounce_right=0;

  if(digitalRead(LEFT_BUTTON_PIN)==0 )
  {
    if(debounce_left==0){
        debounce_left=1;
        tft.fillScreen(TFT_BLACK);
        button_option--;
        if (button_option < 0){
            button_option = total_gif -1;
        }
    }
  }
  else debounce_left=0;
   
}

 /**
 * Helper Function to show gifs in one command (UNDER CONSTRUCTION) 
 */
//void showGIF(const uint8_t [] gify)
//{
//  if (gif.open((uint8_t *) gify, sizeof(gify), GIFDraw))
//  {
//    //tft.fillScreen(TFT_GREEN);
//    tft.startWrite(); // The TFT chip slect is locked low
//    while (gif.playFrame(true, NULL))
//    {
//      yield();
//    }
//    gif.close();
//    tft.endWrite(); // Release TFT chip select for other SPI devices
//  }
//}

// === PERSONAL NOTES IGNORE ====
//// Check size of 2D array 
//  Serial.println("Array: walk");
//  Serial.println(sizeof(walk)/sizeof(walk[0]));
//  Serial.println(sizeof(walk[0])/sizeof(walk[0][0]));

//// Volos Method of Uploading GIFs (frame by frame style)
//for(int i=0;i<frames;i++){
//  delay(40);
//  tft.pushImage(60, 15, animation_width, animation_height, walk[i]);}
//}