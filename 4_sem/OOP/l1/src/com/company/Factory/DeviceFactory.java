package com.company.Factory;

import com.company.Devices.Device;
import com.company.Devices.Drill;
import com.company.Devices.Flashlight;
import com.company.Devices.Kettle;

public class DeviceFactory implements DeviceCreator {

    @Override
    public Device create(Devices req) {

        switch (req) {
            case Flashlight:
                return new Flashlight();
            case Kettle:
                return new Kettle();
            case Drill:
                return new Drill();
            default:
                return null; // sorry
        }
    }
}
