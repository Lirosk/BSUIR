namespace LR_6
{
    interface IPackContingent
    {
        interface IPackСontingent
        {
            bool AteRecently { get; set; }

            bool RestRecently { get; set; }

            void PrintHungry();

            void PrintTired();

            void Walk();

            int Quantity { get; set; }

            string Name { get; set; }

            void IsHungry();
            void IsTired();

            void RandomSpirits();

            void HaveARest();

            void EatSomeone();
            void WhoIsPack();

            void Ending();
        }
    }
}
