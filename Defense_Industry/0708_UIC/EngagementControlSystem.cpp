#include "EngagementControlSystem.h"
#include "MSAM.h"
#include "LSAM.h"
#include <iostream>

void
EngagementControlSystem::setWeapon(WeaponInterface* tmpWeapon)
{
  // dependency injection
  this->weapon = tmpWeapon;
}

void
EngagementControlSystem::startEngagement()
{
  std::cout << "Start Engagement" << std::endl;
  this->weapon->engage();
}