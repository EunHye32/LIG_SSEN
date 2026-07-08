#pragma once
#include "WeaponInterface.h"

class EngagementControlSystem
{
public:
  WeaponInterface* createWeapon(unsigned short);
  void deleteWeapon(WeaponInterface*);

  void startEngagement(WeaponInterface*);

private:
  WeaponInterface* weapon;
};

