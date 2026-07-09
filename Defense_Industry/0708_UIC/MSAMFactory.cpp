#include "MSAMFactory.h"

WeaponInterface*
MSAMFactory::createWeapon()
{
  return new MSAM;
}

void
MSAMFactory::deleteWeapon(WeaponInterface* weapon)
{
  delete weapon;
}