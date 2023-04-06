#include <Arduino.h>
#include <encoder.hpp>
using namespace arduino;
#define ENCODER_DAT 1
#define ENCODER_CLK 2 
#define LED_PWM 3

static int_encoder<ENCODER_DAT,ENCODER_CLK,true> knob;
static unsigned long long knob_old_pos;
static unsigned unsigned char led_value;
void setup() {
  Serial.begin(115200);
  knob.initialize();
  knob_old_pos = knob.position()/4;
  ledcSetup(0,32768,8);
  ledcAttachPin(LED_PWM,0);
}

void loop() {
  unsigned long long pos = knob.position()/4;
  if(pos>knob_old_pos) {
    if(led_value<255) {
      ++led_value;
      ledcWrite(0,led_value);
    } 
  } else if(pos<knob_old_pos) {
    if(led_value>0) {
      --led_value;
      ledcWrite(0,led_value);
    }
  }
}