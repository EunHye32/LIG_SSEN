#include "SAAMFactory.h"

WeaponInterface*
SAAMFactory::createWeapon()
{
  return new SAAM;
}

void
SAAMFactory::deleteWeapon(WeaponInterface* weapon)
{
  delete weapon;
}