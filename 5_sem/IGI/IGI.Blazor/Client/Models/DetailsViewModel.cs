using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json.Serialization;

namespace IGI.Blazor.Client.Models
{
	public class DetailsViewModel
	{
		[JsonPropertyName("name")]
		public string Name { get; set; }
		[JsonPropertyName("description")]
		public string Description { get; set; }
		[JsonPropertyName("price")]
		public double Price { get; set; }
		[JsonPropertyName("image")]
		public string Image { get; set; }
	}
}
