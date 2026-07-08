#pragma once
#include "WeaponInterface.h"
class LSAM :
    public WeaponInterface
{
public:
  void engage() override;
};

