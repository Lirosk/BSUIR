using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using IGI.Entities;

namespace IGI.Models
{
    public class CartItem
	{
        public PCPart PcPart { get; set; }
        public int Quantity { get; set; }
    }
    public class Cart
    {
        public Dictionary<int, CartItem> Items { get; set; }
        public Cart()
		{
            Items = new Dictionary<int, CartItem>();
		}

        public virtual int Count
		{
			get
			{
                return Items.Sum(item => item.Value.Quantity);
			}
		}

        public virtual double Price
		{
			get
			{
				return Math.Truncate(Items.Sum(item => item.Value.Quantity * item.Value.PcPart.Price) * 100) / 100;
			}
		}

		public virtual void AddToCart(PCPart pcPart)
		{
			if (Items.ContainsKey(pcPart.Id))
				Items[pcPart.Id].Quantity++;
			else
				Items.Add(pcPart.Id, new CartItem { PcPart = pcPart, Quantity = 1 });
		}

		public virtual void RemoveFromCart(int id)
		{
			Items.Remove(id);
		}

		public virtual void ClearAll()
		{
			Items.Clear();
		}
    }
}
