"""
http://code.google.com/codejam/contest/351101/dashboard#s=p0
"""
import sys


def solve_case(C, L):
    """
    >>> solve_case(100, [5, 75, 25])
    [2, 3]
    >>> solve_case(100, [5, 75, 75])
    >>> solve_case(100, [5, 50, 75, 25])
    [3, 4]
    >>> solve_case(100, [5, 50, 75, 25, 50])
    [2, 5]
    """
    items = set(L)
    for price in L:
        price_second = C - price
        if price_second == price:
            if L.count(price) < 2:
                continue
            else:
                a = L.index(price) + 1
                b = L.index(price, a) + 1
                return [a, b]
        if price_second in items:
            return sorted([L.index(price_second) + 1,
                           L.index(price) + 1])


def read_cases(inp):
    cases = []
    N = int(inp.readline().strip())
    for n in range(N):
        C = int(inp.readline())
        I = int(inp.readline())
        L = map(int, inp.readline().strip().split())
        assert len(L) == I, 'Bad input in case %d' % (n+1)
        cases.append((C, L))
    return cases


def main():
    cases = read_cases(sys.stdin)
    for x, case in enumerate(cases, 1):
        result = solve_case(*case)
        if result:
            a, b = result
            print 'Case #%d: %d %d' % (x, a, b)


if __name__ == '__main__':
    main()


