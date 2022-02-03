from enum import Enum
from typing import Union
from colorama import Fore

class Color(Enum):
    Black = 0
    Red = 1

class Node:
    d: Union[int, float] = None
    l = None
    r = None
    p = None
    c: Color = Color.Red

    def __init__(self, el: Union[int, float]) -> None:
        self.d = el

    def grandparent(self):
        if self.p and self.p.p:
            return self.p.p
        return None

    def uncle(self):
        g = self.grandparent()

        if g is None:
            return None
        if g.l == self.p:
            return g.r
        else:
            return g.l

    def rotate_left(node):
        piv = node.r
        piv.p = node.p

        if node.p is not None:
            if node.p.l == node:
                node.p.l = piv
            else:
                node.p.r = piv

        node.r = piv.l
        if piv.l is not None:
            piv.l.p = node

        node.p = piv
        piv.l = node

    def rotate_right(node):
        piv = node.l
        piv.p = node.p

        if node.p is not None:
            if node.p.l == node:
                node.p.l = piv
            else:
                node.p.r = piv

        node.l = piv.r
        if piv.r is not None:
            piv.r.p = node

        node.p = piv
        piv.r = node

    def insert_case1(node):
        if node.p is None:
            node.c = Color.Black
        else:
            Node.insert_case2(node)

    def insert_case2(node):
        if node.p.c == Color.Black:
            return
        else:
            Node.insert_case3(node)

    def insert_case3(node):
        u = node.uncle()

        if u is not None and u.c == Color.Red:
            node.p.c = Color.Black
            u.c = Color.Black
            g = node.grandparent()
            g.c = Color.Red
            Node.insert_case1(g) 
        else:
            Node.insert_case4(node)

    def insert_case4(node):
        g = node.grandparent()
 
        if node == node.p.r and node.p == g.l:
            Node.rotate_left(node.p)
            node = node.l
            #node.l.insert_case5()
        elif node == node.p.l and node.p == g.r:
            Node.rotate_right(node.p)
            node = node.r
            #node.r.insert_case5()
        Node.insert_case5(node)

    def insert_case5(node):
        g = node.grandparent()

        node.p.c = Color.Black
        g.c = Color.Red

        if node == node.p.l and node.p == g.l:
            Node.rotate_right(g)
        else:
            Node.rotate_left(g)

    def print(self, indent: int, depth: int = 0) -> None:
        if self.r is not None:
            (self.r).print(indent, depth + 1)
        print(Fore.RED if self.c == Color.Red else "",' '*depth*indent, self.d, Fore.WHITE,'\n')
        #print(' '*depth, self.d, '\n')
        if self.l is not None:
            (self.l).print(indent, depth + 1)

    def add_to_list(self, l: list):
        if self.l is not None:
            self.l.add_to_list(l)
        l.append(self.d)
        if self.r is not None:
            self.r.add_to_list(l)
        


class RBTree:
    root: Node = None
    def __init__(self):
        pass

    def traversal(self, back: bool = False):
        l = []
        self.root.add_to_list(l)    

        if back:
            l.reverse()

        return l


    def add(self, el: Union[int, float]) -> None:
        n = Node(el)
        if self.root is None:
            self.root = n
        else:
            c = self.root

            while True:
                if el > c.d:
                    if c.r is not None:
                        c = c.r
                    else:
                        c.r = n
                        n.p = c
                        break
                elif el < c.d:
                    if c.l is not None:
                        c = c.l
                    else:
                        c.l = n
                        n.p = c
                        break
                else:
                    break

        n.insert_case1()

        while self.root.p is not None:
            self.root = self.root.p

    def print(self, indent: int = 4):
        if self.root is not None:
            self.root.print(indent)
