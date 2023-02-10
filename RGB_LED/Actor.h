#pragma once

class Registry;

//basic abstract class to serve as interface
class Actor{
 private:
  Registry* m_Registry;
    
 public:
  virtual void Update() = 0;

  virtual void UpdateTo(int value) = 0;

  //send messages pub/sub style
  virtual void Message(char* message) = 0;

  void SetRegistry(const Registry* registry){
    this->m_Registry = registry;
  }

  //do we want to broadcast now or collect and broadcast at the next cycle?
  void MessageOut(const String& message){//plus rapide avec const
    this->m_Registry->Message(message);
  }

};