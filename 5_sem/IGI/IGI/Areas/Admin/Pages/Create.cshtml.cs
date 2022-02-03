using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using IGI.Data;
using IGI.Entities;

namespace IGI.Areas.Admin.Pages
{
    public class CreateModel : PageModel
    {
        private readonly IGI.Data.ApplicationDbContext _context;
        private readonly IWebHostEnvironment _enviroment;

        public CreateModel(IGI.Data.ApplicationDbContext context, IWebHostEnvironment environment)
        {
            _context = context;
            _enviroment = environment;
        }

        public IActionResult OnGet()
        {
            return Page();
        }

        [BindProperty]
        public PCPart PCPart { get; set; }
        [BindProperty]
        public IFormFile Image { get; set; }

        // To protect from overposting attacks, see https://aka.ms/RazorPagesCRUD
        public async Task<IActionResult> OnPostAsync()
        {
            ViewData["Id"] = new SelectList(_context.PartCategories, "Id", "Name");
            if (!ModelState.IsValid)
            {
                return Page();
            }

            _context.Parts.Add(PCPart);
            await _context.SaveChangesAsync();

            if(Image != null)
			{
                var fileName = $"{PCPart.Id}" + Path.GetExtension(Image.FileName);
                PCPart.Image = fileName;
                var path = Path.Combine(_enviroment.WebRootPath, "Images", fileName);
                using (var fStream = new FileStream(path, FileMode.Create))
				{
                    await Image.CopyToAsync(fStream);
				}
                await _context.SaveChangesAsync();
			}

            return RedirectToPage("./Index");
        }
    }
}
