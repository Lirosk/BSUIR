using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Threading.Tasks;

namespace FileManager
{
	class Overseer
	{
		private bool enabled = true;
		private Commands slave;// does all the work
		private string sourceDirectoryPath;
		private string logPath;

		internal FileSystemWatcher watcher;

		public Overseer(Options options)
		{
			sourceDirectoryPath = options.SourceDirectoryPath;
			logPath = options.LogPath;

			slave = new Commands(options);

			watcher = new FileSystemWatcher(sourceDirectoryPath);

			watcher.Error += Watcher_ErrorAsync;
			watcher.Deleted += Watcher_Deleted;
			watcher.Created += Watcher_Created;
			watcher.Created += slave.OnAdded;
			watcher.Changed += Watcher_Changed;
			watcher.Renamed += Watcher_Renamed;
		}

		public void Start()
		{
			watcher.EnableRaisingEvents = true;
			while (enabled)
			{
				Thread.Sleep(1000);
			}
		}

		public void Stop()
		{
			watcher.EnableRaisingEvents = false;
			enabled = false;
		}

		private void Watcher_Renamed(object sender, RenamedEventArgs e)
		{
			string fileEvent = "renamed to " + e.FullPath;
			string filePath = e.OldFullPath;
			RecordEntryAsync(fileEvent, filePath);
		}

		private void Watcher_Changed(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "changed";
			string filePath = e.FullPath;
			RecordEntryAsync(fileEvent, filePath);
		}


		private void Watcher_Created(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "created";
			string filePath = e.FullPath;
			RecordEntryAsync(fileEvent, filePath);
		}


		private void Watcher_Deleted(object sender, FileSystemEventArgs e)
		{
			string fileEvent = "deleted";
			string filePath = e.FullPath;
			RecordEntryAsync(fileEvent, filePath);
		}

		private async void Watcher_ErrorAsync(object sender, ErrorEventArgs e)
		{
			await Task.Run(() =>
			{
				using (StreamWriter writer = GetStreamWriter(logPath, 10_000))
			{
				writer.WriteLine("\nException!\n" + DateTime.Now.ToString("dd/MM/yyyy hh:mm:ss ") + e.GetException().Message + "\n\n");
				writer.Flush();
			}
		});
		}

		private async Task RecordEntryAsync(string fileEvent, string filePath)
		{
			await Task.Run(()=>
			{
				using (StreamWriter writer = GetStreamWriter(logPath, 10_000))
				{
					writer.WriteLine(String.Format("{0} file {1} was {2}\n",
						DateTime.Now.ToString("dd/MM/yyyy hh:mm:ss"), filePath, fileEvent));
					writer.Flush();
				}
			});
		}

		internal static StreamWriter GetStreamWriter(string path, int timeoutMs)
		{
			var time = Stopwatch.StartNew();
			while (time.ElapsedMilliseconds < timeoutMs)
			{
				try
				{
					return new StreamWriter(path, true);
				}
				catch (IOException e)
				{
					// access error
					if (e.HResult != -2147024864)
						throw;
				}
			}

			throw new TimeoutException($"Failed to get a write handle to {path} within {timeoutMs}ms.");
		}
	}
}
