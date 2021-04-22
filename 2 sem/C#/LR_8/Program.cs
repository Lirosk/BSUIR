using System;
using System.Threading;

namespace LR_8
{ 
    class Program
    {
        static void Main()
        {           
            try
            {
                Random r = new Random();

                Pack<Smth> pack = new Pack<Smth>(new Smth("unknown"), new Carryables(30));
                {
                    pack.Contingent.ReducedQuantityEvent += delegate (object sender, ushort exq, ushort q)
                    { 
                        Console.Write("From anonymous delegate event-handler: \"Quantity has changed from {0} to {1}!\"\n", exq, q);
                    };
                }


                char a;
                uint turn = 0;

                while (turn < 16)
                {
                    Console.Clear();
                    if (pack.Contingent.Quantity != 0)
                    {
                        if (pack.Contingent.AteRecently)
                        {
                            if (r.Next(0, 5) == 0 && pack.Contingent.Name != "drones")
                            {
                                pack.Contingent.AteRecently = false;
                            }
                        }
                        if (pack.Contingent.RestRecently)
                        {
                            if (r.Next(0, 5) == 0)
                            {
                                pack.Contingent.RestRecently = false;
                            }
                        }

                        Console.WriteLine($"{pack.Contingent.Quantity} {pack.Contingent.Name} in your pack\npack's Contingent still going over the border with Staff...\n\n\n");

                        if (!pack.Contingent.AteRecently && pack.Contingent.Name != "drones")
                        {
                            pack.Contingent.PrintHungry();
                        }
                        if (!pack.Contingent.RestRecently)
                        {
                            pack.Contingent.PrintTired();
                        }
                    }


                    Console.WriteLine(
                        "\n\n" +
                        (pack.Contingent.Name != "drones" ? "'h' to check if someone is hungry\n" : "") +
                        "'t' to check if someone if tired\n" +
                        "'k' to just keep walking\n" +
                        "'r' to have a rest\n" +
                        "'e' to eat someone from your pack\n" +
                        "'s' - Staff?\n" +
                        "'c' to check the Staff\n" +
                        "'w' - who in my pack?\n" +
                        "'n' to change Contingent of pack\n\n"
                        );

                    if (!Char.TryParse(Console.ReadLine(), out a))
                    {
                        continue;
                    }

                    Console.Write("\n\n");

                    if (a == 't')
                    {
                        pack.Contingent.IsTired();
                    }
                    else if (a == 'k')
                    {
                        pack.Contingent.Walk();
                        Console.Write("\n");

                        Thread.Sleep(2000);
                        if (!pack.Contingent.AteRecently && pack.Contingent.Name != "drones")
                        {
                            pack.Contingent.PrintHungry();
                            Thread.Sleep(1000);

                            pack.Contingent.RandomSpirits();
                        }
                        if (!pack.Contingent.RestRecently)
                        {
                            pack.Contingent.PrintTired();
                            Thread.Sleep(1000);

                            pack.Contingent.RandomSpirits();
                        }

                        Thread.Sleep(2000);

                        turn++;
                    }
                    else if (a == 'r')
                    {
                        pack.Contingent.HaveARest();
                        pack.Contingent.RestRecently = true;
                    }
                    else if (a == 'e')
                    {
                        pack.Contingent.EatSomeone();
                        pack.Contingent.AteRecently = true;
                    }
                    else if (a == 'w')
                    {
                        pack.Contingent.WhoIsPack();
                    }
                    else if (a == 'c')
                    {
                        pack.CheckStaff();
                    }
                    else if (a == 's')
                    {
                        Console.WriteLine($"\"{pack.Staff.Name}\" - you can hear..\n");
                    }
                    else if (a == 'n')
                    {
                        Console.WriteLine($"All of {pack.Contingent.Name} prey to God of interfaces for transforming...");

                        if (pack.Contingent.Name == "Carryables")
                        {
                            pack.Contingent = new Drones((ushort)(pack.Contingent.Quantity / 2));
                            {
                                pack.Contingent.ReducedQuantityEvent -= null;
                                pack.Contingent.ReducedQuantityEvent += (Drones, exq, q) =>
                                {
                                    Console.Write("From lambda event-handler: \"Quantity has changed from {0} to {1}!\"\n", exq, q);
                                };
                            }
                        }
                        else //if (pack.Contingent.Name == "drones")
                        {
                            pack.Contingent = new Carryables((ushort)(pack.Contingent.Quantity * 2));
                            {
                                pack.Contingent.ReducedQuantityEvent -= null;
                                pack.Contingent.ReducedQuantityEvent += delegate (object sender, ushort exq, ushort q)
                                { 
                                    Console.Write("From anonymous delegate event-handler: \"Quantity has changed from {0} to {1}!\"\n", exq, q);
                                };                               
                            }
                        }

                        Thread.Sleep(2000);
                        Console.WriteLine("Transformation...");
                        Thread.Sleep(2000);
                        Console.WriteLine($"Now it {pack.Contingent.Name}!");
                        Thread.Sleep(2000);
                        Console.WriteLine("Praise the interfaces!\n");
                    }
                    else if (pack.Contingent.Name != "drones" && a == 'h')
                    {
                        pack.Contingent.IsHungry();
                    }
                    else
                    {
                        Console.WriteLine("Unknown decision...\n");
                        pack.Contingent.RandomSpirits();
                    }

                    if (pack.Contingent.Quantity == 0)
                    {
                        Console.WriteLine("\n\nGAME OVER...\n\n");
                        return;
                    }

                    Thread.Sleep(5000);
                }            

                pack.Contingent.Quantity = 0;
                pack.Contingent.Ending();

                while (true)
                {
                    Console.Clear();

                    Console.WriteLine(
                        "'h' to check if someone is hungry\n" +
                        "'t' to check if someone if tired\n" +
                        "'k' to just keep walking\n" +
                        "'r' to have a rest\n" +
                        "'e' to eat someone from your pack\n" +
                        "'s' - Staff?\n" +
                        "'c' to check the Staff\n" +
                        "'w' - who in my pack?\n" +
                        "'n' to change Contingent of pack\n\n");

                    Char.TryParse(Console.ReadLine(), out a);

                    try
                    {
                        switch (a)
                        {
                            case ('h'):
                                {
                                    pack.Contingent.IsHungry();
                                    break;
                                }
                            case ('t'):
                                {
                                    pack.Contingent.IsTired();
                                    break;
                                }
                            case ('k'):
                                {
                                    pack.Contingent.Walk();

                                    break;
                                }
                            case ('r'):
                                {
                                    pack.Contingent.HaveARest();
                                    break;
                                }
                            case ('e'):
                                {
                                    pack.Contingent.EatSomeone();
                                    break;
                                }
                            case ('w'):
                                {
                                    Console.WriteLine("No members in pack..\n");
                                    break;
                                }
                            case ('c'):
                                {
                                    pack.CheckStaff();
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
                                    break;
                                }
                        }

                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("Exception!\n" + ex.Message + " //0 members in pack so it wrong to execute methods that change(decrease) the unsigned Quantity, right?");
                        Thread.Sleep(3000);
                    }
                    Thread.Sleep(3000);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
