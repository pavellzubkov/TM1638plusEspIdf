/*
* Project Name: TM1638plus 
* File: TM1638plus_common
* Description: cpp  file for common data and functions between model 1 and 2 classes
* Arduino library TM1638plus
* Author: Gavin Lyons.
* URL: https://github.com/gavinlyonsrepo/TM1638plus
*/

#include "TM1638plus_common.h"


TM1638plus_common::TM1638plus_common()
{
	// Blank constructor
}

void TM1638plus_common::pinMode(gpio_num_t pin,gpio_mode_t mode){
  gpio_reset_pin(pin);
  gpio_set_direction(pin, mode);
}

void TM1638plus_common::digitalWrite(gpio_num_t pin,uint32_t level){
 // gpio_reset_pin(pin);
  gpio_set_direction(pin, GPIO_MODE_OUTPUT);
  gpio_set_level(pin,level);
}

void TM1638plus_common::delayMicroseconds(uint32_t usec){
  ets_delay_us(usec);
}

int TM1638plus_common::digitalRead(gpio_num_t pin){
 // gpio_reset_pin(pin);
  gpio_set_direction(pin, GPIO_MODE_INPUT);
  return gpio_get_level(pin);
}

uint8_t  TM1638plus_common::HighFreqshiftin(gpio_num_t dataPin, gpio_num_t clockPin, uint8_t bitOrder) 
{
    uint8_t value = 0;
    uint8_t i = 0;

    for(i = 0; i < 8; ++i) {
        
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(TM_HFIN_DELAY);
        
        if(bitOrder == LSBFIRST)
            value |= digitalRead(dataPin) << i;
        else
            value |= digitalRead(dataPin) << (7 - i);
            
        digitalWrite(clockPin, LOW);
        delayMicroseconds(TM_HFIN_DELAY);
    }
    return value;
}

void TM1638plus_common::HighFreqshiftOut(gpio_num_t dataPin, gpio_num_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else    
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));
            
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(TM_HFOUT_DELAY);
        digitalWrite(clockPin, LOW);
        delayMicroseconds(TM_HFOUT_DELAY);
    }
}
