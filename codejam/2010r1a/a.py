"""
>>> l, r = lr(4, "..R. ..B. .RB. BRBR".split())
>>> ' '.join(l)
'R... B... RB.. BRBR'
>>> ' '.join(r)
'...R ...B ..RB BRBR'
>>> ' '.join(diags(2, '12 34'.split()))
'14 23'
>>> ' '.join(diags(3, '123 456 789'.split()))
'48 68 159 357 26 24'
>>> ' '.join(cols(2, '12 34'.split()))
'13 24'
>>> solve(3, 3, 'xxR xRx Rxx'.split())
'Red'
>>> find(3, 'R.. .R. ..R'.split(), 'R')
True
>>> find(2, '.R. ..R ...'.split(), 'R')
True
>>> find(2, 'R.. ..R .R.'.split(), 'R')
True
>>> find(2, 'R.R ... R.R'.split(), 'R')
False
>>> solve(3, 3, '..R BRB BRR'.split())
'Red'
"""
import sys


def main():
    lines = [s.strip() for s in open(sys.argv[1])]
    n = int(lines[0])
    i = 1
    for j in range(n):
        n, k = map(int, lines[i].split())
        i += 1
        block = lines[i:i+n]
        i += n
        r = solve(n, k, block)
        print 'Case #%d: %s' % (j+1, r)


def solve(n, k, block):
    l, r = lr(n, block)

    red = 0
    blue = 0

    # lns = l + r
    # lns += cols(n, l)
    # lns += cols(n, r)
    # lns += diags(n, l)
    # lns += diags(n, r)

    # for ln in lns:
    #     if 'R' * k in ln:
    #         red += 1
    #     if 'B' * k in ln:
    #         blue += 1
    red = find(k, r, 'R')## + find(k, r, 'R')
    blue = find(k, r, 'B')## + find(k, r, 'B')
    
    if red and blue:
        return 'Both'
    elif red:
        return 'Red'
    elif blue:
        return 'Blue'
    else:
        return 'Neither'



def lr(n, block):
    block = [ln.replace('.', '') for ln in block]
    l = [ln + ('.' * (n-len(ln))) for ln in block]
    r = [('.' * (n-len(ln))) + ln for ln in block]
    return l, r


def cols(n, block):
    return [
        ''.join(ln) for ln in
        zip(*block)
    ]


def diags(n, block):
    dl = []

    for i in range(-n, n):
        l1 = ''
        l2 = ''
        for y in range(n):
            x = y + i
            if 0 <= x < n:
                l1 += block[y][x]
                l2 += block[y][n-x-1]
        if len(l1) > 1:
            dl.append(l1)
            dl.append(l2)
    
    return dl


def find(k, block, c):
    dirs = [(1, 0), (0, 1), (1, 1), (-1, 1)]
    n = len(block)
    # print 'block', block
    for y in range(n):
        for x in range(n):
            if block[y][x] == c:
                for dx, dy in dirs:
                    x1 = x
                    y1 = y

                    # print '-' * 80
                    # print '%d x %d' % (x, y), 'dx dy:', dx, dy
                
                    s = ''
                    while (0 <= x1 < n) and (0 <= y1 < n) and len(s) < k:
                        # print '%d x %d' % (x1, y1), s
                        s += block[y1][x1]
                        x1 += dx
                        y1 += dy
                    # print '%d x %d' % (x1, y1), s
                    if s == c * k:
                        return True
    return False


if __name__ == '__main__':
    main()