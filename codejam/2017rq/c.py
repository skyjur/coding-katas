import sys
import argparse
from heapq import heappush, heappop
from collections import deque


def split(n):
    """
    >>> split(7)
    (3, 3)
    >>> split(8)
    (3, 4)
    >>> split(1)
    (0, 0)
    """
    return n - (n // 2) - 1, n // 2


def solve2(case):
    (N, K) = case
    q = [-N]
    for i in range(K):
        n2 = -sorted(q)[0]
        n = -heappop(q)
        assert n2 == n, (n2, n, q)
        left, right = split(n)
        assert left <= right
        if right > 0:
            heappush(q, -right)
        if left > 0:
            heappush(q, -left)
        if n == 0:
            break
    r2 = solve2((N, K))
    assert r2 == (right, left), (r2, (right, left))
    return right, left


def solve(case):
    (N, K) = case
    q = {N: 1}
    k = 0
    while k < K:
        n = max(q)
        i = q.pop(n)
        left, right = split(n)
        q[left] = q.get(left, 0) + i
        q[right] = q.get(right, 0) + i
        k += i
    return right, left


def parse_cases(inp):
    for ln in list(inp)[1:]:
        yield map(int, ln.strip().split())


def format_result(i, r):
    (a, b) = r
    return 'Case #%d: %d %d\n' % (i, a, b)


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
            print('  Input: %s' % case)
            result = solve(case)
            print('  Result: %s' % (result, ))
            print('')
            out.write(format_result(i, result))


if __name__ == '__main__':
    main()