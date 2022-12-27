// Define Pins
#define RED 6
#define GREEN 5
#define  BLUE 3

//basic template list class to hold objects
template <typename T>
class List {
 private:
  struct Node {
    T data;
    Node* next;
  };

  Node* head;
  int size;

 public:
  List() : head(nullptr), size(0) {}

  ~List() {
    clear();
  }

  int getSize() const {
    return size;
  }

  bool isEmpty() const {
    return size == 0;
  }

  void clear() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    size = 0;
  }

  void add(const T& data) {
    Node* newNode = new Node{data, head};
    head = newNode;
    ++size;
  }

  T& operator[](int index) {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }

  const T& operator[](int index) const {
    Node* current = head;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  }
};

//basic abstract class to serve as interface
class Actor{
 public:
  // Abstract method with a single integer parameter
  virtual void update() = 0;

  // Abstract method with a single integer parameter
  virtual void updateTo(int value) = 0;
};

//Registry class to hold references to all Actor-class objects allowing mass update
class Registry {
 private:
  List<Actor*> registeredObjects;

 public:
  void add(Actor* object) {
    registeredObjects.add(object);
  }

  int getNumRegisteredObjects() const {
    return registeredObjects.getSize();
  }
  
  void update() {
    for (int i = 0; i < registeredObjects.getSize(); ++i) {
      registeredObjects[i]->update();
    }
  }

  void updateTo(int value) {
    for (int i = 0; i < registeredObjects.getSize(); ++i) {
      registeredObjects[i]->updateTo(value);
    }
  }
};

//Example Actor class that powers a Led with increasing and decreasing power cycle
//Another example could use the timer to change their PWM according to the actual time elapsed between updates
class LedOutput : public Actor{
  private:
    //the led objec tis connected to a pin and has a current PWM value
    byte pin;
    int value;
    int increment;

  public:
    LedOutput(int pin, int value_0, int increment_0){
      this->pin = pin;
      this->value = value_0;
      this->increment = increment_0;
      init();
    }

    byte getValue(){
      return this->value;
    }

    void init(){
        pinMode(this->pin, OUTPUT);
        digitalWrite(this->pin, this->value);//output the initial value
    }

    void update() override {
      if((this->value<=0 && this->increment<0) || (this->value>=255 && this->increment>0))
        this->increment = -this->increment;
      this->value += this->increment;
      analogWrite(this->pin, this->value);
    }

    void updateTo(int value) override {
      this->value = value;
      analogWrite(this->pin, this->value);
    }

};

// define variables
Registry registry;
#define delayTime 1 // fading time between colors

//define and register red, green, blue LEDs with different PWM rates of change
void setup(){
  LedOutput redLed(RED,0,1); 
  LedOutput greenLed(GREEN,170,2); 
  LedOutput blueLed(BLUE,170,3); 
  
  registry.add(&redLed);
  registry.add(&greenLed);
  registry.add(&blueLed);
}

// main loop to call the registry update each cycle
void loop()
{  
  registry.update();
  delay(delayTime);
}

