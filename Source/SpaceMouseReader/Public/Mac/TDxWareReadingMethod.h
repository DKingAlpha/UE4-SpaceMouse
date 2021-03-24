﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if PLATFORM_MAC

#include "CoreMinimal.h"
#include "ReadingMethod/DataReadingMethod.h"

struct FTDxDeviceModel
{
    uint16 VID;
    uint16 PID;
}

class SPACEMOUSEREADER_API FTDxWareReadingMethod
    : public FDataReadingMethod
    , public TSharedFromThis<FTDxWareReadingMethod, ESPMode::ThreadSafe>
{
private:
    TArray<FTDxDeviceModel> SeenDevices;
    FProcessedDeviceOutput AccumulatedData;

    static void DeviceAdded(uint32_t unused);
    static void DeviceRemoved(uint32_t unused);
    static void DeviceEvent(uint32_t unused, uint32_t msg_type, void* msg_arg);

public:
    FTDxWareReadingMethod();
    ~FTDxWareReadingMethod();

    uint16 ClientID = 0;
    bool bDriverLoaded = false;
    bool bHasOldDriver = false; // 3Dconnexion drivers before 10 beta 4 are "old", not all buttons will work
    bool bHasNewDriver = false; // drivers >= 10.2.2 are "new", and can process events on a separate thread
    bool bMoved = false;

    virtual void Tick(FDataReadingOutput& Output, float DeltaSecs) override;
}

#endif