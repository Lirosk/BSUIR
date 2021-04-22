using System;
using static LR_6.IPackContingent;

namespace LR_6
{
    class pack<T>
    {
        public IPackСontingent Contingent { get; set; }
        public T Staff { get; set; }

        public void CheckStaff()
        {
            if (Contingent.Quantity == 0)
            {
                Console.WriteLine("Staff has been stolen...\n");
            }
            else
            {
                Console.WriteLine("Staff still here.");
            }
        }

        public pack(T Staff, IPackСontingent Contingent = null)
        {
            this.Staff = Staff;
            this.Contingent = Contingent;
        }
    }
}
