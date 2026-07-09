#pragma once
#include "WeaponFactory.h"
#include "MSAM.h"

class MSAMFactory :
    public WeaponFactory
{
public:
  WeaponInterface* createWeapon() override;
  void deleteWeapon(WeaponInterface*) override;
};