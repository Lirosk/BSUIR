using System;
using System.Collections.Generic;

namespace task_1
{
    enum Months
    {
        NotSet,
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        Octomber,
        November,
        December
    }
    class Human
    {
        public string Name { get; set; } = "";

        public int Age { get; set; } = 0;
        
        

        public int Height { get; set; } = 0;

        public string Speciality { get; set; } = "";

        public int DayOfBirthday { get; set; } = 0;

        public Months? MonthOfBirthday { get; set; } = null;
        
        public Human()
        {
            //this.MonthOfBirthday.Value
        }

        public Human(string name, int age, int height, string speciality, int dayOfBirthday, Months monthOfBirthday)
        {
            this.Name = name;
            this.Age = age;
            this.Height = height;
            this.Speciality = speciality;
            this.DayOfBirthday = dayOfBirthday;
            this.MonthOfBirthday = monthOfBirthday;
        }

        public override string ToString()
        {
            return $"Name: {Name}\n" +
                   $"Age: {Age} years\n" +
                   $"Height: {Height} (cm)\n" +
                   $"Speciality: {Speciality}\n" + 
                   $"Birthday: {DayOfBirthday} of {MonthOfBirthday}\n";
        }
    }

    class Sportsmen : Human
    {
        public int Mass { get; set; } = 0;

        public int ExpInSport { get; set; } = 0;

        public int WhenStarted { get; set; } = 0;
        public Sportsmen()
        {
        }

        public Sportsmen(string name, int age, int height, string speciality, int dayOfBirthday, Months monthOfBirthday,
            int mass, int whenStarted) :
            base(name, age, height, speciality, dayOfBirthday, monthOfBirthday)
        {
            this.Mass = mass;
            this.ExpInSport = age - whenStarted;
            this.WhenStarted = whenStarted;
        }

        public override string ToString()
        {
            return base.ToString() + 
                   $"Mass: {Mass} (kg)\n" +
                   $"Experience in sport: {ExpInSport} years\n" +
                   $"Started at {WhenStarted} years\n";
        }
    }

    class Specialist : Sportsmen
    {
        public int ExpInField { get; set; } = 0;
        
        public Specialist()
        {
        }

        public Specialist(string name, int age, int height, string speciality, int dayOfBirthday, Months monthOfBirthday, int mass, int whenStarted) :
            base(name, age, height, speciality, dayOfBirthday, monthOfBirthday, mass, whenStarted)
        {
            this.ExpInField = age - whenStarted;
            this.ExpInSport = age - whenStarted;
        }

        public string ToString()
        {
            return base.ToString() + 
                   $"Experience in field: {ExpInField} years.\n";
        }
    }

/*    
    interface IMove
    {
        int GetValue();
        
        static void Moving()
        {
            Console.WriteLine("Walking");
        }
    }
    
    struct Athlete : IMove
    {
        public static string NameS = "Wruum";
        
        public void Message()
        {
            IMove.Moving();
        }
    }
  */  
    
    class Program
    {
        static void Add(List<Specialist> list, GetSpec setSpecialist)
        {
            list.Add(setSpecialist());
        }

        static void Del(List<Specialist> list, int position)
        {
            list.RemoveAt(position);
        }

        static void swap<T>(ref T a, ref T b)
        {
            var temp = a;
            a = b;
            b = temp;
        }

        static void ShowSpecialist(Specialist specialist)
        {
            Console.WriteLine(specialist.ToString());
        }

        static Specialist SetSpecialist()
        {
            Specialist temp = new Specialist();

            Console.Write("\nEnter name of your sportsmen: ");
            temp.Name = (Console.ReadLine());

            Console.Write("\nEnter age of your sportsmen: ");
            temp.Age = (Int32.Parse(Console.ReadLine()));

            Console.Write("\nEnter height(cm): ");
            temp.Height = (Int32.Parse(Console.ReadLine()));

            Console.Write("\nEnter speciality: ");
            temp.Speciality = (Console.ReadLine());
            
            Console.Write("\nEnter day of birthday (num): ");
            temp.DayOfBirthday = Int32.Parse(Console.ReadLine());
            
            Console.Write("\nEnter month of birthday (num): ");
            temp.MonthOfBirthday = (Months)(Int32.Parse(Console.ReadLine()));
            
            Console.Write("\nEnter mass(kg): ");
            temp.Mass = (Int32.Parse(Console.ReadLine()));

            Console.Write("\nEnter the age, at which started sport: ");
            temp.WhenStarted = (Int32.Parse(Console.ReadLine()));

            temp.ExpInSport = (temp.Age - temp.WhenStarted);

            temp.ExpInField = (temp.Age - temp.WhenStarted);

            return temp;
        }

        delegate void ShowSpec(Specialist a);

        delegate Specialist GetSpec();

        static void ShowAll(List<Specialist> list, ShowSpec showSpecialist)
        {
            foreach (var i in list)
            {
                showSpecialist(i);
                Console.WriteLine("\n");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void Main()
        {
  
            System.Threading.Thread.Sleep(1000);
            
            
            List<Specialist> specialists = new List<Specialist>
            {
                new Specialist("Alex", 38, 187,
                    "Boxer", 1, (Months)5, 82, 20),
                new Specialist("Aang", 112, 167,
                    "Avatar", 5, (Months)4, 60, 3)
            };
            
            Console.WriteLine(specialists[0].ToString());
            
            ShowSpec showSpec = ShowSpecialist;
            GetSpec setSpec = SetSpecialist;

            for (bool stayHere = true; stayHere;)
            {
                Console.Clear();
                Console.WriteLine("\nEnter 's' to show all sportsmen.\n" +
                                  "Enter 'e' to edit inf about someone.\n" +
                                  "Enter 'a' to add one.\n" +
                                  "Enter 'd' to del one.\n" +
                                  "Enter 'q' to exit.\n"
                );

                switch (Console.ReadLine())
                {
                    case ("s"):
                    {
                        ShowAll(specialists, showSpec);
                        Console.WriteLine("\n\npress any key...");
                        Console.ReadKey();
                        break;
                    }
                    case ("e"):
                    {
                        Console.Clear();
                        Console.WriteLine("Show all? ('y' - yes / 'n' - no)\n");

                        switch (Console.ReadLine())
                        {
                            case ("y"):
                            {
                                ShowAll(specialists, showSpec);
                                Console.WriteLine("\n\npress any key...");
                                Console.ReadKey();
                                break;
                            }
                        }

                        Console.WriteLine("Enter the order (starts with 1): ");

                        var selection = Int32.Parse(Console.ReadLine());

                        specialists[selection - 1] = SetSpecialist();

                        break;
                    }
                    case ("a"):
                    {
                        Add(specialists, setSpec);
                        break;
                    }
                    case ("d"):
                    {
                        Console.Clear();
                        Console.WriteLine("Show all? ('y' - yes / 'n' - no)\n");

                        switch (Console.ReadLine())
                        {
                            case ("y"):
                            {
                                ShowAll(specialists, showSpec);
                                Console.WriteLine("\n\npress any key...");
                                Console.ReadKey();
                                break;
                            }
                        }

                        Console.WriteLine("Enter the order (starts with 1): ");

                        var selection = Int32.Parse(Console.ReadLine());

                        Del(specialists, selection - 1);

                        break;
                    }
                    case ("q"):
                    {
                        stayHere = false;
                        break;
                    }
                    default:
                    {
                        Console.WriteLine("\nIncorrect input..");
                        Console.WriteLine("\n\npress any key...");
                        Console.ReadKey();
                        break;
                    }
                }
            }
        }
    }
}