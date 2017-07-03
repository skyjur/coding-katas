from __future__ import print_function
import sys


COLOR_BITS = {
    'R': 1,
    'Y': 2,
    'B': 4,
    'O': 1+2,
    'G': 2+4,
    'V': 1+4
}

COLOR_NAMES = 'ROYGBV'


def check(r):
    for i in range(-1, len(r)-1):
        a,b = COLOR_BITS[r[i]], COLOR_BITS[r[i+1]]
        if a&b:
            raise Exception('%s at %d (%s & %s)' % (r, i, a, b))
    

def solve(N, roygbv):
    r = ''
    roygbv = list(roygbv)
    l = [0, 1, 2, 3, 4, 5]

    left = right = 0

    while any(roygbv):
        if r:
            l.sort(key=lambda x: COLOR_NAMES[x] != r[0])
        l.sort(key=roygbv.__getitem__, reverse=True)
        
        for i in l:
            if roygbv[i]:
                c = COLOR_NAMES[i]
                middle = COLOR_BITS[c]
                if not left & middle:
                    r += c
                    roygbv[i] -= 1
                    left = COLOR_BITS[c]
                    break
        else:
            return 'IMPOSSIBLE'

    return r


def solve2(N, roygbv):
    R, O, Y, G, B, V = roygbv
    if (R>(Y+B) or Y>(R+B) or B>(R+Y)):
        return

    left = right = 0

    if len(r) == N:
        return r

    if r:
        left = COLOR_BITS[r[-1]]
        if len(r) == N-1:
            right = COLOR_BITS[r[0]]
    
    #print(' ', r + '.' * (N-len(r)), roygbv, [left, right])
    #a, b, c, d, e, f = ('......' + r)[-6:]

    l = sorted([0, 1, 2, 3, 4, 5], key=lambda x: r.rfind(COLOR_NAMES[x]))

    for i in l:
        if roygbv[i] > 0:
            c = COLOR_NAMES[i]
            middle = COLOR_BITS[c]
            if not ((left & middle) or (middle & right)):
                roygbv1 = list(roygbv)
                roygbv1[i] -= 1
                r1 = solve(N, roygbv1, r + c)
                if r1:
                    return r1


def main():
    fin = sys.argv[1]
    assert '.in' in fin
    fout = fin.replace('.in', '.out')

    out = open(fout, 'w')
    i = 1

    for ln in list(open(fin))[1:]:
        N, R, O, Y, G, B, V = list(map(int, ln.strip().split()))
        case = (N, (R, O, Y, G, B, V))

        print('=' * 80)
        print('Input:', case)

        r = solve(*case) or 'IMPOSSIBLE'

        try:
            check(r)
        except:
            r = 'IMPOSSIBLE'

        print('Result:', r)

        out.write('Case #%d: %s\n' % (i, r))

        i+=1


if __name__ == '__main__':
    main()