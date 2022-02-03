package com.company.Factory;

import com.company.Devices.Device;

public interface DeviceCreator {
    Device create(Devices req);
}
