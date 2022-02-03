using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using IGI.Data;
using IGI.Entities;

namespace IGI.Blazor.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class PCPartsAPI : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public PCPartsAPI(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/PCPartsAPI
        [HttpGet]
        public async Task<ActionResult<IEnumerable<PCPart>>> GetParts()
        {
            return await _context.Parts.ToListAsync();
        }

        // GET: api/PCPartsAPI/5
        [HttpGet("{id}")]
        public async Task<ActionResult<PCPart>> GetPCPart(int id)
        {
            var pCPart = await _context.Parts.FindAsync(id);

            if (pCPart == null)
            {
                return NotFound();
            }

            return pCPart;
        }

        // PUT: api/PCPartsAPI/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutPCPart(int id, PCPart pCPart)
        {
            if (id != pCPart.Id)
            {
                return BadRequest();
            }

            _context.Entry(pCPart).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!PCPartExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/PCPartsAPI
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<PCPart>> PostPCPart(PCPart pCPart)
        {
            _context.Parts.Add(pCPart);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetPCPart", new { id = pCPart.Id }, pCPart);
        }

        // DELETE: api/PCPartsAPI/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeletePCPart(int id)
        {
            var pCPart = await _context.Parts.FindAsync(id);
            if (pCPart == null)
            {
                return NotFound();
            }

            _context.Parts.Remove(pCPart);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool PCPartExists(int id)
        {
            return _context.Parts.Any(e => e.Id == id);
        }
    }
}
