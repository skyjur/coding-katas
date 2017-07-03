from __future__ import print_function
import pprint


def solve(D, horses):
    maxt = 0

    for ki, si in horses:
        d = D - ki
        t = d / float(si)
        maxt = max(maxt, t)

    return '%.6f' % round(D / maxt, 6)


def main():
    f = 'A-large.in'
    assert '.in' in f
    fo = f.replace('.in', '.out')

    lines = [ln.strip() for ln in open(f)]
    out = open(fo, 'w')

    T = int(lines[0])

    i = 1
    for x in range(T):

        D, N = map(int, lines[i].split())
        i += 1
        horses = [
            (int(ki), int(si))
            for ki, si in
            [r.split() for r in lines[i:N+i]]
        ]
        i += N

        print('=' * 80)
        print('Case %d' % (x+1))
        print('')
        print('Input:')
        print(D)
        print(pprint.pformat(horses))

        r = solve(D, horses)

        print('Output:', r)

        out.write('Case #%d: %s\n' % (x+1, r))


if __name__ == '__main__':
    main()
