using System;

namespace LR1_ind1
{
    class MyComplex
    {

        public double R = 0; //Real part
        public double I = 0; //Imaginary part

        public MyComplex()
        {
            //R = 0;
            //I = 0;
        }
        public MyComplex(double R, double I) 
        {
            this.R = R;
            this.I = I;
        }

        static public MyComplex Mult(double R1, double I1, double R2, double I2)
        {
            return new MyComplex((R1 * R2 - I1 * I2), (R1 * I2 + R2 * I1));
        }

        static public MyComplex Divide(double R1, double I1, double R2, double I2)
        {
            return new MyComplex(
                (R1 * R2 + I1 * I2) / (R2 * R2 + I2 * I2), 
                (R2 * I1 - R1 * I2) / ((R2 * R2 + I2 * I2)));
        }

        public void MultByNum(double num)
        {
            R *= num;
            I *= num;
        }

        static public MyComplex MultByNum(double R, double I, double num)
        {
            return new MyComplex(R * num, I * num);
        }

        static public MyComplex Summ(double R1, double I1, double R2, double I2)
        {
            return new MyComplex((R1 + R2), (I1 + I2));
        }

        static private double AngelOfComplex(double R, double I)
        {
            if ((R > 0) && (I >= 0))
            {
                return (Math.Atan(I / R));
            }
            else if ((R < 0) && (I >= 0))
            {
                return (Math.PI - Math.Atan(Math.Abs(I / R)));
            }
            else if ((R < 0) && (I < 0))
            {
                return (Math.PI + Math.Atan(Math.Abs(I / R)));
            }
            else if ((R > 0) && (I < 0)) //   (() && ())
            {
                return (2 * Math.PI - Math.Atan(Math.Abs(I / R)));
            }
            else if ((R == 0) && (I > 0))
            {
                return (Math.PI / 2);
            }
            else// if ((R == 0) && (I < 0))
            {
                return ((3 / 2) * Math.PI);
            }
        }
        static public MyComplex Exp(double R, double I, double exp)
        {
            double r = Math.Sqrt(R * R + I * I);
            double angle = 0;

            angle = AngelOfComplex(R, I);

            //Console.WriteLine("angle = " + angle);

            return new MyComplex(Math.Pow(r, exp) * Math.Cos((angle) * exp), Math.Pow(r, exp) * Math.Sin((angle) * exp));
        }

        public void WriteNum()//double R, double I)
        {
            if (R == 0 && I == 0)
            {
                Console.Write(0);
                return;
            }


            if (R != 0)
            {
                Console.Write(R);
            }
            else
            {
                if (I == 1)
                {
                    Console.Write("i");
                }
                else if (I == -1)
                {
                    Console.Write("-i");
                }
                else// if (I > 0) || (I < 0)
                {
                    Console.Write(I + "i");
                }

                return;
            }
            if (I != 0)
            {
                if (I == 1)
                {
                    Console.Write("+i");
                }
                else if (I == -1)
                {
                    Console.Write("-i");
                }
                else if (I > 0)
                {
                    Console.Write("+" + I + "i");
                }
                else if (I < 0)
                {
                    Console.Write(I + "i");
                }
            }

        }
    }




    class Program
    {

        static void PrintEquation(double a, double b, double c, double d, string x)
        {

            if ((a != 1) && (a != -1))
            {
                Console.Write(a + x + "^3");
            }
            else
            {
                if (a == 1)
                {
                    Console.Write(x + "^3");
                }
                else
                {
                    if (a == -1)
                    {
                        Console.Write("-" + x + "^3");
                    }
                }
            }


            if (b > 0)
            {
                if (b != 1)
                {
                    Console.Write("+" + b + x + "^2");
                }
                else
                {
                    Console.Write("+" + x + "^2");
                }
            }
            else
            {
                if (b < 0)
                {
                    if (b != -1)
                    {
                        Console.Write(b + x + "^2");
                    }
                    else
                    {
                        Console.Write("-" + x + "^2");
                    }
                }
            }

            if (c > 0)
            {
                if (c != 1)
                {
                    Console.Write("+" + c + x);
                }
                else
                {
                    Console.Write("+" + x);
                }
            }
            else
            {
                if (c < 0)
                {
                    if (c != -1)
                    {
                        Console.Write(c + x);
                    }
                    else
                    {
                        Console.Write("-" + x);
                    }
                }
            }

            if (d > 0)
            {
                Console.Write("+" + d);
            }
            else
            {
                if (d < 0)
                {
                    Console.Write(d);
                }
            }

            Console.Write("=0\n");
        }


        static double Acosh(double angle)
        {
            return (Math.Log(angle + Math.Sqrt(angle*angle-1)));
        }

        static double Asinh(double angle)
        {
            return (Math.Log(angle + Math.Sqrt(angle * angle + 1)));
        }

        static int Input(string name)
        {
        	Console.Write("Enter " + name + ": ");
        	return Int32.Parse(Console.ReadLine());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////


        static void Main()
        {

            Console.Write("\nFind solution of ax^3 + bx^2 + cx + d = 0,\na(a!=0),b,c,d of integer\n");

            double a = 0, b = 0, c = 0;

            {
                int aTemp = 0, bTemp = 0, cTemp = 0, dTemp = 0;

                aTemp = Input("a");
                bTemp = Input("b");
                cTemp = Input("c");
                dTemp = Input("d");

                for (; ; )
                {
                    

                    if (aTemp != 0)
                    {
                        break;
                    }
                    else
                    {
                        Console.Write("\n\na != 0\n\n");
                        Console.ReadLine();
                        continue;
                    }
                }

                Console.WriteLine("\n");
                PrintEquation(aTemp, bTemp, cTemp, dTemp, "x");

                a = (double)bTemp / aTemp;
                b = (double)cTemp / aTemp;
                c = (double)dTemp / aTemp;

                if (aTemp != 1)
                {
                    Console.Write("\ndivided by a\n");
                    PrintEquation(1, a, b, c, "x");
                }
            }

            /*
            Console.WriteLine("\na = " + a);
            Console.WriteLine("b = " + b);
            Console.WriteLine("c = " + c);
            */

            double Q = (a * a - 3 * b) / 9, R = (2 * a * a * a - 9 * a * b + 27 * c) / 54, S = Q * Q * Q - R * R;

            //Console.Write("\n\nQ = " + Q + "\nR = " + R + "\nS = " + S + "\n");

            double phi = 0;

            if (S > 0)
            {
                phi = Math.Acos(R / Math.Pow(Q, (double)1.5)) / 3;

                //Console.WriteLine("Acos/3 = " + Math.Acos(R / Math.Pow(Q, (double)1.5))/3 + "\nphi = "+phi);

                double x1 = -2 * Math.Sqrt(Q) * Math.Cos((double)phi) - a / 3;
                double x2 = -2 * Math.Sqrt(Q) * Math.Cos(phi + 2 * Math.PI / 3) - a / 3;
                double x3 = -2 * Math.Sqrt(Q) * Math.Cos(phi - 2 * Math.PI / 3) - a / 3;

                Console.WriteLine("\n\nAnswers:\nx1 = " + x1 + "\nx2 = " + x2 + "\nx3 = " + x3 + "\n");
            }
            else if (S < 0)
            {
                if (Q > 0)
                {
                    phi = Acosh(Math.Abs(R) / Math.Pow(Q, (double)1.5)) / 3;
                    double x1 = -2 * Math.Sign(R) * Math.Sqrt(Q) * Math.Cosh(phi) - a / 3;
                    MyComplex x2 = new MyComplex(x1 * (-0.5), Math.Sqrt(3 * Q) * Math.Cosh(phi));
                    MyComplex x3 = new MyComplex(x2.R, -x2.I);


                    Console.Write("\n\nAnswers:\nx1 = " + x1 + "\nx2 = ");
                    x2.WriteNum();
                    Console.Write("\nx3 = ");
                    x3.WriteNum();
                    Console.WriteLine();
                }
                else if (Q < 0)
                {
                    phi = Asinh(Math.Abs(R) / Math.Pow(Math.Abs(Q), (double)1.5)) / 3;
                    double x1 = -2 * Math.Sign(R) * Math.Sqrt(Math.Abs(Q)) * Math.Sinh(phi) - a / 3;
                    MyComplex x2 = new MyComplex(x1 * (-0.5), Math.Sqrt(3 * Math.Abs(Q)) * Math.Cosh(phi));
                    MyComplex x3 = new MyComplex(x2.R, -x2.I);


                    Console.Write("\n\nAnswers:\nx1 = " + x1 + "\nx2 = ");
                    x2.WriteNum();
                    Console.Write("\nx3 = ");
                    x3.WriteNum();
                    Console.WriteLine();
                }
                else // if (Q == 0)
                {
                    //MyComplex x1 = MyComplex.Exp(c - a * a * a / 27, 0, (double)1 / 3);
                    double x1 = -a / 3;
                    {
                        double temp = c - a * a * a / 27;
                        x1 -= Math.Sign(temp) * Math.Pow(Math.Abs(temp), (double)1 / 3);
                    }

                    //double x1 = Math.Sign(c - a*a*a/27) * Math.Pow(Math.Abs(c - a*a*a/27),(double)1/3) - a/3;//-Math.Pow((c - a * a * a) / 27, (double)1 / 3) - a / 3;

                    MyComplex x2 = new MyComplex(-(a + x1) / 2, (double)0.5 * Math.Sqrt(Math.Abs((a - 3 * x1) * (a + x1) - 4 * b)));
                    MyComplex x3 = new MyComplex(x2.R, -x2.I);


                    /*
                    MyComplex x1 = MyComplex.Exp(c - a * a * a / 27, 0, (double)1 / 3);
                    x1.R = -x1.R - a/3;
                    x1.I = -x1.I;
                    */

                    Console.Write("\n\nAnswers:\nx1 = " + x1 + "\nx2 = ");
                    x2.WriteNum();
                    Console.Write("\nx3 = ");
                    x3.WriteNum();
                    Console.WriteLine();
                }
            }
            else // if (S == 0)
            {
                double x1 = -2 * Math.Sign(R) * Math.Pow(Math.Abs(R), (double)1 / 3) - a / 3;
                double x2 = Math.Sign(R) *  Math.Pow(Math.Abs(R), (double)1 / 3) - a / 3;

                Console.WriteLine("\n\nAnswers:\nx1 = " + x1 + "\nx2 = " + x2 + "\n");
            }


            Console.WriteLine("\n\npress any key...");
            Console.ReadLine();
        }

    }
}
