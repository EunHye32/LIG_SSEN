#include "EngagementControlSystem.h"
#include "WeaponFactory.h"
#include "MSAMFactory.h"
#include "LSAMFactory.h"
#include "SAAMFactory.h"
#include <iostream>

int main()
{
  WeaponFactory* weaponFactory = new MSAMFactory;
  WeaponInterface* weapon = weaponFactory->createWeapon();
  EngagementControlSystem* ECS = new EngagementControlSystem;

  ECS->setWeapon(weapon); // 2
  ECS->startEngagement(); // 1

  delete ECS;
  weaponFactory->deleteWeapon(weapon);
  delete weaponFactory;
}