using System.Text;

namespace Program
{
    public class Program
    {
        private static readonly string EncodedFilePath = "encoded.txt";
        private static readonly string DecodedFilePath = "decoded.txt";

        private static (string, Action<string[]>)[] commands = new (string, Action<string[]>)[]
        {
            ("help", PrintHelp),
            ("caesar", Caesar),
            ("vigenere", Vigenere),
        };

        private static string[][] helpMessages = new string[][]
        {
            new string[] { "help", "prints the help screen"},
            new string[] { "caesar", "encode/decode caesar cipher with key in range[0, 26]" },
            new string[] { "vigenere", "encode/decode vigenere cipher with key" },
        };

        private static string[] CodingModes = new string[]
        {
            "encode",
            "decode",
        };

        public static void Main(string[] args)
        {
            args = "vigenere encode abiba".Split();

            if (args.Length != 3 || args[0] == commands[0].Item1)
            {
                PrintHelp(args);
                return;
            }

            const int commandIndex = 0;
            var command = args[commandIndex];

            var index = Array.FindIndex(commands, i => i.Item1.Equals(command, StringComparison.InvariantCultureIgnoreCase));

            if (index >= 0)
            {
                const int parametersIndex = 1;
                commands[index].Item2(args[parametersIndex..]);
            }
            else
            {
                PrintHelp(args);
                return;
            }
        }

        private static void PrintHelp(string[] args)
        {
            Console.WriteLine("commands:");
            foreach (var helpMessage in Program.helpMessages)
            {
                Console.WriteLine("\t{0,-10}\t- {1}.", helpMessage[0], helpMessage[1]);
            }
        }

        private static void Caesar(string[] parameters)
        {
            if (!byte.TryParse(parameters[^1], out var key) || key > 26 || key < 0)
            {
                Console.WriteLine("invalid key.");
            }

            var mode = parameters[0];

            if (!Program.CodingModes.Contains(mode))
            {
                PrintHelp(parameters);
                return;
            }

            string fileToReadPath = Program.DecodedFilePath,
                   fileToWritePath = Program.EncodedFilePath;

            if (mode.Equals("decode", StringComparison.InvariantCultureIgnoreCase))
            {
                (fileToReadPath, fileToWritePath) = (fileToWritePath, fileToReadPath);
            }

            using var readingStream = new StreamReader(fileToReadPath, Encoding.UTF8);
            using var writingStram = new StreamWriter(fileToWritePath, false, Encoding.UTF8);

            int readed;
            char symbol;
            var sb = new StringBuilder();
            while ((readed = readingStream.Read()) > 0)
            {
                symbol = Convert.ToChar(readed);
                symbol = ShiftAlphabetSymbol(symbol, key, mode);
                writingStram.Write(symbol);
            }

            writingStram.Flush();
        }

        private static void Vigenere(string[] parameters)
        {
            var key = parameters[^1];
            var mode = parameters[0];

            if (!Program.CodingModes.Contains(mode))
            {
                PrintHelp(parameters);
                return;
            }

            string fileToReadPath = Program.DecodedFilePath,
                   fileToWritePath = Program.EncodedFilePath;

            if (mode.Equals("decode", StringComparison.InvariantCultureIgnoreCase))
            {
                (fileToReadPath, fileToWritePath) = (fileToWritePath, fileToReadPath);
            }

            using var readingStream = new StreamReader(fileToReadPath, Encoding.UTF8);
            using var writingStram = new StreamWriter(fileToWritePath, false, Encoding.UTF8);

            int readed;
            char symbol;
            var sb = new StringBuilder();
            int count = 0;
            while ((readed = readingStream.Read()) > 0)
            {
                symbol = Convert.ToChar(readed);
                symbol = ShiftAlphabetSymbol(symbol, IndexInAlphabet(key[count]), mode);
                writingStram.Write(symbol);
                count = (count + 1) % key.Length;
            }

            writingStram.Flush();
        }

        private static byte IndexInAlphabet(char symbol)
        {
            symbol = char.ToLower(symbol);
            return (byte)(symbol - 'a');
        }

        private static char ShiftAlphabetSymbol(char symbol, byte key, string codingMode)
        {
            var ranges = new int[][]
            {
                new int[] { 97, 122 },
                new int[] { 65, 90 },
            };

            int code = (int)symbol;

            foreach (var range in ranges)
            {

                if (code >= range[0] && code <= range[1])
                {
                    code -= range[0];
                    code += codingMode switch
                    {
                        "encode" => key,
                        "decode" => -key,
                        _ => 0,
                    };

                    var len = range[1] - range[0] + 1;
                    if (code < 0)
                    {
                        code += len;
                    }
                    code %= len;
                    code += range[0];

                    break;
                }
            }

            return (char)code;
        }
    }
}
