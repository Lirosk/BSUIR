using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using IGI.Data;
using IGI.Entities;

namespace IGI.Blazor.Server.Controllers
{
    public class PCPartsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public PCPartsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: PCParts
        public async Task<IActionResult> Index()
        {
            return View(await _context.Parts.ToListAsync());
        }

        // GET: PCParts/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var pCPart = await _context.Parts
                .FirstOrDefaultAsync(m => m.Id == id);
            if (pCPart == null)
            {
                return NotFound();
            }

            return View(pCPart);
        }

        // GET: PCParts/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: PCParts/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Description,Price,Image,CategoryId")] PCPart pCPart)
        {
            if (ModelState.IsValid)
            {
                _context.Add(pCPart);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(pCPart);
        }

        // GET: PCParts/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var pCPart = await _context.Parts.FindAsync(id);
            if (pCPart == null)
            {
                return NotFound();
            }
            return View(pCPart);
        }

        // POST: PCParts/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Description,Price,Image,CategoryId")] PCPart pCPart)
        {
            if (id != pCPart.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(pCPart);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!PCPartExists(pCPart.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(pCPart);
        }

        // GET: PCParts/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var pCPart = await _context.Parts
                .FirstOrDefaultAsync(m => m.Id == id);
            if (pCPart == null)
            {
                return NotFound();
            }

            return View(pCPart);
        }

        // POST: PCParts/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var pCPart = await _context.Parts.FindAsync(id);
            _context.Parts.Remove(pCPart);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool PCPartExists(int id)
        {
            return _context.Parts.Any(e => e.Id == id);
        }

		[HttpGet]
		public async Task<ActionResult<IEnumerable<PCPart>>> GetPCParts(int? categoryId)
		{
			var pcParts = _context.Parts.Where(p => !categoryId.HasValue || p.Id == categoryId.Value);
			return await pcParts.ToListAsync();
		}

/*		[HttpGet]
        public IEnumerable<PCPart> Get()
        {
            return _context.Parts.ToArray();
        }*/
    }

}
