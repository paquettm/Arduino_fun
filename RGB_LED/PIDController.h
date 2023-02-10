#ifndef PIDController_class
#define PIDController_class

class PIDController {
  private:
    // PID controller constants
    float kp, ki, kd;
    // error sum and previous error
    float errorSum, prevError;
    // output range
    int outMin, outMax;
    // input and output pins
    int inputPin, outputPin;
    // current output value
    int output;

  public:
    // constructor
    PIDController(int inputPin, int outputPin, float kp, float ki, float kd, int outMin, int outMax) {
      this->inputPin = inputPin;
      this->outputPin = outputPin;
      this->kp = kp;
      this->ki = ki;
      this->kd = kd;
      this->outMin = outMin;
      this->outMax = outMax;
      this->errorSum = 0.0;
      this->prevError = 0.0;
      this->output = 0;
    }

    // update the PID controller and output the control signal
    void update(float setpoint) {
      // read input value from photoresistor
      int input = analogRead(inputPin);
      Serial.println(input);
      // calculate error
      float error = setpoint - input;

      // update error sum
      errorSum += error;

      // calculate PID output
      output = kp * error + ki * errorSum + kd * (error - prevError);

      // limit output to the specified range
      output = constrain(output, outMin, outMax);

      // set output pin to PWM value
      analogWrite(outputPin, output);

      // update previous error
      prevError = error;
    }
};
#endif