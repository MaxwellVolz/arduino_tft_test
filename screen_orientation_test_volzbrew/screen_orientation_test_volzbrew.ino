// UTFT_Textrotation_Demo (C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the textrotation-functions.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <UTouch.h>

// Data wire is plugged into port 10 on the Arduino
#define ONE_WIRE_BUS 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Uncomment the next line for Arduino 2009/Uno
//UTFT myGLCD(ITDB32S,19,18,17,16);   // Remember to change the model parameter to suit your display module!

// Uncomment the next line for Arduino Mega
//UTFT myGLCD(ITDB32S,38,39,40,41);   // Remember to change the model parameter to suit your display module!
UTFT myGLCD(ILI9341_16,38,39,40,41);


//INIT touchscreen
UTouch  myTouch( 6, 5, 4, 3, 2);


float tempf;
int x = 0;
int y = 0;
int count = 0;

void drawOutline()
{
      myGLCD.print("VOLZBREW", 0, 0);
    myGLCD.setColor(0, 0, 255);
    myGLCD.print("Temperature", 0, 16, 0);
    myGLCD.setColor(0, 255, 0);
    myGLCD.print("VolzBrew", 319, 0, 90);
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("VolzBrew", 319, 239, 180);
    myGLCD.setColor(255, 255, 0);
    myGLCD.print("Volzbrew", 0, 239, 270);

 //   myGLCD.setFont(SevenSegNumFont);
 //   myGLCD.setColor(0, 255, 0);
//    myGLCD.print("72", 90, 100, 45);
    myGLCD.setColor(0, 255, 255);
 //   myGLCD.print("72", 150, 50, 0);
}

void checkTemp()
{
   sensors.requestTemperatures(); // Send the command to get temperatures
   tempf = (sensors.getTempCByIndex(0)*1.8+32);
   myGLCD.printNumF(tempf, 2, 150, 50);
}

void setup()
{
//SETUP POWER AND GND FOR TEMP ON PINS 9-11
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(11, HIGH);

  //SCREEN INIT
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

  //BUTTONS INIT
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  // Start up the temp library
  sensors.begin();
  drawOutline();
}

void loop()
{
      if (myTouch.dataAvailable())
    {
   //   myTouch.read();
   //  x=myTouch.getX();
   //  y=myTouch.getY();
    myGLCD.setColor(255, 127, 0);
    myGLCD.print("Touch", 140, 120, 0);
      
      
      while(myTouch.dataAvailable());
  //      myTouch.read();
        myGLCD.print("     ", 140, 120, 0);
    }
     if (count == 10000)
     {
      checkTemp();
      count = 0;
     }
     else {
      count ++;
     }
//      delay(1000);
}

