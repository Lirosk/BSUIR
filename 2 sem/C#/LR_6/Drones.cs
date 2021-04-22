using System;
using static LR_6.IPackContingent;
using System.Threading;

namespace LR_6
{
    class Drones : IPackСontingent //it could be the drones...
    {
        public void PrintHungry()
        {

        }
        public void PrintTired()
        {
            Console.WriteLine("Someone's battery low..\n");
        }

        public bool AteRecently { get; set; }
        public bool RestRecently { get; set; }
        public void Walk()
        {
            Console.WriteLine("Drones are flying.\nWzzzuuuuuuhh in the wind..\n");
        }

        public Drones(int value = 0, string Name = "drones")
        {
            if (value > 0)
            {
                Quantity = value;
            }
            else
            {
                Quantity = 0;
            }

            this.Name = Name;

            AteRecently = false;
            RestRecently = false;
        }

        public int Quantity { get; set; }

        public string Name { get; set; }

        public void IsHungry() //cant be hungry
        {


            if (Quantity == 0)
            {
                Console.WriteLine("There are no drones to charge their batteries...\n");
            }
            else if (AteRecently)
            {
                Console.WriteLine("There are no triggers about batteries charge now.");//("Everybody feels fine");
            }
            else
            {
                if (new Random().Next(0, 4) != 0)
                {
                    byte a = (byte)new Random().Next(1, 6);

                    if (a >= Quantity)
                    {
                        Quantity = 0;
                        Console.WriteLine("Their batteries are low.\nExecuting the program to power save for black box...\n");
                    }
                    else
                    {
                        Quantity -= a;
                        Console.WriteLine($"{a} drones have trouble with batteries.\nRemains {Quantity} who can continue.");
                    }
                }
                else
                {
                    Console.WriteLine("They make beep-bop, but you don't understand beep-bop...\n");
                    RandomSpirits();
                }
            }
        }

        public void IsTired() //only if battery
        {


            if (Quantity == 0)
            {
                Console.WriteLine("There are no drones to be need for battery charge...");
            }
            else if (RestRecently)
            {
                Console.WriteLine("Batteries are full.");//("Everybody feels fine");
            }
            else
            {
                if (new Random().Next(0, 4) != 0)
                {
                    byte a = (byte)new Random().Next(1, 6);

                    if (a >= Quantity)
                    {
                        Quantity = 0;
                        Console.WriteLine("All of their batteries are low.\nThey fell to the ground...\n");
                    }
                    else
                    {
                        Quantity -= a;
                        Console.WriteLine($"There are {a} with low battery.\nRemains {Quantity} who can continue.");
                    }
                }
                else
                {
                    Console.WriteLine("They told beep-bop to you, but you don't understand beep-bop...\n");
                    RandomSpirits();
                }
            }
        }

        public void RandomSpirits() //spirits?
        {
            if (Quantity == 0)
            {
                return;
            }

            if (new Random().Next(0, 2) == 1)
            {
                byte a = (byte)new Random().Next(1, 4);
                Console.WriteLine("\n\nElectro-magnetic storm make vzvzvzvvzzzzzzvzvzvzz...\n");
                Thread.Sleep(2000);

                if (a >= Quantity)
                {

                    Console.WriteLine($"The remaining {Quantity} drones just have made beep-bop and then turned off...\n");
                    Quantity = 0;
                }
                else if (Quantity == 1)
                {
                    Console.WriteLine("Your last drone's scanners detect the beep-bop-beep...\n");
                    Thread.Sleep(3000);
                    Console.WriteLine("Last drone just made its last beep-bop and turned off...\n");
                    Thread.Sleep(3000);
                }
                else
                {
                    Quantity -= a;
                    Console.WriteLine($"{a} drones from your pack just disappeared. Scanners can't detect them...\nRemain {Quantity} drones.\n");
                }
            }
        }

        public void HaveARest() //battery charge
        {

            if (Quantity == 0)
            {
                Console.WriteLine("There is no drones for battery charge...\n");
                return;
            }
            else if (RestRecently)
            {
                Console.WriteLine("All of batteries are full.");//("Everybody feels fine");
                return;
            }

            Console.WriteLine("Drones make beep-bop and charging their batteries...");
            Thread.Sleep(3000);
            Console.WriteLine("They are \"bop-beep\" that they can charge batteries...");
            Thread.Sleep(3000);
            RandomSpirits();
        }

        public void EatSomeone() //battery charge?
        {
            Console.WriteLine("Drones can't eat each other... Drones can't even eat...\n");
        }

        public void WhoIsPack()
        {
            Console.WriteLine("Beep-bop?\nDrones!\n");
        }

        public void Ending()
        {
            Console.Clear();
            Console.WriteLine("Your pack has crossed the border...\n");
            Thread.Sleep(3000);
            Console.WriteLine("They see somethings scanners can't detect on the horizon...\n");
            Thread.Sleep(3000);
            Console.WriteLine("Silence...\n");
            Thread.Sleep(3000);
            Console.WriteLine("Electro-magnetic pulse...\n");
            Thread.Sleep(5000);
        }
    }
}
