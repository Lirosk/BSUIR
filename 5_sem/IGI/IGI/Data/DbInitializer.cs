using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using IGI.Entities;

namespace IGI.Data
{
	public class DbInitializer
	{
		public static async Task Seed(ApplicationDbContext context,
								UserManager<ApplicationUser> userManager,
								RoleManager<IdentityRole> roleManager)
		{
			string adminEmail = "admin@gmail.com";
			string adminRoleName = "admin";

			context.Database.EnsureCreated();
			if(!context.Roles.Any())
			{
				var roleAdmin = new IdentityRole
				{
					Name = adminRoleName,
					NormalizedName = adminRoleName
				};
				await roleManager.CreateAsync(roleAdmin);
			}
			if(!context.Users.Any())
			{
				var user = new ApplicationUser
				{
					Email = "user@gmail.com",
					UserName = "user@gmail.com"
				};
				await userManager.CreateAsync(user, "1234567890");

				var admin = new ApplicationUser
				{
					Email = adminEmail,
					UserName = "admin@gmail.com"
				};
				await userManager.CreateAsync(admin, "1234567890");

				admin = await userManager.FindByEmailAsync(adminEmail);
				await userManager.AddToRoleAsync(admin, adminRoleName);
			}
			if (!context.Parts.Any())
			{
				context.Parts.AddRange(
					new List<PCPart>
					{
						new PCPart {
							Name="AMD Ryzen 5 5600X", Description="3.7-4.2GHz 6 core 65W", Price=299.0,
							Image="AMD Ryzen 5 5600X.jpg", CategoryId=1},
						new PCPart {
							Name="AMD Ryzen 7 5800X", Description="3.8-4.7GHz 8 core 105W", Price=386.66,
							Image="AMD Ryzen 7 5800X.jpg", CategoryId=1},
						new PCPart {
							Name="Intel Core i7-10700K", Description="3.8-5.1GHz 8 core 125W", Price=324.0,
							Image="Intel Core i7-10700K.jpg", CategoryId=1},
						new PCPart {
							Name="Noctua NH-D15 chromax.black", Description="Height 165 mm", Price=109.95,
							Image="Noctua NH-D15 chromax.black.jpg", CategoryId=2},
						new PCPart {
							Name="Noctua NH-P1 Fanless CPU Cooler", Description="Height 158 mm", Price=109.9,
							Image="Noctua NH-P1 Fanless CPU Cooler.jpg", CategoryId=2},
						new PCPart {
							Name="Noctua NH-U9S chromax.black 46.4 CFM CPU Cooler", Description="Height 125 mm", Price=69.95,
							Image="Noctua NH-U9S chromax.black 46.4 CFM CPU Cooler.jpg", CategoryId=2},
						new PCPart {
							Name="Asus ROG STRIX B550-F GAMING (WI-FI) ATX AM4 Motherboard", Description="AM4 Socket", Price=194.99,
							Image="Asus ROG STRIX B550-F GAMING (WI-FI) ATX AM4 Motherboard.jpg", CategoryId=3},
						new PCPart {
							Name="Asus TUF GAMING X570-PLUS (WI-FI) ATX AM4 Motherboard", Description="AM4 Socket Wifi", Price=195.05,
							Image="Asus TUF GAMING X570-PLUS (WI-FI) ATX AM4 Motherboard.jpg", CategoryId=3},
						new PCPart {
							Name="MSI MAG B550 TOMAHAWK ATX AM4 Motherboard", Description="AM4 Socket", Price=139.99,
							Image="MSI MAG B550 TOMAHAWK ATX AM4 Motherboard.jpg", CategoryId=3},
						new PCPart {
							Name="Corsair Vengeance RGB Pro 16 GB (2 x 8 GB) DDR4-3200 CL16 Memory", Description="16 GB (2 x 8 GB) DDR4-3200 CL16", Price=86.99,
							Image="Corsair Vengeance RGB Pro 16 GB (2 x 8 GB) DDR4-3200 CL16 Memory.jpg", CategoryId=4},
						new PCPart {
							Name="Samsung 970 Evo Plus 1 TB M.2-2280 NVME Solid State Drive", Description="1 TB M.2", Price=139.99,
							Image="Samsung 970 Evo Plus 1 TB M.2-2280 NVME Solid State Drive.jpg", CategoryId=5},
						new PCPart {
							Name="EVGA GeForce RTX 3060 12 GB XC GAMING Video Card", Description="12 GB", Price=769.95,
							Image="EVGA GeForce RTX 3060 12 GB XC GAMING Video Card.jpg", CategoryId=6},
						new PCPart {
							Name="NZXT H510 ATX Mid Tower Case", Description="Mid Tower", Price=74.98,
							Image="NZXT H510 ATX Mid Tower Case.jpg", CategoryId=7},
						new PCPart {
							Name="EVGA SuperNOVA GA 650 W 80+ Gold Certified Fully Modular ATX Power Supply", Description="650 W 80+ Gold Certified", Price=111.97,
							Image="EVGA SuperNOVA GA 650 W 80 Gold Certified Fully Modular ATX Power Supply.jpg", CategoryId=8}
					});
				await context.SaveChangesAsync();
			}
			if (!context.PartCategories.Any())
			{
				context.PartCategories.AddRange(
					new List<PCPartCategory>
					{
						new PCPartCategory {Name="CPU"},
						new PCPartCategory {Name="CPU Cooler"},
						new PCPartCategory {Name="Motherboard"},
						new PCPartCategory {Name="Memory"},
						new PCPartCategory {Name="Storage"},
						new PCPartCategory {Name="Video Card"},
						new PCPartCategory {Name="Case"},
						new PCPartCategory {Name="Power Supply"}
					});
				await context.SaveChangesAsync();
			}
		}
	}
}
