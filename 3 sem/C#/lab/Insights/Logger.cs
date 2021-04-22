using System;
using System.Data.SqlClient;
using System.IO;
using System.Reflection;

namespace Insights
{
	public static class Logger
	{
		private static SqlCommand command = new SqlCommand() 
		{	
			CommandText = $"insert into [Northwind].[dbo].[Insights] values ({DateTime.Now.ToString(format)}, {description})", 
			CommandType = System.Data.CommandType.Text 
		};

		private static string description;
		private static string format = "yyyy-MM-dd HH:mm:ss";

		public static SqlConnection Connection
		{
			set
			{
				command.Connection = value;
			}
		}
		public static void Watcher_Created(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "created";
			string filePath = e.FullPath;
			Log($"File {filePath} was {fileEvent}.");
		}

		public static void Watcher_Changed(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "changed";
			string filePath = e.FullPath;
			Log($"File {filePath} was {fileEvent}.");
		}

		public static void Watcher_Deleted(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "deleted";
			string filePath = e.FullPath;
			Log($"File {filePath} was {fileEvent}.");
		}

		public static void Watcher_Renamed(object sender, RenamedEventArgs e)
		{
			string fileEvent = "renamed to " + e.FullPath;
			string filePath = e.OldFullPath;
			Log($"File {filePath} was {fileEvent}.");
		}

		public static void Watcher_Error(object sender, ErrorEventArgs ex)
		{
			LogEx(sender, ex.GetException());
		}

		public static void LogEx(object sender, Exception ex)
		{
			Log($"Exception! Sender: {sender.GetType().FullName}, Message: {ex.Message}.");
		}

		public static void Log(string descr)
		{
			var a = command;
			try
			{
				command.Connection.Open();
				description = descr;
				command.ExecuteNonQuery();
			}
			finally
			{
				command.Connection.Close();

			}
		}

		public static void Log(MethodInfo where, string descr)
		{
			var a = command;
			try
			{
				command.Connection.Open();
				description = where.Name + ": " + descr;
				command.ExecuteNonQuery();
			}
			finally
			{
				command.Connection.Close();

			}
		}
	}
}
