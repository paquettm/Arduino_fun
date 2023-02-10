#ifndef PIDLedOutput_class
#define PIDLedOutput_class

#include "Actor.h"
#include "PIDController.h"

//Example Actor class that powers a Led with increasing and decreasing power cycle
//Another example could use the timer to change their PWM according to the actual time elapsed between updates
class PIDLedOutput : public Actor{
  private:
    //the led object is connected to a pin and has a current PWM value
    int setpoint;
    PIDController *controller;

  public:
    PIDLedOutput(int input_pin, int output_pin, int setpoint){
      this->setpoint = setpoint;
      float kp = 1.0;
      float ki = 0.0;
      float kd = 0.0;
      this->controller = new PIDController(input_pin, output_pin, kp, ki, kd, 0, 255);
      pinMode(output_pin, OUTPUT);
      pinMode(input_pin, INPUT);
      digitalWrite(output_pin, 0);//output the initial value
    }

    void update() override {
      this->controller->update(this->setpoint);
    }

    void updateTo(int value) override {
      this->controller->update(value);
    }

    void message(char* message) override {
      if(strcmp(message,"ledOutput/update")==0)
        this->update();
    }

};
#endif