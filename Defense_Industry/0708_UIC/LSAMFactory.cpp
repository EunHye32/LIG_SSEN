#include "LSAMFactory.h"

WeaponInterface*
LSAMFactory::createWeapon()
{
  return new LSAM;
}

void
LSAMFactory::deleteWeapon(WeaponInterface* weapon)
{
  delete weapon;
}