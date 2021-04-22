from RBTree import RBTree
import random

def main() -> None:
    rbt = RBTree()

    #l = [-15, -6, 1, 2, 18, 17, 3, 12, -9, -4, -10]
    l = [17, 25, 6, 3, 1, 8, 36, 4, 12, 39, 30, 28, 0, 24]
    for i in l:#range(15):
        #l.append(random.randrange(0, 42))
        rbt.add(i)

        print("\n\nafter adding", i, ":\n\n")
        rbt.print(5)
    
    print(l, '\n')
    rbt.print(5)

    print(rbt.traversal())

    pass

if __name__ == '__main__':
    main()