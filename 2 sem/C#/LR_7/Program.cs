using System;

namespace LR_7
{
    //rational number
    class RatNum: IEquatable<RatNum>
    {
        private int up;
        private int down;

        public int Up { get { return up; } }
        public int Down { get { return down; } }

        public RatNum(int up = 1, int down = 1)
        {
            if (down > 0)
            {
                this.down = down;
            }
            else if (down == 0)
            {
                throw new Exception("No zero in denominator.");
            }
            else
            {
                this.down = -down;
                this.up *= -1;
            }

            this.up = up;
            this.down = down;

            this.reduce();
        }



        //////////////////////////////////////////////////////////////////////////////////
        #region operator <

        public static bool operator <(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down < num2.up * num1.down);
        }

        public static bool operator <(RatNum num1, double num2)
        {
            return ((double)num1.up < num2 * num1.down);
        }

        #endregion operator <


        //////////////////////////////////////////////////////////////////////////////////
        #region operator <=

        public static bool operator <=(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down <= num2.up * num1.down);
        }

        public static bool operator <=(RatNum num1, double num2)
        {
            return ((double)num1.up <= num2 * num1.down);
        }

        #endregion operator <=


        //////////////////////////////////////////////////////////////////////////////////
        #region operator >

        public static bool operator >(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down > num2.up * num1.down);
        }

        public static bool operator >(RatNum num1, double num2)
        {
            return ((double)num1.up > num2 * num1.down);
        }

        #endregion operator >


        //////////////////////////////////////////////////////////////////////////////////
        #region operator >=

        public static bool operator >=(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down >= num2.up * num1.down);
        }

        public static bool operator >=(RatNum num1, double num2)
        {
            return ((double)num1.up >= num2 * num1.down);
        }

        #endregion operator >=


        //////////////////////////////////////////////////////////////////////////////////
        #region operator ==

        public static bool operator ==(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down == num2.up * num1.down);
        }

        public static bool operator ==(RatNum num1, double num2)
        {
            return ((double)num1.up == num2 * num1.down);
        }

        #endregion operator ==


        //////////////////////////////////////////////////////////////////////////////////
        #region operator !=

        public static bool operator !=(RatNum num1, RatNum num2)
        {
            return (num1.up * num2.down != num2.up * num1.down);
        }

        public static bool operator !=(RatNum num1, double num2)
        {
            return ((double)num1.up != num2 * num1.down);
        }

        #endregion operator !=

        //////////////////////////////////////////////////////////////////////////////////
        #region Equals

        public override bool Equals(object obj)
        {
            if (obj == null)
            {
                return false;
            }
            RatNum num = obj as RatNum;

            if (num == null)
            {
                return false;
            }
            
            return ((up == num.up) && (down == num.down));
        }

        public bool Equals(RatNum num)
        {
            return ((up == num.up) && (down == num.down));
        }

        public static bool Equals(RatNum num1, RatNum num2)
        {
            return ((num1.up == num2.up) && (num1.down == num2.down)) ;
        }

        public static bool Equals (RatNum num, int a)
        {
            num.reduce();

            return (num.down == 1 && num.up == a) ;
        }

        
        public bool Equals (int a)
        {
            reduce();

            return (down == 1 && up == a) ;
        }
        

        public static bool Equals(RatNum num, double a)
        {
            return ((double)num.up / num.down == a) ;
        }

        
        public bool Equals(double a)
        {
            return ((double)up / down == a) ;
        }
        

        #endregion


        //////////////////////////////////////////////////////////////////////////////////
        #region sum

        public static RatNum operator +(RatNum num1, RatNum num2)
        {
            var a = new RatNum(num1.up * num2.down + num2.up * num1.down, num1.down * num2.down);
            return a;
        }

        public static RatNum operator +(RatNum num1, int num2)
        {
            var a = new RatNum(num1.up + num2 * num1.down, num1.down);
            return a;
        }

        public static RatNum operator +(RatNum num1, double num2)
        {
            var a = new RatNum((int)(10000 * (num1.up + num2 * num1.down)), num1.down * 10000);
            return a;
        }

        public static RatNum operator ++(RatNum num1)
        {
            return new RatNum(num1.up + num1.down, num1.down);
        }

        #endregion sum


        //////////////////////////////////////////////////////////////////////////////////
        #region difference

        public static RatNum operator -(RatNum num1, RatNum num2)
        {
            var a = new RatNum(num1.up * num2.down - num2.up * num1.down, num1.down * num2.down);
            return a;
        }

        public static RatNum operator -(RatNum num1, int num2)
        {
            var a = new RatNum((num1.up - num2 * num1.down), num1.down);
            return a;
        }

        public static RatNum operator -(RatNum num1, double num2)
        {
            var a = new RatNum((int)(10000 * (num1.up - num2 * num1.down)), num1.down * 10000);
            return a;
        }

        public static RatNum operator --(RatNum num1)
        {
            return new RatNum(num1.up - num1.down, num1.down);
        }

        public static RatNum operator -(RatNum num1)
        {
            return new RatNum(-num1.up, num1.down);
        }

        #endregion difference


        //////////////////////////////////////////////////////////////////////////////////
        #region multiplication

        public static RatNum operator *(RatNum num1, RatNum num2)
        {
            var a = new RatNum(num1.up * num2.up, num1.down * num2.down);
            return a;
        }

        public static RatNum operator *(RatNum num1, int num2)
        {
            var a = new RatNum(num2 * num1.up, num1.down);
            return a;
        }

        public static RatNum operator *(RatNum num1, double num2)
        {
            var a = new RatNum((int)(num2 * 10000 * num1.up), num1.down*10000);
            return a;
        }

        #endregion multiplication


        //////////////////////////////////////////////////////////////////////////////////
        #region division


        public static RatNum operator /(RatNum num1, RatNum num2)
        {
            var a = new RatNum(num1.up * num2.down, num1.down * num2.up);
            return a;
        }        
        public static RatNum operator /(RatNum num1, int num2)
        {
            RatNum a = new RatNum();
            if (num2 > 0)
            {
                a = new RatNum(num1.up, (num1.down * num2));
            }
            else if (num2 < 0)
            {
                a = new RatNum(-num1.up, (num1.down * num2));
            }
            else
            {
                throw new Exception("No divide by zero.");
            }

            return a;

        }

        public static RatNum operator /(RatNum num1, double num2)
        {
            RatNum a = new RatNum();
            if (num2 > 0)
            {
                a = new RatNum(num1.up * 10000, (int)(10000 * (num1.down * num2)));
            }
            else if (num2 < 0)
            {
                a = new RatNum(-num1.up * 10000, (int)(10000 * (num1.down * num2)));
            }
            else
            {
                throw new Exception("No division by zero.");
            }

            return a;
        }

        #endregion division


        //////////////////////////////////////////////////////////////////////////////////       
        #region Simplifying fraction

        public void reduce() 
        {
            int a = down;
            if (Math.Abs(up) > down)
            {
                a = up;
            }

            a = (int)Math.Sqrt(a);

            while ((up % 2 == 0) && (down % 2 == 0))
            {
                up /= 2;
                down /= 2;
            }

            for (int i = 3; i < a; i += 2)
            {
                while ((up % i == 0) && (down % i == 0))
                {
                    up /= i;
                    down /= i;
                }
            }
        }

        #endregion


        //////////////////////////////////////////////////////////////////////////////////
        #region ToString

        public override string ToString()
        {
            return $"{(double)up / (double)down}";
        }

        public string NormToString()
        {
            if (up == 0)
            {
                return "0";
            }
            if (down == 1)
            {
                return $"{up}";
            }
            return $"{up}/{down}";
        }

        public string DecToString()
        {
            if (up == 0)
            {
                return "0";
            }
            if (down == 1)
            {
                return $"{up}";
            }
            return ((double)up / (double)down).ToString();
        }

        #endregion ToString


        //////////////////////////////////////////////////////////////////////////////////
        #region Get from others types

        public static RatNum ToRatNum(string str)
        {
            int up = 0, down = 1;
            bool minus = false;

            for (int i = 0; i < str.Length; i++)
            {
                if (str[i] >= '0' && str[i] <= '9')
                {
                    up *= 10;
                    up += str[i] - 48;
                }
                else if (str[i] == '/') // '/'
                {
                    down = 0;

                    for (int j = i + 1; j < str.Length; j++)
                    {
                        if (str[j] >= '0' && str[j] <= '9')
                        {
                            down *= 10;
                            down += str[j] - '0';
                        }
                    }

                    break;
                }
                else if (str[i] == '.' || str[i] == ',') // '.' ','
                {
                    down = 1;

                    for (int j = i + 1; j < str.Length; j++)
                    {
                        up *= 10;
                        up += str[j] - 48;
                        down *= 10;
                    }

                    break;
                }
                else if (str[i] == '-')
                {
                    minus = true;
                }
            }

            RatNum a = new RatNum(up * ((minus) ? (-1) : (1)), down);
            return a;
        }
        public static RatNum ToRatNum(int num2)
        {
            return new RatNum(num2, 1);
        }

        public static RatNum ToRatNum(double num2)
        {
            var a = new RatNum((int)(num2 * 10000), (int)Math.Pow(10, (int)Math.Log10((int)num2) + 4));
            return a;
        }

        #endregion Get from others types


        //////////////////////////////////////////////////////////////////////////////////
        #region To double or int

        public static double ToDouble(RatNum num)
        {
            if (num.down == 1)
            {
                return num.up;
            }
            return (double)num.up / num.down;
        }

        public double ToDouble()
        {
            if (down == 1)
            {
                return up;
            }
            return (double)up / down;
        }

        public static int ToInt(RatNum num)
        {
            if (num.down == 1)
            {
                return num.up;
            }
            return num.up / num.down;
        }

        public int ToInt()
        {
            if (down == 1)
            {
                return up;
            }
            return up / down;
        }

        #endregion


        //////////////////////////////////////////////////////////////////////////////////
        #region type conversion

        public static implicit operator RatNum(int x)
        {
            return new RatNum(x, 1);
        }

        public static implicit operator RatNum(double x)
        {
            var a = new RatNum((int)(x * 10000), 10000);
            return a;
        }

        public static explicit operator int(RatNum num)
        {
           return num.up / num.down;
        }

        public static explicit operator double(RatNum num)
        {
            return (double)num.up / num.down;
        }

        #endregion
    }
}