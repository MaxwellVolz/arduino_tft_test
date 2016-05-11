#include <UTFT_Buttons.h>

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
#include <UTFT_Geometry.h>


// Data wire is plugged into port 10 on the Arduino
#define ONE_WIRE_BUS 10

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Dingbats1_XL[];

// Uncomment the next line for Arduino 2009/Uno
//UTFT myGLCD(ITDB32S,19,18,17,16);   // Remember to change the model parameter to suit your display module!

// Uncomment the next line for Arduino Mega
//UTFT myGLCD(ITDB32S,38,39,40,41);   // Remember to change the model parameter to suit your display module!
UTFT myGLCD(ILI9341_16,38,39,40,41);


// geometry library var
UTFT_Geometry geo(&myGLCD);

//INIT touchscreen
UTouch  myTouch( 6, 5, 4, 3, 2);

UTFT_Buttons myButtons(&myGLCD, &myTouch);


float tempf;
int x = 0;
int y = 0;
int count = 0;
int counter1 = 0;
int counter2 = 0;


void drawOutline()
{
    myGLCD.print("test", 0, 0);
    myGLCD.setColor(0, 0, 255);
    myGLCD.print("Dope", 0, 16, 0);
    myGLCD.setColor(0, 255, 0);
    
    myGLCD.print("Dope", 0, 32, 0);
    myGLCD.setColor(0, 255, 0);

    myGLCD.print("Shit", 319, 0, 90);
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("yeeeeeee", 319, 239, 180);
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
  
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);

  // Start up the temp library
  sensors.begin();
  //drawOutline();
}

void loop()
{
  // Button Positioning Guide
  //
  // addButton( x, y, width, height, text)
  //
  // screenWidth: 420
  // screenHeight: 340
  // comfortable click height: 50
  // comfortable click width: 50  
  
  
  int but1, but2, but3, but4, but5, butX, butY, pressed_button;
  boolean default_colors = true;
  int butCounter1, butPlus1, butMinus1;
  int butCounter2, butPlus2, butMinus2;
  	
   
  //but1 = myButtons.addButton( 10,  10, 145,  50, "Button 1");
  //but2 = myButtons.addButton( 165,  10, 145,  50, "Button 2");
  //but3 = myButtons.addButton( 10,  70, 300,  50, "Button 3");
  //but4 = myButtons.addButton( 10,  130, 300,  50, "Button 4");
  butX = myButtons.addButton( 10, 180, 80, 50, "a");

  // untest section ------------------------------------------------  
  // incrementer with buttons
  counter1= 0;
  butCounter1 = myButtons.addButton( 200, 10, 50, 50, "0");
  butPlus1 = myButtons.addButton( 260, 10, 50, 50, "+"); 
  butMinus1 = myButtons.addButton( 140, 10, 50, 50, "-"); 

  //counter2=0;
  

  //butCounter2 = myButtons.addButton( 160, 60, 50, 50, "#");
  
  //butCounter2 = myButtons.addButton( 160, 120, 50, 50, "0");
  //butPlus2 = myButtons.addButton( 10, 120, 80, 50, "+"); 
  //butMinus2 = myButtons.addButton( 80, 120, 80, 50, "-"); 
  
  // untest section ------------------------------------------------
  

  // volzbrew logo geometry
  //geo.drawArc(20,20,60,-40,40,3);
  
  // drawArc( x,y,r,startAngle,endAngle,thickness(o))
  //geo.drawArc(30,30,30,180,0,3);
  
  // draw circle
  // myGLCD.drawCircle(x, y, r);
  int x,r,y;
    x=18; // posX
    y=7; // posY
    r=4;
    myGLCD.drawCircle( x-1, y, r);
    myGLCD.drawCircle( x+13, y, r);
    // drawLine(x1,y1,x2,y2)
    
    //arms
    myGLCD.drawLine( x-8, y+6, x+21, y+6);
    
    // legs
    // left legs
    myGLCD.drawLine( x-5, y+14, x+3, y+6);
    myGLCD.drawLine( x-5, y+6, x+3, y+14);
    
    // right legs
    myGLCD.drawLine( x+9, y+6, x+17, y+14);
    myGLCD.drawLine( x+9, y+14, x+17, y+6);
    
    // left beer
    myGLCD.fillRect( x-14,y+4,x-10,y+8);
    myGLCD.drawCircle( x-12, y+3, r-2);
    
    // right beer
    myGLCD.fillRect( x+23,y+4,x+27,y+8);
    myGLCD.drawCircle( x+25, y+3, r-2);
    
    // left face
    myGLCD.drawLine( x-3, y-1, x-2, y-1);
    myGLCD.drawLine( x, y-1, x+1, y-1);
    //myGLCD.drawLine(x-3, y+1, x+1, y+1);
    geo.fillTriangle( x-3,y+1,x+1,y+1,x-1,y+3);
    
    // right face
    myGLCD.drawLine( x+11, y-1, x+12, y-1);
    myGLCD.drawLine( x+14, y-1, x+15, y-1);
    //myGLCD.drawLine(x+13, y+1, x+17, y+1);
    geo.fillTriangle( x+11,y+1,x+15,y+1,x+13,y+3);
  
  myButtons.drawButtons();
  
 while(1) 
  {
    if (myTouch.dataAvailable() == true)
    {
      pressed_button = myButtons.checkButtons();

      if (pressed_button==but1)
        myGLCD.print("Button 1", 110, 220);
      if (pressed_button==but2)
        myGLCD.print("Button 2", 110, 220);
      if (pressed_button==but3)
        myGLCD.print("Button 3", 110, 220);
      if (pressed_button==but4)
        myGLCD.print("Button 4", 110, 220);
      if (pressed_button==-1)
        myGLCD.print("None    ", 110, 220);
      if(pressed_button==butPlus1){
        ++counter1;
        char str[15];
        sprintf(str,"%d",counter1);
        //myGLCD.print("lame", 110, 220);
        myButtons.relabelButton(butCounter1, str);
        myButtons.drawButtons();
      }
      if(pressed_button==butMinus1){
        --counter1;
        char str[15];
        sprintf(str,"%d",counter1);
        //myGLCD.print("lame", 110, 220);
        myButtons.relabelButton(butCounter1, str);
        myButtons.drawButtons();
      }
      if(pressed_button==butPlus2){
        ++counter2;
        char str[15];
        sprintf(str,"%d",counter2);
        //myGLCD.print("addition   ", 110, 220);
        myButtons.relabelButton(butCounter2, str);
        myButtons.drawButtons();
      }
      if(pressed_button==butMinus2){
        --counter2;
        char str[15];
        sprintf(str,"%d",counter2);
        //myGLCD.print("subtraction    ", 110, 220);
        myButtons.relabelButton(butCounter2, str);
        myButtons.drawButtons();
      }

    }
  }
}

