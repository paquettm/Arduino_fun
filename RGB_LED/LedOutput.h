#pragma once

#include "Actor.h"

//Example Actor class that powers a Led with increasing and decreasing power cycle
//Another example could use the timer to change their PWM according to the actual time elapsed between updates
class LedOutput : public Actor{
  constexpr byte INVALID_PIN = 255;//TODO: must be static?

  private:
    //the led objec tis connected to a pin and has a current PWM value
    byte m_Pin{INVALID_PIN};
    int m_Value{0};
    int m_Increment{1};


  public:
    LedOutput() = delete;//to prevent default constructor
    LedOutput(int pin, int value_0, int increment_0){
      m_Pin = pin;
      m_Value = value_0;
      m_Increment = increment_0;
      init();
    }

    byte GetValue() const { return m_Value; }

    void init(){
        pinMode(m_Pin, OUTPUT);
        digitalWrite(m_Pin, m_Value);//output the initial value
    }

    void Update() override {
      if((m_Value<=0 && m_Increment<0) || (m_Value>=255 && m_Increment>0))
        this->increment = -this->increment;
      this->value = constrain(this->value + this->increment, 0, 255);
      analogWrite(this->pin, this->value);
    }

    void UpdateTo(int value) override {
      this->value = value;
      analogWrite(this->pin, this->value);
    }

    void Message(char* message){
      if(strcmp(message,"ledOutput/update")==0)
        this->update();
    }

};