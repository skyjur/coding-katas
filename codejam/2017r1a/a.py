from __future__ import print_function
import sys


def fill(case, c, ai, aj, bi, bj):
    for i in range(ai, bi+1):
        for j in range(aj, bj+1):
            if case[i][j] not in ('?', c):
                return False

    for i in range(ai, bi+1):
        for j in range(aj, bj+1):
            assert case[i][j] in ('?', c), case[i][j]
            case[i][j] = c

    return True
            


def solve(case):
    print('-- Input')
    print('\n'.join([''.join(r) for r in case]))

    d = {}
    R, C = len(case), len(case[0])

    for i, r in enumerate(case):
        for j, c in enumerate(r):
            if c != '?':
                assert c not in d
                d[c] = ((i, j), (i, j))

    for c, v in d.items():
        a,b=v
        ai,aj=a
        bi,bj=b
        while ai > 0 and fill(case, c, ai-1, aj, bi, bj):
            ai -= 1
        d[c] = ((ai,aj),(bi,bj))

    for c, v in d.items():
        a,b=v
        ai,aj=a
        bi,bj=b
        while aj > 0 and fill(case, c, ai, aj-1, bi, bj):
            aj -= 1
        d[c] = ((ai,aj),(bi,bj))

    for c, v in d.items():
        a,b=v
        ai,aj=a
        bi,bj=b
        while bi < R-1 and fill(case, c, ai, aj, bi+1, bj):
            bi += 1
        d[c] = ((ai,aj),(bi,bj))

    for c, v in d.items():
        a,b=v
        ai,aj=a
        bi,bj=b
        while aj > 0 and fill(case, c, ai, aj-1, bi, bj):
            aj -= 1
        d[c] = ((ai,aj),(bi,bj))

    for c, v in d.items():
        a,b=v
        ai,aj=a
        bi,bj=b
        while bj < C-1 and fill(case, c, ai, aj, bi, bj+1):
            bj += 1
        d[c] = ((ai,aj),(bi,bj))


    print('-- Otput')
    print('\n'.join([''.join(r) for r in case]))

    A=set(d.keys())
    B=set(c for row in case for c in row)
    assert A==B, (A,B)

    return '\n'.join([''.join(r) for r in case])


def main():
    fin = sys.argv[1]
    assert '.in' in fin
    fout = fin.replace('.in', '.out')
    fout = open(fout, 'w')
    lns = [ln.strip() for ln in open(fin)]
    lns.pop(0)
    i = 1
    while lns:
        R, C = lns.pop(0).split()
        case = [list(lns.pop(0)) for j in range(int(R))]
        print('Case #%d:' % i, file=fout)
        i+=1
        print(solve(case), file=fout)
    fout.close()


main()
