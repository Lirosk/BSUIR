package com.company.Devices;
import java.lang.String;

public abstract class Tool extends Device {
    public String instruction;

    public Tool() {
    }

    public Tool(float consumption) {
        super(consumption);
        this.instruction = "";
    }

    /*
    @Override
    public float getConsumption()
    {
        return consumption;
    }
    */

    @Override
    public String toString()
    {
        String res = "Tool, consumption: " + getConsumption();
        return res;
    }
}