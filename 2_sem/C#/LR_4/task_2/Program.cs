using System.Runtime.InteropServices;


namespace task_2
{
	class dll
	{
		//2 DLLs in project folder (x64 and x86)
		[DllImport("D:\\BSUIR\\Tapping\\C#\\LR_4\\task_2\\Dll1-x64.dll")] // lay the way to DLL
		public static extern void dllact();
	}
	class Program
	{
		static void Main()
		{
			dll.dllact(); //random act
		}              
	}
}