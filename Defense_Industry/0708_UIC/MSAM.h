#pragma once
#include "WeaponInterface.h"
class MSAM :
    public WeaponInterface
{
public:
  void engage() override;
};

