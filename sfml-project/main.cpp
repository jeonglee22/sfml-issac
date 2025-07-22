#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(960, 540, "Binding of Isaac: Rebirth");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}