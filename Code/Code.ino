/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/

static unsigned long offset =  0; //3590ul + 3600ul * 23ul;

// Writable by TimeToCharBuf().  Readonly to all others.
#define bufLen 12


static char _timeBuffer[bufLen];
static unsigned long _lastSeconds = 0;
static unsigned long _uptimeSeconds = 0;
 

void setup() {
  // Init Serial Monitor.
  Serial.begin(9600);

  // Turn onboard LED off.
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer
  display.clearDisplay();
  display.setTextColor(WHITE);        // WHITE, BLACK, or INVERSE
  display.display();
}

void loop() {
  //Screen1();
  Screen2();
}

void Screen2()
{
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println(F("Text Size 1"));

  display.setTextSize(2);
  display.println(F("12.345.678"));

  display.setTextSize(3);
  display.println(F("Size 3"));

  display.setTextSize(1);
  display.println(F("Size 1 again"));

  display.setTextSize(1);
  display.println(F("Size 1 again and again"));

  display.display();
}

void Screen1()
{
  display.setTextSize(2);

  display.setCursor(0,12);
  display.setTextColor(WHITE, BLACK);
  TimeToCharBuf(_timeBuffer);
  display.println(_timeBuffer);

  display.setCursor(0,40);
  display.setTextSize(3);
  display.println(F("F"));
  display.setCursor(18,55);
  display.setTextSize(1);
  display.println(F("loating"));
  
  display.display();
}

//
// Time is maintained in static variable "_uptimeSeconds" with span up to 136 years.
//  New value is calculated and written to string buffer "_timeBuffer" with 10 printable chars.
//  
void TimeToCharBuf(char * buf)
{  
  unsigned long t = millis() / 1000;
  if (t != _lastSeconds)
  {
    _uptimeSeconds++;
    _lastSeconds = t;
  }

  // Isolate uptime variable from alteration.
  t = _uptimeSeconds + offset;

  // Calculate sec, min, hrs, days.
  int s = t - ((t / (unsigned long)60 ) * (unsigned long)60);
  t = (t - (unsigned long)s) / (unsigned long)60;
  int m = t - ((t / (unsigned long)60 ) * (unsigned long)60);
  t = (t - (unsigned long)m) / (unsigned long)60;
  int h = t - ((t / (unsigned long)24 ) * (unsigned long)24);
  int days = (t - (unsigned long)h) / (unsigned long)24;

  // Display based on if have been alive for at least one day or less.
  if (days > 0)
  {
    // "DDDd HH:MM"
    snprintf(_timeBuffer, bufLen - 1, "%3dd %2d:%02d", (int)days, (int)h, (int)m);
  }
  else
  {  
    // "  HH:MM:SS"
    snprintf(_timeBuffer, bufLen - 1, "  %2d:%02d:%02d", (int)h, (int)m, (int)s);
  }
}
