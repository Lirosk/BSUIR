using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using IGI.Entities;
using IGI.Models;
using IGI.Data;
using Microsoft.Extensions.Logging;

namespace IGI.Controllers
{
	[Authorize]
	public class ProductController : Controller
	{
/*		private ILogger _logger;*/
		ApplicationDbContext _context;
		private int _pageSize;

		public ProductController(ApplicationDbContext context/*, ILogger<ProductController> logger*/)
		{
			_pageSize = 3;
			_context = context;
/*			_logger = logger;*/
		}

		[Route("Catalog")]
		[Route("Catalog/Page_{pageNo}")]
		public IActionResult Index(int? categoryId, int pageNo=1)
		{
/*			_logger.LogInformation($"info: Category Id: {categoryId ?? 0}, Page Number: {pageNo}");*/
			ViewData["Categories"] = _context.PartCategories;
			ViewData["CurrentCategory"] = categoryId ?? 0;
			var filteredPcParts = _context.Parts.Where(p => !categoryId.HasValue || p.CategoryId == categoryId.Value);
			var model = ListViewModel<PCPart>.GetModel(filteredPcParts, pageNo, _pageSize);
			if (Request.Headers["x-requested-with"].ToString().ToLower().Equals("xmlhttprequest"))
			{
				return PartialView("_listpartial", model);
			}
			else
			{
				return View(model);
			}
		}
	}
}
