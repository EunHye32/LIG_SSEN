#include "EngagementControlSystem.h"
#include <iostream>

int main()
{
  EngagementControlSystem* ECS = new EngagementControlSystem;

  WeaponInterface* weapon = ECS->createWeapon(1); // 2
  ECS->startEngagement(weapon); // 1
  ECS->deleteWeapon(weapon); // 2

  delete ECS; // 3
}