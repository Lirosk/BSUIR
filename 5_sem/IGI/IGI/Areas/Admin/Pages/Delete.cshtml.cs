using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using IGI.Data;
using IGI.Entities;

namespace IGI.Areas.Admin.Pages
{
    public class DeleteModel : PageModel
    {
        private readonly IGI.Data.ApplicationDbContext _context;

        public DeleteModel(IGI.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        [BindProperty]
        public PCPart PCPart { get; set; }

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

        public async Task<IActionResult> OnPostAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            PCPart = await _context.Parts.FindAsync(id);

            if (PCPart != null)
            {
                _context.Parts.Remove(PCPart);
                await _context.SaveChangesAsync();
            }

            return RedirectToPage("./Index");
        }
    }
}
