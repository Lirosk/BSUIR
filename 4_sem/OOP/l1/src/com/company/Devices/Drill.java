package com.company.Devices;

public class Drill extends Tool
{
    public float rotationFrequency = 1;

    public Drill(){}


    public Drill(float consumption)
    {
        super(consumption);
    }

    @Override
    public float getConsumption()
    {
        return super.getConsumption()*rotationFrequency;
    }

    public void changeFrequency(float value)
    {
        if (value < 0 || value > 1)
        {
            System.out.println("Frequency value must be between 0 and 1!\n");
        }
    }

    @Override
    public String toString()
    {
        String res = "Drill, consumption: ";

        if (isSwitchedOn)
        {
            res += consumption + "*" + rotationFrequency + "=";
        }

        res += getConsumption();

        return res;
    }
}