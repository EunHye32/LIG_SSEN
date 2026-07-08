#include "EngagementControlSystem.h"
#include "MSAM.h"
#include "LSAM.h"
#include <iostream>

WeaponInterface*
EngagementControlSystem::createWeapon(unsigned short weaponID)
{
  WeaponInterface* weapon = nullptr;
  if (weaponID == 1)
  {
    weapon = new MSAM;
  }
  else if (weaponID == 2)
  {
    weapon = new LSAM;
  }
  else if (weaponID == 3)
  {
    //weapon = new SAAM;
  }
  else
  {
    std::cout << "WeaponID is not defined" << std::endl;
  }

  return weapon;
}

void
EngagementControlSystem::deleteWeapon(WeaponInterface* weapon)
{
  delete weapon;
}

void
EngagementControlSystem::startEngagement(WeaponInterface* weapon)
{
  std::cout << "Start Engagement" << std::endl;

  weapon->engage();

  
}