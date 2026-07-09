#pragma once
#include "WeaponInterface.h"

class WeaponFactory
{
public:
  virtual WeaponInterface* createWeapon() = 0;
  virtual void deleteWeapon(WeaponInterface* weapon) = 0;
};

