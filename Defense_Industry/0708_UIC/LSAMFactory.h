#pragma once
#include "WeaponFactory.h"
#include "LSAM.h"

class LSAMFactory :
  public WeaponFactory
{
public:
  WeaponInterface* createWeapon() override;
  void deleteWeapon(WeaponInterface*) override;
};