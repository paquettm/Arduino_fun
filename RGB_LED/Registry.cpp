#include "Registry.h"

#include "Actor.h"
#include "List.h"

//Registry class to hold references to all Actor-class objects allowing mass update
void Registry::Register(const Actor* object)
{
  registeredObjects.add(object);
  object->setRegistry(this);
}

void Registry::Update() {
  for (Actor* actor : registeredObjects)
  {
    actor->Update();
  }
}

void Registry::Message(char* message)
{
  for (Actor* actor : registeredObjects)
  {
    actor->Message(message);
  }
}

void Registry::UpdateTo(int value)
{
  for (Actor* actor : registeredObjects)
  {
    actor->UpdateTo(value);
  }
}
