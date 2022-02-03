using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using IGI.Extensions;
using IGI.Models;

namespace IGI.Components
{
	public class CartViewComponent : ViewComponent
	{
		private Cart _cart;
		public CartViewComponent(Cart cart)
		{
			_cart = cart;
		}
		public IViewComponentResult Invoke()
		{
			var cart = HttpContext.Session.Get<Cart>("cart");
			return View(cart);
		}

	}
}
