#include <RCSwitch.h>
#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<4> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 2
rgb_color colors[LED_COUNT];

RCSwitch mySwitch = RCSwitch();

unsigned long time=0L;
unsigned long nextblink=0L;
unsigned long nextbeep=0L;


int numberofblinks=0;
int blinkinterval=300;
int blinkstate=0;
rgb_color blinkcolor;
rgb_color black;

int numberofbeeps=0;
int beepinterval=300;
int beepstate=0;

boolean isAfter( unsigned long timer )
{
  if(timer<=time && !(time>3000000000L && timer<1000000000L) ) return(true);
  if(timer>3000000000L && time<1000000000L) return(true);
  return(false);
}

void blinking()
{
  if( numberofblinks>0 && isAfter(nextblink) )
  {
    numberofblinks--;
    nextblink=millis()+blinkinterval;
    blinkstate=1-blinkstate;
    if( blinkstate==0 ) setColor(black);
      else setColor(blinkcolor);
    if( numberofblinks==0 ) setColor(black);
  }
}

void beeping()
{
  if( numberofbeeps>0 && isAfter(nextbeep) )
  {
    numberofbeeps--;
    nextbeep=millis()+beepinterval;
    beepstate=1-beepstate;
    if( beepstate==0 ) digitalWrite(3, LOW);
      else digitalWrite(3, HIGH);;
    if( numberofbeeps==0 ) digitalWrite(3, LOW);
  }
}

void setColor(rgb_color color)
{
   for(uint16_t i = 0; i < LED_COUNT; i++)
   {
     colors[i] = color;
   }
      
   ledStrip.write(colors, LED_COUNT);
}

void setup() {
  mySwitch.enableReceive(0);  // interrupt 0 - pin 2

  black=rgb_color(0,0,0);

  pinMode(3, OUTPUT);
  digitalWrite(3,LOW);
}

void loop() {
  time=millis();
  blinking();
  beeping();
  rgb_color color;

  //przyszły jakieś dane radiowo
  if (mySwitch.available()) {
    
    unsigned long value = mySwitch.getReceivedValue();
    int len=mySwitch.getReceivedBitlength();
    int protocol=mySwitch.getReceivedProtocol();
    
    if (value == 0) {
      //nieznane kodowanie/błędny odczyt;
    } else {  

      if( len==24 && protocol==2 && value==2220L )
      {
        numberofbeeps=0;
        numberofblinks=0;
        setColor(black);
        digitalWrite(3, LOW);
      }

      if( len==24 && protocol==2 && value==2221L )
      {
        blinkcolor=rgb_color(255,0,0);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }

      if( len==24 && protocol==2 && value==2222L )
      {
        blinkcolor=rgb_color(0,0,255);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }      

      if( len==24 && protocol==2 && value==2223L )
      {
        blinkcolor=rgb_color(0,255,0);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }     

      if( len==24 && protocol==2 && value==2224L )
      {
        blinkcolor=rgb_color(255,0,255);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }     


      if( len==24 && protocol==2 && value==2225L )
      {
        blinkcolor=rgb_color(0,255,255);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }     


      if( len==24 && protocol==2 && value==2226L )
      {
        blinkcolor=rgb_color(255,255,0);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }     


      if( len==24 && protocol==2 && value==2227L )
      {
        blinkcolor=rgb_color(255,255,255);
        numberofbeeps=15;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }     

      if( len==24 && protocol==2 && value==2228L )
      {
        blinkcolor=rgb_color(255,255,255);
        numberofbeeps=0;
        numberofblinks=90;
        nextblink=millis();
        nextbeep=millis();      
      }   

      if( len==24 && protocol==2 && value==2229L )
      {
        blinkcolor=rgb_color(0,255,0);
        numberofbeeps=0;
        numberofblinks=10;
        nextblink=millis();
        nextbeep=millis();      
      }         
      
    }
    mySwitch.resetAvailable();
  }

}
