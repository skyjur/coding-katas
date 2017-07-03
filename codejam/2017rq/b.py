"""
>>> solve(132)
129
>>> solve(1000)
999
>>> solve(7)
7
>>> solve(111111111111111110)
99999999999999999L
"""
import sys


def solve(N):
    n = len(str(N))
    prev = 0
    result = 0

    for i in range(n, 0, -1):
        d = N % 10**i / 10**(i-1)

        if d < prev:
            N -= N % 10**i + 1
            return solve(N)
        
        prev = d

    return N


def main():
    args = list(sys.argv)
    if len(args) == 1:
        args += ['a-test.in']
    lines = list(open(args[1]))
    outf = args[1].replace('.in', '.out')
    out = open(outf, 'w')
    for i, ln in enumerate(lines[1:], 1):
        N = int(ln.strip())
        r = solve(N)
        assert r <= N, (r, N)
        print('Case #%d: %d -> %d' % (i, N, r))
        out.write('Case #%d: %d\n' % (i, r))


if __name__ == '__main__':
    main()