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
using Microsoft.EntityFrameworkCore;
using IGI.Data;
using IGI.Entities;


namespace IGI.Areas.Admin.Pages
{
    public class EditModel : PageModel
    {
        private IWebHostEnvironment _enviroment;
        private readonly IGI.Data.ApplicationDbContext _context;

        public EditModel(IGI.Data.ApplicationDbContext context, IWebHostEnvironment environment)
        {
            _context = context;
            _enviroment = environment;
        }

        [BindProperty]
        public PCPart PCPart { get; set; }
        [BindProperty]
        public IFormFile Image { get; set; }


        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            PCPart = await _context.Parts.FirstOrDefaultAsync(m => m.Id == id);

            if (PCPart == null)
            {
                return NotFound();
            }
            return Page();
        }

        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see https://aka.ms/RazorPagesCRUD.
        public async Task<IActionResult> OnPostAsync()
        {
            ViewData["Id"] = new SelectList(_context.PartCategories, "Id", "Name");
            if (!ModelState.IsValid)
            {
                return Page();
            }
            if (Image != null)
            {
                var fileName = $"{PCPart.Id}" + Path.GetExtension(Image.FileName);
                PCPart.Image = fileName;
                var path = Path.Combine(_enviroment.WebRootPath, "Images", fileName);
                using (var fStream = new FileStream(path, FileMode.Create))
                {
                    await Image.CopyToAsync(fStream);
                }
            }
            _context.Attach(PCPart).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PCPartExists(PCPart.Id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return RedirectToPage("./Index");
        }

        private bool PCPartExists(int id)
        {
            return _context.Parts.Any(e => e.Id == id);
        }
    }
}
