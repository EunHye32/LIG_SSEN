#pragma once
#include "WeaponInterface.h"

class EngagementControlSystem
{
public:
  void setWeapon(WeaponInterface*);
  void startEngagement();

private:
  WeaponInterface* weapon;
};

