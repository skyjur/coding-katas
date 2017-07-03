import sys
from collections import namedtuple
from math import pi


class Cake:
    def __init__(self, r, h):
        self.r=r
        self.h=h
    
    def side(self):
        return 2.0 * pi * self.r * self.h

    def top(self):
        return pi * self.r * self.r 


def solve(n, k, cakes):
    cakes = sorted(cakes, key=lambda c: c.r, reverse=True)
    base = cakes[0]
    smaller = cakes[1:]
    s = base.side() + base.top()
    smaller.sort(key=lambda x: x.h, reverse=True)
    for c in smaller[:k-1]:
        s += c.side()
    return s


def main():
    lines = [map(int, ln.strip().split()) for ln in open(sys.argv[1])]
    out = open(sys.argv[1].replace('.in', '.out'), 'w')
    N = lines[0][0]
    p=0
    for i in range(N):
        p += 1
        n, k = lines[p]
        cakes = []
        for j in range(n):
            p += 1
            r, h = lines[p]
            cakes.append(Cake(r, h))
        out.write('Case #%d: %.8f\n' % (i+1, solve(n, k, cakes)))



if __name__ == '__main__':
    main()