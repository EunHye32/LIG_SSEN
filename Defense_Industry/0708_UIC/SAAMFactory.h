#pragma once
#include "WeaponFactory.h"
#include "SAAM.h"

class SAAMFactory :
  public WeaponFactory
{
public:
  WeaponInterface* createWeapon() override;
  void deleteWeapon(WeaponInterface*) override;
};