#include <Arduino.h>
#include <encoder.hpp>
using namespace arduino;
#define ENCODER_DAT 13
#define ENCODER_CLK 14
#define LED_PWM 12

static int_encoder<ENCODER_DAT,ENCODER_CLK,true> knob;
static unsigned long long knob_old_pos=0;
static unsigned char led_value=0;
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
  knob_old_pos = pos;
}