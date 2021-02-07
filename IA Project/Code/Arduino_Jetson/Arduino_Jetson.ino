#include <Adafruit_NeoPixel.h>

int Brightness = 20;
#define LED_COUNT 10 
#define LED_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void SetColor(int from, int to, int r, int g , int b)
{
  for (int i = from; i < to; i++)
  {
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();

}

String completeMessage;
bool inMessage;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial1.begin(115200); // opens serial port, sets data rate to 9600 bps
  
  strip.begin();
  strip.setBrightness(Brightness);
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'

  //Initialize LEDS
  SetColor(0, LED_COUNT, 255, 255, 255);  
}

// the loop function runs over and over again forever
void loop() {

   while(Serial1.available()) {

    char inchar = (char)Serial1.read();
    if(inchar == '(')
    {
      inMessage = true;
    }
    if(inchar == ')')
    {
      inMessage = false;

      ManageMessage(completeMessage);
      
      completeMessage = "";
    }

    if(inMessage && inchar != '(' && inchar != ')')
    {
      completeMessage += inchar;
    }

  }
  
}

void ManageMessage(String message)
{
   if(message == "PL")
   {
      SetColor(0, 2, 0, 0, 0);
      SetColor(2, 6, 0, 255, 0);
      SetColor(6, 8, 0, 0, 255);
   }
   else if(message == "PR")
   {
      SetColor(0, 2, 0, 0, 255);
      SetColor(2, 6, 0, 255, 0);
      SetColor(6, 8, 0, 0, 0);
   }
   else if(message == "PC")
   {
      SetColor(0, 2, 0, 0, 0);
      SetColor(2, 6, 0, 255, 0);
      SetColor(6, 8, 0, 0, 0);
   }
   else if(message == "NP")
   {
      SetColor(0, 2, 0, 0, 0);
      SetColor(2, 6, 255, 0, 0);
      SetColor(6, 8, 0, 0, 0);
   }  
   else if(message == "OFF")
   {
      SetColor(0, LED_COUNT, 0, 0, 0);
   } 
}
