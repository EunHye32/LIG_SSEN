#pragma once
#include "WeaponInterface.h"
class SAAM :
  public WeaponInterface
{
public:
  void engage() override;
};