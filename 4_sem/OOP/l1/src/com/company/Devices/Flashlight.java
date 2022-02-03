package com.company.Devices;

public class Flashlight extends Device
{
    public float brightness = 1;

    public Flashlight(){}

    public Flashlight(float consumption)
    {
        super(consumption);
    }

    @Override
    public float getConsumption()
    {
        return super.getConsumption() * brightness;
    }

    public void changeBrightness(float value)
    {
        if (value < 0 || value > 1)
        {
            System.out.println("Brightness value must be between 0 and 1!\n");
            return;
        }

        brightness = value;
    }

    @Override
    public String toString()
    {
        String res = "Flashlight, consumption: ";

        if (isSwitchedOn)
        {
            res += consumption + "*" + brightness + "=";
        }

        res += getConsumption();

        return res;
    }
}