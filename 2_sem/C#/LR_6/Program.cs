using System;
using System.Threading;

namespace LR_6
{
    class Program
    {
        static void Main()
        {
            pack<Smth> Pack = new pack<Smth>(new Smth("unknown"), new CarryAbles(30));         

            char a;

            //Console.WriteLine("Quantity of your pack is {0}\n", Pack.Contingent.Quantity);

            uint turn = 0;

            while (turn < 16)
            {
                Console.Clear();
                if (Pack.Contingent.Quantity != 0)
                {
                    if (Pack.Contingent.AteRecently)
                    {
                        if (new Random().Next(0, 5) == 0 && Pack.Contingent.Name != "drones")
                        {
                            Pack.Contingent.AteRecently = false;
                        }
                    }
                    if (Pack.Contingent.RestRecently)
                    {
                        if (new Random().Next(0, 5) == 0)
                        {
                            Pack.Contingent.RestRecently = false;
                        }
                    }

                    Console.WriteLine($"{Pack.Contingent.Quantity} {Pack.Contingent.Name} in your pack\nPack's Contingent still going over the border with Staff...\n\n\n");

                    if (!Pack.Contingent.AteRecently && Pack.Contingent.Name != "drones")
                    {
                        Pack.Contingent.PrintHungry();
                    }
                    if (!Pack.Contingent.RestRecently)
                    {
                        Pack.Contingent.PrintTired();
                    }
                }


                Console.WriteLine(
                    "\n\n'h' to check if someone is hungry\n" +
                    "'t' to check if someone if tired\n" +
                    "'k' to just keep walking\n" +
                    "'r' to have a rest\n" +
                    "'e' to eat someone from your pack\n" +
                    "'s' - Staff?\n" +
                    "'c' to check the Staff\n" +
                    "'w' - who in my pack?\n" +
                    "'n' to change Contingent of pack\n\n"
                    ) ;

                Char.TryParse(Console.ReadLine(), out a);

                Console.Write("\n\n");

                switch (a)
                {
                    case ('h'):
                        {
                            Pack.Contingent.IsHungry();
                            break;
                        }
                    case ('t'):
                        {
                            Pack.Contingent.IsTired();
                            break;
                        }
                    case ('k'):
                        {
                            Pack.Contingent.Walk();
                            Console.Write("\n");

                            Thread.Sleep(2000);
                            if (!Pack.Contingent.AteRecently && Pack.Contingent.Name != "drones")
                            {
                                Pack.Contingent.PrintHungry();
                                Thread.Sleep(1000);
                                Pack.Contingent.RandomSpirits();
                            }
                            if (!Pack.Contingent.RestRecently)
                            {
                                Pack.Contingent.PrintTired();
                                Thread.Sleep(1000);
                                Pack.Contingent.RandomSpirits();
                            }

                            Thread.Sleep(2000);

                            turn++;
                            break;
                        }
                    case ('r'):
                        {
                            Pack.Contingent.HaveARest();
                            Pack.Contingent.RestRecently = true;
                            break;
                        }
                    case ('e'):
                        {
                            Pack.Contingent.EatSomeone();
                            Pack.Contingent.AteRecently = true;
                            break;
                        }
                    case ('w'):
                        {
                            Pack.Contingent.WhoIsPack();
                            break;
                        }
                    case ('c'):
                        {
                            Pack.CheckStaff();
                            break;
                        }
                    case ('s'):
                        {
                            Console.WriteLine($"\"{Pack.Staff.Name}\" - you can hear..\n");
                            break;
                        }
                    case ('n'):
                        {
                            Console.WriteLine($"All of {Pack.Contingent.Name} prey to God of interfaces for transforming...");

                            if (Pack.Contingent.Name == "CarryAbless")
                            {                              
                                Pack.Contingent = new Drones(Pack.Contingent.Quantity/2);                          
                            }
                            else //if (Pack.Contingent.Name == "drones")
                            {                                
                                Pack.Contingent = new CarryAbles(Pack.Contingent.Quantity*2);
                            }
                            

                            Thread.Sleep(2000);
                            Console.WriteLine("Transformation...");
                            Thread.Sleep(2000);
                            Console.WriteLine($"Now it {Pack.Contingent.Name}!");
                            Thread.Sleep(2000);
                            Console.WriteLine("Praise the interfaces!\n");
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Unknown decision...\n");
                            Pack.Contingent.RandomSpirits();
                            break;
                        }
                }
                Thread.Sleep(5000);

                if (Pack.Contingent.Quantity == 0)
                {
                    Console.WriteLine("\n\nGAME OVER...\n\n");
                    return;
                }
            }

            Pack.Contingent.Quantity = 0;
            Pack.Contingent.Ending();

            while (true)
            {
                Console.Clear();

                Console.WriteLine(
                    "\n\n'h' to check if someone is hungry\n" +
                    "'t' to check if someone if tired\n" +
                    "'k' to just keep walking\n" +
                    "'r' to have a rest\n" +
                    "'e' to eat someone from your pack\n" +
                    "'s' - Staff?\n" +
                    "'c' to check the Staff\n" +
                    "'w' - who in my pack?\n" +
                    "'n' to change Contingent of pack\n\n"
                    );

                Char.TryParse(Console.ReadLine(), out a);

                switch (a)
                {
                    case ('h'):
                        {
                            Pack.Contingent.IsHungry();
                            break;
                        }
                    case ('t'):
                        {
                            Pack.Contingent.IsTired();
                            break;
                        }
                    case ('k'):
                        {
                            Pack.Contingent.Walk();

                            break;
                        }
                    case ('r'):
                        {
                            Pack.Contingent.HaveARest() ;
                            break;
                        }
                    case ('e'):
                        {
                            Pack.Contingent.EatSomeone();
                            break;
                        }
                    case ('w'):
                        {
                            Console.WriteLine("No members in pack..\n");
                            break;
                        }
                    case ('c'):
                        {
                            Pack.CheckStaff();
                            break;
                        }
                    case ('s'):
                        {
                            Console.WriteLine("Staff?...\n");
                            break;
                        }
                    case ('n'):
                        {
                            Console.WriteLine("There is no pack to transform...\n");
                            break;
                        }
                    default:
                        {
                            Console.WriteLine("Unknown decision...\n");
                            //Pack.Contingent.RandomSpirits();
                            break;
                        }
                }
                Thread.Sleep(5000);
            }
        }
    }
}
