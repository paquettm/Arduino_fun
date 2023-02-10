#pragma once

#include "List.h"

class Actor;

//Registry class to hold references to all Actor-class objects allowing mass update
class Registry {
 private:
  List<const Actor*> registeredObjects;

 public:
  void Register(Actor* object);
  
  void Update() const;

  void Message(char* message) const;

  void UpdateTo(int value) const;
};