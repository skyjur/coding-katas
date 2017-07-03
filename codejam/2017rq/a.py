import string
import argparse

H = '+'
S = '-'

T = string.maketrans('+-', '-+')


def flip(s, start, K):
    """
    >>> flip('+++---', 0, 3)
    '------'
    >>> flip('+++---', 1, 3)
    '+--+--'
    """
    return s[:start] + s[start:start+K].translate(T) + s[start+K:]


def solve(case):
    cakes, K = case
    n = len(cakes)
    j = 0

    for i in range(n - K + 1):
        if cakes[i] == '-':
            j += 1
            cakes = flip(cakes, i, K)

    if '-' in cakes:
        return 'IMPOSSIBLE'
    else:
        return j


def parse_cases(inp):
    for ln in list(inp)[1:]:
        ln = ln.strip().split()
        yield ln[0], int(ln[1])


def format_result(i, r):
    return 'Case #%d: %s\n' % (i, r)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file_name')
    parser.add_argument('--case', default=None, type=int,
                        help='Only solve this case number')
    args = parser.parse_args()

    inp_fname = args.input_file_name
    assert inp_fname.endswith('.in'), inp_fname
    out_fname = inp_fname.replace('.in', '.out')

    with open(inp_fname) as inp, open(out_fname, 'w') as out:
        for i, case in enumerate(parse_cases(inp), 1):
            if args.case and args.case != i:
                continue
            print('Case #%d:' % i)
            print('  Input: %s' % (case, ))
            result = solve(case)
            print('  Result: %s' % (result, ))
            print('')
            out.write(format_result(i, result))


if __name__ == '__main__':
    main()