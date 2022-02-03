using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text.Json;

namespace lab1
{
	internal class Program
	{
		[Serializable]
		internal class ExClass
		{
			public int intField { get; set; }
			public double doubleField { get; set; }
			public string stringField { get; set; }

            public Point p = new Point() { x = 5, y = 4f };

			public struct Point
            {
				public int x;
				public double y;
            }

			public ExClass() { }

			public ExClass(int intField, double doubleField, string stringField)
			{
				this.intField = intField;
				this.doubleField = doubleField;
				this.stringField = stringField;
			}
		}

		[Serializable]
		internal class MoreExClasses : IEnumerable
		{
			public List<ExClass> list { get; private set; }

			public MoreExClasses() { }

			public MoreExClasses(List<ExClass> list)
			{
				this.list = list;
			}

			public void JsonSerialize(string path)
			{
				
				var buf = JsonSerializer.Serialize(list, new JsonSerializerOptions() { WriteIndented = true });
				File.WriteAllText(path, buf);

				
			}

			public static MoreExClasses JsonDeserialize(string path)
			{
				var buf = File.ReadAllText(path);
				var list = JsonSerializer.Deserialize<List<ExClass>>(buf);

				return new MoreExClasses() { list = list };
			}

			public void BinarySerialize(string path)
			{
				using (FileStream fs = File.OpenWrite(path))
				{
					new BinaryFormatter().Serialize(fs, list);
				}
			}

			public static MoreExClasses BinaryDeserialize(string path)
			{
				var list = new List<ExClass>();

				using (FileStream fs = File.OpenRead(path))
				{
					list = (List<ExClass>)new BinaryFormatter().Deserialize(fs);
				}

				return new MoreExClasses() { list = list };
			}

			public IEnumerator GetEnumerator()
			{
				return list.GetEnumerator();
			}
		}

		static void Main()
		{
			try
			{
				var mec = new MoreExClasses(
					new List<ExClass>()
					{
					new ExClass(1, 5.5f, "h\\i"),
					new ExClass(2, 6.6f, "ag\\a"),
					new ExClass(3, 7.7f, @"b\rr")
					}
					);

                string command;
				//const int offset = -25;
				//string format = "{0," + offset + "}{1}";
				string format = "{0,-25}{1}";

				while (true)
				{
					Console.Write(Commands.path + ">");
                    command = Console.ReadLine().Trim();
					command = command.ToLower();
					Console.WriteLine();

					try
					{
						switch (command)
						{
							case ("help"):
								{
									Console.WriteLine(format, "copy", "copy the existing file or directory");
									Console.WriteLine(format, "cut", "cut the existig file or directory");
									Console.WriteLine(format, "paste", "paste the file or directory");
									Console.WriteLine(format, "dir", "show the directory contents");
									Console.WriteLine(format, "cls", "clear the console");
									Console.WriteLine(format, "mount", "choose new existing current directory");
									Console.WriteLine(format, "rename", "rename the existing file or directory");
									Console.WriteLine(format, "zip", "zip the existing file or directory");
									Console.WriteLine(format, "unzip", "unzip the existing file or directory");
									Console.WriteLine(format, "delete", "delete the existing file or directory");
									Console.WriteLine(format, "create file", "create file");
									Console.WriteLine(format, "create dir", "create dir");
									Console.WriteLine(format, "targeting", "change the way of choosing needed file or directory");
									Console.WriteLine(format, "read", "read class from existing file");
									Console.WriteLine(format, "write", "write class to file");

									break;
								}
							case ("targeting"):
								{
									Commands.ChangeTargeting();

									break;
								}
							case ("cls"):
								{
									Commands.Cls();

									continue;
									//break;
								}
							case ("unzip"):
								{
									Commands.Unzip();

									break;
								}
							case ("zip"):
								{
									Commands.Zip();

									break;
								}
							case ("rename"):
								{
									Commands.Rename();

									break;
								}
							case ("delete"):
								{
									Commands.Delete();

									break;
								}
							case ("create file"):
								{
									Commands.CreateFile(Input("Enter name of file to create:"));

									break;
								}
							case ("create dir"):
								{
									Commands.CreateDir(Input("Enter the name of dir to create:"));

									break;
								}
							case ("paste"):
								{
									Commands.Paste();

									break;
								}
							case ("copy"):
								{
									Commands.Copy();

									break;
								}
							case ("cut"):
								{
									Commands.Cut();

									break;
								}
							case ("mount"):
								{
									Commands.Mount();

									break;
								}
							case ("dir"):
								{
									Commands.PrintFilesAndDirs();

									break;
								}
							case ("write"):
								{
									Commands.WriteClassToFile(in mec);

									break;
								}
							case ("read"):
								{
									Commands.ReadClassFromFile(out mec);

									break;
								}
							default:
								{
									throw new Exception("Invalid command!");
								}
						}

					}
                    catch (DirectoryNotFoundException)
                    {
                        Console.WriteLine("Directory not found!");
                    }
                    catch (FileNotFoundException)
                    {
                        Console.WriteLine("File not found!");
                    }
                    catch (FileLoadException)
                    {
                        Console.WriteLine("Error to load file!");
                    }
                    catch (Exception ex)
					{
						Console.WriteLine(ex.Message);
					}

					Console.WriteLine("\n\n");
				}
			}
			catch (Exception ex)
			{
				Console.WriteLine(ex.Message);
			}
		}		

		static string Input(dynamic output, bool newLine = true)
		{
			Console.WriteLine(output);
			var fkkn = Console.ReadLine();
			if (newLine) { Console.WriteLine(); }
			return fkkn;
		}		
	}
}