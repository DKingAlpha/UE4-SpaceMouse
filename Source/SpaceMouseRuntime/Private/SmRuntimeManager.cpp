﻿// Copyright 2018-2021 David Morasz All Rights Reserved.
// This source code is under MIT License https://github.com/microdee/UE4-SpaceMouse/blob/master/LICENSE


#include "SmRuntimeManager.h"

FUserSettings FSmRuntimeManager::GetUserSettings()
{
    static FUserSettings BaseSettings {};
    return BaseSettings;
}
