﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadingMethod/ActiveHidSmDevice.h"

#include "hidapi.h"


FActiveHidSmDevice::FActiveHidSmDevice(hid_device_info* DeviceInfo)
    : DeviceInfo(DeviceInfo)
{
    Device = hid_open_path(DeviceInfo->path);
    bDeviceOpened = Device != nullptr;
    if (bDeviceOpened) hid_set_nonblocking(Device, 1);
}

FActiveHidSmDevice::~FActiveHidSmDevice()
{
    if(Device) hid_close(Device);
}

int FActiveHidSmDevice::Read(uint8* data, size_t length) const
{
    return hid_read(Device, data, length);
}