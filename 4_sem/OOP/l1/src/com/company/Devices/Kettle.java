package com.company.Devices;


public class Kettle extends Device {
    public float maxVolume;
    public float liquidVolume;

    public Kettle() {}

    public Kettle(float consumption, float maxVolume) {
        super(consumption);

        this.maxVolume = maxVolume;
        this.liquidVolume = 0;
    }

    @Override
    public float getConsumption() {
        System.out.println("Kettle power = " + super.getConsumption());
        return super.getConsumption();
    }

    public void fillWithLiquid(float volume) {
        if (volume < 0)
        {
            System.out.println("Volume must be positive");
            return;
        }

        if (volume <= maxVolume - liquidVolume)
        {
            liquidVolume += volume;
        }
        else
        {
            liquidVolume = maxVolume;
        }
    }

/*    @Override
    public String toString() {
        String res = "Kettle, consumption: " + getConsumption();
        return res;
    }*/
}