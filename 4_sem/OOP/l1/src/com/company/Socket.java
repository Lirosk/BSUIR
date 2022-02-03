package com.company;
import com.company.Devices.Device;

import java.util.LinkedList;
import java.util.List;

public class Socket {
    public List<Device> connected;

    public Socket()
    {
        connected = new LinkedList<>();
    }

    @Override
    public String toString()
    {
        if (connected == null || connected.isEmpty())
        {
            return "No devices connected";
        }

        String output = "";
        int i = 0;

        for (Device device: connected)
        {
            output += i + ": " + device + "\n";
            i++;
        }

        return output;
    }

    public float calculateConsumption()
    {
        if (connected == null || connected.isEmpty())
        {
            return 0;
        }

        float consumption = 0;
        for (Device device : connected)
        {
            consumption += device.getConsumption();
        }

        return consumption;
    }
}
