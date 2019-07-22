// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "TimerManager.h"
#include "LevelEditorViewport.h"
#include "Hid.h"
#include "SpaceMouseConfig.h"
#include "SharedPointer.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpaceMouseEditor, Log, All);

#define SPACEMOUSE_BUTTONCOUNT 48

#define BUTTONDOWN(id) (Buttons[id] && !PrevButtons[id])

class FSpaceMouseDevice
{
private:
	bool PrevMoving;

	FString dr0;
	FString dr1;
	FString dr2;
	FString dr3;
public:

	int InternalID = 0;
	hid_device* Device;
	hid_device_info* DeviceInfo;

	bool DeviceOpened;
	unsigned char OutputBuffer[80];

	FVector Translation;
	FRotator Rotation;
	bool Buttons[SPACEMOUSE_BUTTONCOUNT];

	bool OnMovementStartedFrame = false;
	bool OnMovementEndedFrame = false;
	bool Moving = false;

	void Tick();

	explicit FSpaceMouseDevice(hid_device_info* dev, int iid)
	{
		InternalID = iid;
		PrevMoving = false;
		Moving = false;
		OnMovementStartedFrame = false;
		DeviceInfo = dev;
		Device = hid_open_path(dev->path);
		DeviceOpened = Device != nullptr;
		if (DeviceOpened) hid_set_nonblocking(Device, 1);
	}

	~FSpaceMouseDevice()
	{
		hid_close(Device);
	}
};

class FSpaceMouseModule : public IModuleInterface
{
private:

	FTimerDelegate OnTickDel;
	void OnTick();
	bool Enabled = false;

	FVector Translation;
	FRotator Rotation;
	bool PrevButtons[SPACEMOUSE_BUTTONCOUNT];
	bool Buttons[SPACEMOUSE_BUTTONCOUNT];

	bool bWasOrbitCamera = false;
	bool bWasRealtime = false;

	TArray<FSpaceMouseDevice*> Devices;

	// We're only supplied with a pointer so we can't create a TWeakPtr :(
	FEditorViewportClient* ActiveViewportClient = nullptr;
	FString focusedVpType = "";

	bool HandleSettingsSaved();
	void RegisterSettings();
	void UnregisterSettings();

	void ManageActiveViewport();
	void MoveActiveViewport(bool onmovestarted, bool onmoveended);
	const bool IsActiveViewportInvalid(const TArray<FEditorViewportClient*>& AllViewportClients);

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }

	int LastErrorCode;

	static USpaceMouseConfig* Settings;
	static float gResolution;

	float Resolution = 350.0;

	bool DeviceOpened;
	hid_device_info * DeviceInfos;
};
