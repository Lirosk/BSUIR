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
    public class IndexModel : PageModel
    {
        private readonly IGI.Data.ApplicationDbContext _context;

        public IndexModel(IGI.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        public IList<PCPart> PCPart { get;set; }

        public async Task OnGetAsync()
        {
            PCPart = await _context.Parts.ToListAsync();
        }
    }
}
