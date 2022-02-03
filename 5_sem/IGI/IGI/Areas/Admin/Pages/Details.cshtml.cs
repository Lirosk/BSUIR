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
    public class DetailsModel : PageModel
    {
        private readonly IGI.Data.ApplicationDbContext _context;

        public DetailsModel(IGI.Data.ApplicationDbContext context)
        {
            _context = context;
        }

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
    }
}
