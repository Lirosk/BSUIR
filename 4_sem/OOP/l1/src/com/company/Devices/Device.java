package com.company.Devices;

public abstract class Device {
    protected float consumption;
    protected boolean isSwitchedOn;

    public Device(){}

    public Device(float consumption) {
        this.consumption = consumption;
        this.isSwitchedOn = false;
    }

    //public abstract float getConsumption();

    public float getConsumption() {
        if (isSwitchedOn) {
            return this.consumption;
        }

        return  0f;
    }

    public void setConsumption(float value)
    {
        consumption = value;
    }

    public void switchOn()
    {
        isSwitchedOn = true;
    }

    public void switchOff()
    {
        isSwitchedOn = false;
    }

    @Override
    public String toString()
    {
        String res = "Device, consumption: " + getConsumption();
        return res;
    }
}
