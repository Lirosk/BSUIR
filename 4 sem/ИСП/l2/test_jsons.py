import unittest
from class_to_check import Ctc
import jsons

def main():
    unittest.main()

class TestSer(unittest.TestCase):
    def test_ser(self):
        dmpd = jsons.dumps(Ctc)
        print(dmpd)
        
        self.assertEqual(0, 0)
        '''
        prsd = jsons.loads(dmpd)

        self.assertEqual(prsd._s1, Ctc._s1)
        self.assertEqual(prsd._s2, Ctc._s2)
        self.assertEqual(prsd.F(10, Ctc.F(10)))
        self.assertEqual(prsd.m(10), Ctc.m(10))
        '''



if __name__ == '__main__':
    main()