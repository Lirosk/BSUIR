using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using static lab1.Program;

namespace lab1
{
	internal static class Commands
	{
		private static string _copiedpath = null;
		public static string path { get; private set; } = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);
		private static bool _cut = false;
		private static bool _quasiSmartTargeting = false;

		private static void ListOutputWithChosen(List<string> list, int chosen, int endOfFiles)
		{
			int counter = 0;

			foreach (var i in list)
			{
                if (counter < endOfFiles)
                {
                    Console.ForegroundColor = ConsoleColor.Yellow;
                }

                if (counter == chosen)
				{
					Console.ForegroundColor = ConsoleColor.Red;
				}

				Console.WriteLine(i);
				Console.ResetColor();

				counter++;
			}
		}

		public static void Cls()
		{
			Console.Clear();
		}

		public static void Rename()
		{
			var name = GetNeededName("Enter name of file/dir to rename:");
			var buf = Path.Combine(path, name);
	

			if (File.Exists(buf))
			{
				RenameFile(name);
			}
			else if (Directory.Exists(buf))
			{
				RenameDir(name);
			}
			else 
			{
				throw new Exception("File or dir not found!");
			}
		}

		public static void Zip()
		{
			var name = Path.Combine(path, GetNeededName("Enter name of file/dir to zip:"));
			var buf = Path.Combine(path, name);

			if (File.Exists(buf))
			{
				FileToZip(name);
			}
			else if (Directory.Exists(buf))
			{
				DirToZip(name);
			}
			else
			{
				throw new Exception("File or dir not found!");
			}
		}

		public static void Unzip()
		{
			var name = Path.Combine(path, GetNeededName("Enter name of file/dir to unzip:"));
			var buf = Path.Combine(path, name);

			if (Path.GetExtension(buf) == ".gz")
			{
				UnzipFile(name);
			}
			else if (Path.GetExtension(buf) == ".zip")
			{
				UnzipDir(name);
			}
			else
			{
				throw new Exception("File or dir not found!");
			}
		}

		public static void Delete()
		{
			var name = Path.Combine(path, GetNeededName("Enter name of file/dir to delete:"));
			var buf = Path.Combine(path, name);

			if (File.Exists(buf))
			{
				DeleteFile(name);
			}
			else if (Directory.Exists(buf))
			{
				DeleteDir(name);
			}
			else
			{
				throw new Exception("File or dir not found!");
			}
		}

		private static string GetNeededName(string message = null, bool filesOnly = false)
		{
			if (_quasiSmartTargeting)
			{
				return QuasiSmartChooseFileOrDir(filesOnly);
			}

			return Input(message).Trim();
		}

		private static string QuasiSmartChooseFileOrDir(bool filesOnly = false)
		{
			int endOfFiles, chosen = 0;

			List<string> list;

			{
				var listbuf = Directory.GetFiles(path).ToList<string>();
				for (int i = 0; i < listbuf.Count; i++)
				{
					listbuf[i] = Path.GetFileName(listbuf[i]);
				}

				list = listbuf;

				endOfFiles = list.Count;

				if (!filesOnly)
				{
					listbuf = Directory.GetDirectories(path).ToList<string>();
					for (int i = 0; i < listbuf.Count; i++)
					{
						listbuf[i] = Path.GetFileName(listbuf[i]);
					}

					list.AddRange(listbuf);
				}
			}

			var cycle = true;
			var len = list.Count;

			while (cycle)
			{
				ListOutputWithChosen(list, chosen, endOfFiles);

				var a = Console.ReadKey();

				switch (a.Key)
				{
					case (ConsoleKey.Enter):
						{
							cycle = false;
							break;
						}
					case (ConsoleKey.UpArrow):
						{
							chosen = ((chosen - 1) % len + len) % len;
							break;
						}
					case (ConsoleKey.DownArrow):
						{
							chosen = (chosen + 1) % len;
							break;
						}
					case (ConsoleKey.Escape):
						{
							throw new Exception("");
							//break;
						}
				}

				Console.SetCursorPosition(0, Console.CursorTop - len);
			}

			Console.SetCursorPosition(0, Console.CursorTop + len);

			Console.WriteLine("\n");

			return list[chosen];
		}

		public static void ChangeTargeting()
		{
			_quasiSmartTargeting = !_quasiSmartTargeting;
			Console.WriteLine("Targeting changed\n");
		}

		public static void Mount()
		{
			var buf = Input("Enter new path:");

			if (!Directory.Exists(buf))
			{
				throw new DirectoryNotFoundException();
			}

			path = buf;
		}

		public static void Cut()
		{
			Copy();

			_cut = true;
		}

		public static void Copy()
		{
			var name = GetNeededName("Enter the name of file/dir to copy:");
			var buf = Path.Combine(path, name);

			if (File.Exists(buf) || Directory.Exists(buf))
			{
				_copiedpath = buf;
			}
            else
            {
				throw new FileNotFoundException();
			}
		}

		public static void UnzipDir(string name)
		{
			var buf = name[..^4];

			ZipFile.ExtractToDirectory(Path.Combine(path, name), Path.Combine(path, buf));
		}

		public static void FileToZip(string name)
		{
			var buf = new StringBuilder(name);
			buf.Append(".gz");

			using (var targetStream = File.Create(Path.Combine(path, buf.ToString())))
			using (var sourceStream = new FileStream(Path.Combine(path, name), FileMode.OpenOrCreate, FileAccess.Read))// File.OpenRead(Path.Combine(path, name))
			using (var compressionStream = new GZipStream(targetStream, CompressionMode.Compress))
			{
				sourceStream.CopyTo(compressionStream);
			}
		}

		public static void UnzipFile(string name)
		{
			var buf = name[..^3];

			using (var targetStream = File.Create(Path.Combine(path, buf)))
			using (var sourceStream = File.OpenRead(Path.Combine(path, name)))// new FileStream(Path.Combine(path, name), FileMode.OpenOrCreate, FileAccess.Read))
			using (var decomressionStream = new GZipStream(sourceStream, CompressionMode.Decompress))
			{
				decomressionStream.CopyTo(targetStream);
			}
		}

		public static void DirToZip(string name)
		{
			var buf = new StringBuilder(Path.Combine(path, name));
			buf.Append(".zip");

			ZipFile.CreateFromDirectory(Path.Combine(path, name), Path.Combine(path, buf.ToString()));
		}

		public static void ReadClassFromFile(out MoreExClasses mec)
		{
			var name = GetNeededName("Enter file name to read data:");
			var buf = Path.Combine(path, name);

			switch (Path.GetExtension(name))
			{
				case (".txt"):
					{
						mec = MoreExClasses.JsonDeserialize(buf);
						break;
					}
				case (".json"):
					{
						mec = MoreExClasses.JsonDeserialize(buf);
						break;
					}
				case (".bin"):
					{
						mec = MoreExClasses.BinaryDeserialize(buf);
						break;
					}
				default:
					{
						throw new Exception("Invalid file extension!");
					}
			}
		}

		public static void WriteClassToFile(in MoreExClasses mec)
		{
			var name = GetNeededName("Enter file name to write data:");
			var buf = Path.Combine(path, name);

			switch (Path.GetExtension(name))
			{
				case (".txt"):
					{
						mec.JsonSerialize(buf);
						break;
					}
				case (".json"):
					{
						mec.JsonSerialize(buf);
						break;
					}
				case (".bin"):
					{
						mec.BinarySerialize(buf);
						break;
					}
				default:
					{
						throw new Exception("Invalid file extension!");
					}
			}
		}

		public static void Paste()
        {
			if (File.Exists(_copiedpath))
            {
				PasteFile();
            }
			else if (Directory.Exists(_copiedpath))
            {
				PasteDir();
            }
			else
            {
				throw new Exception("File or directory not found!");
            }
        }

		static private void PasteDir()
        {
			var name = Path.GetFileName(_copiedpath);
			//var buf = Path.Combine(path, name);

			if (Directory.Exists(Path.Combine(path, name)))
			{
				name = Path.GetFileName(name);

				StringBuilder buf = new StringBuilder(name);
				buf.Append(" - copy");
				name = buf.ToString();

				if (Directory.Exists(Path.Combine(path, name)))
				{
					StringBuilder againBuf;
					int i = 1;

					do
					{
						i++;
						againBuf = new StringBuilder(buf.ToString());
						againBuf.Append($" ({i})");
					}
					while (Directory.Exists(Path.Combine(path, againBuf.ToString())));

					name = againBuf.ToString();
				}
			}

			DirectoryCopy(_copiedpath, Path.Combine(path, name), true);

			if (_cut)
			{
				Directory.Delete(_copiedpath);
				_cut = false;
			}

		}

		private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs = true)
		{
			// Get the subdirectories for the specified directory.
			DirectoryInfo dir = new DirectoryInfo(sourceDirName);

			if (!dir.Exists)
			{
				throw new DirectoryNotFoundException(
					"Source directory does not exist or could not be found: "
					+ sourceDirName);
			}

			DirectoryInfo[] dirs = dir.GetDirectories();

			// If the destination directory doesn't exist, create it.       
			Directory.CreateDirectory(destDirName);

			// Get the files in the directory and copy them to the new location.
			FileInfo[] files = dir.GetFiles();
			foreach (FileInfo file in files)
			{
				string tempPath = Path.Combine(destDirName, file.Name);
				file.CopyTo(tempPath, false);
			}

			// If copying subdirectories, copy them and their contents to new location.
			if (copySubDirs)
			{
				foreach (DirectoryInfo subdir in dirs)
				{
					string tempPath = Path.Combine(destDirName, subdir.Name);
					DirectoryCopy(subdir.FullName, tempPath, copySubDirs);
				}
			}
		}

		private static void PasteFile()
		{
			var name = Path.GetFileName(_copiedpath);
			//var buf = Path.Combine(path, name);

			if (File.Exists(Path.Combine(path, name)))
			{
				var ext = Path.GetExtension(name);
				name = Path.GetFileNameWithoutExtension(name);

				StringBuilder buf = new StringBuilder(name);
				buf.Append(" - copy");

				name = buf.ToString() + ext;

				if (File.Exists(Path.Combine(path, name)))
				{
					StringBuilder againBuf;
					int i = 1;

					do
					{
						i++;
						againBuf = new StringBuilder(buf.ToString());
						againBuf.Append($" ({i})");
						againBuf.Append(ext);
					}
					while (File.Exists(Path.Combine(path, againBuf.ToString())));

					name = againBuf.ToString();
				}
			}

			File.Copy(_copiedpath, Path.Combine(path, name), true);

			if (_cut)
			{
				File.Delete(_copiedpath);
				_cut = false;
			}

		}

		private static void DeleteDir(string name)
		{
			var buf = Path.Combine(path, name);

			if (!Directory.Exists(buf))
			{
				throw new DirectoryNotFoundException();
			}

			Directory.Delete(buf);
		}

		public static void CreateFile(string name)
		{
			using (var fs = File.Create(Path.Combine(path, name))) { }
		}

		private static void DeleteFile(string name)
		{
			var buf = Path.Combine(path, name);

			if (!File.Exists(buf))
			{
				throw new FileNotFoundException();
			}

			File.Delete(buf);
		}

		private static void RenameFile(string name)
		{
			var buf = Path.Combine(path, name);

			if (!File.Exists(buf))
			{
				throw new FileNotFoundException();
			}

			name = Input("Enter new name:");// its ok

			if (buf != Path.Combine(path, name))
			{
				File.Move(buf, Path.Combine(path, name));
			}
		}

		private static void RenameDir(string name)
		{
			var buf = Path.Combine(path, name);

			if (!Directory.Exists(buf))
			{
				throw new DirectoryNotFoundException();
			}

			name = Input("Enter new name:");// its ok

			if (buf != Path.Combine(path, name))
			{
				Directory.Move(buf, Path.Combine(path, name));
			} 
		}

		public static void PrintFilesAndDirs()
		{
			Console.ForegroundColor = ConsoleColor.Yellow;
			Directory.GetFiles(path).ToList<string>().ForEach(i => Console.WriteLine(Path.GetFileName(i)));
			Console.ResetColor();
			Directory.GetDirectories(path).ToList<string>().ForEach(i => Console.WriteLine(Path.GetFileName(i)));
			Console.WriteLine();
		}

		public static void CreateDir(string name)
		{
			Directory.CreateDirectory(Path.Combine(path, name));
		}

		private static string Input(dynamic output, bool newLine = true)
		{
			Console.WriteLine(output);
			var fkkn = Console.ReadLine();
			if (newLine) { Console.WriteLine(); }
			return fkkn;
		}
	}
}
