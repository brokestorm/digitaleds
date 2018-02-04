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

#define BRIGHTNESS          200
#define FRAMES_PER_SECOND  60

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
}
  
void loop()
{ 
  // send the 'leds' array out to the actual LED strip
    
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND); 
  //leds[0] = CRGB(255,0,0);
  
  //snake(false);
  //rainbow(false);
  //lollypop(false);
  //Custom(5, false);
  individual(60);
}

void espectre(){
  for(int i = 0; i < NUM_LEDS; i++){
    changingLedsByCluster();
  }
}

void individual(int tim){
  for(int i = 0; i < NUM_LEDS; i++){
    changingLedsIndividually(i);
  } 
  delay(tim);
  FastLED.show();
  
}

void changingLedsByCluster(){
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
;

void snake(bool mode){
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
  if(mode == true){
    leds[snake_control] = CRGB(0,0,0);
  }
  
  
}

void rainbow(bool mode){
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
  if (mode == true){
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

void lollypop( bool mode){

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
  
  if(mode == true){
    leds[snake_control-2*aux_cor] = CRGB(0,0,0);
  }
}

void Custom(int interval, bool mode){
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
  
  if (mode == true){
    leds[snake_control-2*aux_cor] = CRGB(0,0,0);
  }
}
