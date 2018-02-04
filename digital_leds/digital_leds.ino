#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    5
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    60
#define NUM_CLUSTER 6
// Protoboard

byte led1 = 11;           // the PWM pin the LED is attached to
byte led2 = 6;
byte led3 = 13;

int brightness = 0;    // how bright the LED is
byte brightness2 = 0;

byte fadeAmount = 5;    // how many points to fade the LED by
int valPot = 0;
byte potPin = 0; // analog input
byte ctsPin = 2;
int soundSensor = 1; // analog input
byte auxPos = 1;

// Digital Leds

byte lights [] =  {             0,   0,   0,   0,   0,   1,   1,   2,
                                              2,   3,   4,   5,   6,   7,   8,   9,
                                             11,  12,  13,  15,  17,  18,  20,  22,
                                             24,  26,  28,  30,  32,  35,  37,  39,
                                             42,  44,  47,  49,  52,  55,  58,  60,
                                             63,  66,  69,  72,  75,  78,  81,  85,
                                             88,  91,  94,  97, 101, 104, 107, 111,
                                            114, 117, 121, 124, 127, 131, 134, 137,
                                            141, 144, 147, 150, 154, 157, 160, 163,
                                            167, 170, 173, 176, 179, 182, 185, 188,
                                            191, 194, 197, 200, 202, 205, 208, 210,
                                            213, 215, 217, 220, 222, 224, 226, 229,
                                            231, 232, 234, 236, 238, 239, 241, 242,
                                            244, 245, 246, 248, 249, 250, 251, 251,
                                            252, 253, 253, 254, 254, 255, 255, 255,
                                            255, 255, 255, 255, 254, 254, 253, 253,
                                            252, 251, 251, 250, 249, 248, 246, 245,
                                            244, 242, 241, 239, 238, 236, 234, 232,
                                            231, 229, 226, 224, 222, 220, 217, 215,
                                            213, 210, 208, 205, 202, 200, 197, 194,
                                            191, 188, 185, 182, 179, 176, 173, 170,
                                            167, 163, 160, 157, 154, 150, 147, 144,
                                            141, 137, 134, 131, 127, 124, 121, 117,
                                            114, 111, 107, 104, 101,  97,  94,  91,
                                             88,  85,  81,  78,  75,  72,  69,  66,
                                             63,  60,  58,  55,  52,  49,  47,  44,
                                             42,  39,  37,  35,  32,  30,  28,  26,
                                             24,  22,  20,  18,  17,  15,  13,  12,
                                             11,   9,   8,   7,   6,   5,   4,   3,
                                              2,   2,   1,   1,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0,
                                              0,   0,   0,   0,   0,   0,   0,   0};

        byte HSVlights[] = {     0,   4,   8,  13,  17,  21,  25,  30,  34,  38,  42,  47,  51,  55,  59,  64,
                                             68,  72,  76,  81,  85,  89,  93,  98, 102, 106, 110, 115, 119, 123, 127, 132,
                                            136, 140, 144, 149, 153, 157, 161, 166, 170, 174, 178, 183, 187, 191, 195, 200,
                                            204, 208, 212, 217, 221, 225, 229, 234, 238, 242, 246, 251, 255 };

        byte HSVpower[] =  {     0,   2,   4,   6,   8,  11,  13,  15,  17,  19,  21,  23,  25,  28,  30,
                                             32,  34,  36,  38,  40,  42,  45,  47,  49,  51,  53,  55,  57,  59,  62,
                                             64,  66,  68,  70,  72,  74,  76,  79,  81,  83,  85,  87,  89,  91,  93,
                                             96,  98, 100, 102, 104, 106, 108, 110, 113, 115, 117, 119, 121, 123, 125,
                                            127, 130, 132, 134, 136, 138, 140, 142, 144, 147, 149, 151, 153, 155, 157,
                                            159, 161, 164, 166, 168, 170, 172, 174, 176, 178, 181, 183, 185, 187, 189,
                                            191, 193, 195, 198, 200, 202, 204, 206, 208, 210, 212, 215, 217, 219, 221,
                                            223, 225, 227, 229, 232, 234, 236, 238, 240, 242, 244, 246, 249, 251, 253,
                                            255 };

        byte Breath[] =  {  255, 252, 249, 247, 244, 242, 239, 237, 234, 232, 229, 226, 224, 221, 219, 216,
                                         214, 211, 209, 206, 204, 201, 198, 196, 193, 191, 188, 186, 183, 181, 178, 175,
                                         173, 170, 168, 165, 163, 160, 158, 155, 153, 150, 147, 145, 142, 140, 137, 135,
                                         132, 130, 127, 124, 122, 119, 117, 114, 112, 109, 107, 104, 102,  99,  96,  94,
                                          91,  89,  86,  84,  81,  79,  76,  73,  71,  68,  66,  63,  61,  58,  56,  53,
                                          51,  48,  45,  43,  40,  38,  35,  33,  30,  28,  25,  22,  20,  17,  15,  12,
                                          10,   7,   5,   2,   0 };
                                          

CRGB leds[NUM_LEDS];
int snake_control = 3;
int aux_control = 1;
int clusters[NUM_CLUSTER];

CRGB color_cluster[NUM_CLUSTER];
CRGB cores[NUM_LEDS];
CRGB cor_atual;
int aux_cor = 1;
int cor_controle;
int red = 255;
int green = 0;
int blue = 0;

int interval = 1;
int aux_interval = 10;

bool pattern_status = false;
bool mode1 = false;
bool mode2 = false;
bool mode3 = false;
bool mode4 = false;
#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  60


void rainbow();
void Custom();
void lollypop();
void snake();
void individual();
void nextPattern();
void RealHSVRainbow_analog();
void PowerHSVRainbow_analog();
void SineWaveRainbow_analog();

//oldanalog
byte redValue = 0;
byte greenValue = 0;
byte blueValue = 0;

int angle = 0;


void setup() {
  for(int k = 0; k < NUM_LEDS; k++){
    cores[k] = CRGB (255 - k, k, 0);
  }
  for(int k = 0; k < NUM_CLUSTER; k++){
    clusters[k] = NUM_LEDS/NUM_CLUSTER * k;
  }
  
  //delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ctsPin, INPUT);
  pinMode(soundSensor, INPUT);
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, snake, individual, lollypop, Custom, RealHSVRainbow_analog, PowerHSVRainbow_analog, SineWaveRainbow_analog };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop()
{ 
  gPatterns[gCurrentPatternNumber]();
  
  analogWrite(led2, brightness); // Aciona o LED proporcionalmente ao valor da leitura analógica
  
  int soundData = analogRead(soundSensor);
  soundData = map(soundData, 0, 1023, 0, 255);
  if(soundData >= 160 && soundData <= 255){
    analogWrite(led1, soundData);
   // FastLED.setBrightness(soundData);
  } else{
    analogWrite(led1, LOW); 
   // FastLED.setBrightness(LOW); 
  }
  // set the brightness of pin 9:
  //analogWrite(led1, brightness);


  
  // WORKING PROPERLY ------------------
  int ctsValue = digitalRead(ctsPin);
  if (ctsValue == HIGH){
    digitalWrite(led3, HIGH);
    if(pattern_status == false){
      
      for(int k = 0; k < NUM_LEDS; k++){
        cores[k] = CRGB (255 - k, k, 0);
      }
      aux_cor = 1;
      cor_controle = 0;
      red = 255;
      green = 0;
      blue = 0;
      interval = 1;
      aux_interval = 10;
      snake_control = 3;
      aux_control = 1;
      mode1 = false;
      mode2 = false;
      mode3 = false;
      mode4 = false;
      //oldanalog
      redValue = 0;
      greenValue = 0;
      blueValue = 0;
      angle = 0;
    //  FastLED.setBrightness(soundData);
      
      nextPattern();
      
    }
      pattern_status = true;
  }
  else{
    pattern_status = false;
    digitalWrite(led3, LOW);
  }
  // ------------------------------------ 

  
  valPot =  analogRead(potPin); //Faz a leitura analógica do pino em que o potenciômetro esta ligado 
  brightness  = map(valPot, 0, 1023, 0, 255);
  FastLED.setBrightness(brightness);
  
  // send the 'leds' array out to the actual LED strip
    
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 
  //leds[0] = CRGB(255,0,0);
  
  //snake(false);
  //rainbow(false);
  //lollypop(false);
  //Custom(5, false);
  //individual();

  angle = (angle + 1) % 360;

}


#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void RealHSVRainbow_analog(){
  if (angle < 60)
            {
                redValue = 255;
                greenValue = HSVlights[angle];
                blueValue = 0;
            }
            else if (angle < 120)
            {
                redValue = HSVlights[120 - angle];
                greenValue = 255;
                blueValue = 0;
            }
            else if (angle < 180)
            {
                redValue = 0;
                greenValue = 255;
                blueValue = HSVlights[angle - 120];
            }
            else if (angle < 240)
            {
                redValue = 0;
                greenValue = HSVlights[240 - angle];
                blueValue = 255;
            }
            else if (angle < 300)
            {
                redValue = HSVlights[angle - 240];
                greenValue = 0;
                blueValue = 255;
            }
            else
            {
                redValue = 255;
                greenValue = 0;
                blueValue = HSVlights[360 - angle];
            }
      
      for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(redValue, greenValue, blueValue);
      }
      
      FastLED.show();
}

void PowerHSVRainbow_analog()
{ 
            if (angle < 120)
            {
                redValue = HSVpower[120 - angle];
                greenValue = HSVpower[angle];
                blueValue = 0;
            }
            else if (angle < 240)
            {
                redValue = 0;
                greenValue = HSVpower[240 - angle];
                blueValue = HSVpower[angle - 120];
            }
            else
            {
                redValue = HSVpower[angle - 240];
                greenValue = 0;
                blueValue = HSVpower[360 - angle];
            }
            
    for (int i = 0; i < NUM_LEDS; i++){
       leds[i] = CRGB(redValue, greenValue, blueValue);     
    }
    FastLED.show();
}

 void SineWaveRainbow_analog()
 {
            redValue = lights[(angle + 120) % 360];
            greenValue = lights[angle];
            blueValue = lights[(angle + 240) % 360];

      for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(redValue, greenValue, blueValue);
      }
      FastLED.show();
}


void changingLedsByCluster(int ind_led){
  int x = 1;
  switch (cor_controle%3){
    case 0: red = red - x;
            green = green + x;
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - x;
            blue = blue + x;
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - x;
            red = red + x;
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cores[ind_led] = CRGB(red, green, blue);
  leds[ind_led] = cores[ind_led];
}


void snake(){
  snake_control = aux_control + snake_control;
  if(snake_control >= 59 or snake_control <= 0)
  {
      aux_control = -aux_control;
  }
  switch (cor_controle%3){
    case 0: red = red - (255/NUM_LEDS);
            green = green + (255/NUM_LEDS);
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - (255/NUM_LEDS);
            blue = blue + (255/NUM_LEDS);
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - (255/NUM_LEDS);
            red = red + (255/NUM_LEDS);
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cor_atual = CRGB(red, green, blue);
  leds[snake_control] = cor_atual;
  FastLED.show();
  delay(30);
  if(mode1 == true){
    leds[snake_control] = CRGB(0,0,0);
  }
  
  
}

void rainbow(){
  snake_control = aux_control + snake_control;
  if(snake_control >= 58 or snake_control <= 2)
  {
      aux_control = -aux_control;
      aux_cor = -aux_cor;
  }

  
  switch (cor_controle%3){
    case 0: red = red - (255/NUM_LEDS);
            green = green + (255/NUM_LEDS);
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - (255/NUM_LEDS);
            blue = blue + (255/NUM_LEDS);
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - (255/NUM_LEDS);
            red = red + (255/NUM_LEDS);
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cor_atual = CRGB(red, green, blue);
  leds[snake_control] = CRGB(255,255,255);
  FastLED.show();
  leds[snake_control-aux_cor] = cor_atual;

  FastLED.show();
  delay(30);
  
  if (mode2 == true){
    leds[snake_control-2*aux_cor] = CRGB(0,0,0);
  }
}

void changingLedsIndividually(int ind_led){
  int x = 1;
  switch (cor_controle%3){
    case 0: red = red - x;
            green = green + x;
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - x;
            blue = blue + x;
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - x;
            red = red + x;
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cores[ind_led] = CRGB(red, green, blue);
  leds[ind_led] = cores[ind_led];
}

void lollypop(){

  snake_control = aux_control + snake_control;
  if(snake_control >= 58 or snake_control <= 2)
  {
      aux_control = -aux_control;
      aux_cor = -aux_cor;
      interval = interval + aux_interval;
  }
  if(interval >=255 || interval <= 0){
    aux_interval = -aux_interval;
  }
  
  switch (cor_controle%3){
    case 0: red = red - (interval);
            green = green + (interval);
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - (interval);
            blue = blue + (interval);
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - (interval);
            red = red + (interval);
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cor_atual = CRGB(red, green, blue);
  leds[snake_control] = CRGB(255,255,255);
  FastLED.show();
  leds[snake_control-aux_cor] = cor_atual;

  FastLED.show();
  delay(30);
  
  if(mode3 == true){
    leds[snake_control-2*aux_cor] = CRGB(0,0,0);
  }
}

void Custom(){
  if(interval > 255){interval = 255;}
  else if(interval < 1){interval = 1;}  
  
  snake_control = aux_control + snake_control;
  if(snake_control >= 58 or snake_control <= 2)
  {
      aux_control = -aux_control;
      aux_cor = -aux_cor;
  }

  
  switch (cor_controle%3){
    case 0: red = red - (interval);
            green = green + (interval);
            blue = 0;
            if(red <= 0 || green >= 255){
              cor_controle++;
            }
      break;
    case 1: green = green - (interval);
            blue = blue + (interval);
            red = 0;
            if(green <= 0 || blue >= 255){
              cor_controle++;
            }
      break;
    case 2: blue = blue - (interval);
            red = red + (interval);
            green = 0;
            if(blue <= 0 || red >= 255){
              cor_controle++;
            }
     break;
  }
  
  
  if(red > 255){ red == 255;}
  if(green > 255){ green == 255;}
  if(blue > 255){ blue == 255;}
  if(red < 0){ red == 0;}
  if(blue < 0){ blue == 0;}
  if(green < 0){ green == 0;}
  
  cor_atual = CRGB(red, green, blue);
  leds[snake_control] = CRGB(255,255,255);
  FastLED.show();
  leds[snake_control-aux_cor] = cor_atual;

  FastLED.show();
  delay(30);
  
  if (mode4 == true){
    leds[snake_control-2*aux_cor] = CRGB(0,0,0);
  }
}

void individual(){
  for(int i = 0; i < NUM_LEDS; i++){
    changingLedsIndividually(i);
  }
  delay(80);
  FastLED.show();
}

