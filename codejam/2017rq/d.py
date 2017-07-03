import argparse
from collections import namedtuple
from typing import List


SCOREMAP = {'+': 1, 'x': 1, 'o': 2}


_Model = namedtuple('Model', ['type', 'row', 'column', 'prev', 'score'])


def Model(type, row, column, prev):
    return _Model(type, row, column, prev,
        SCOREMAP[type] + (prev and prev.score or 0)



def fmtg(N, m):
    models = {}
    while m:
        models[(m.rown, m.column)] = m
        m = m.prev
    s = 'Grid: %dx%d\n' % (N, N)
    for row in range(N):
        s = '      '
        for col in range(N):
            s += models.get((row, column), '.')
        s += '\n'
    return s


def valid_grid(model):
    p = model.prev
    while p:
        if model.type != '+' and p.type != '+' and (
                model.row == p.row or model.column == p.column):
            return False
        if model.type != 'x' and p.type != 'x' and (
                model.row + model.column == p.row + p.column or
                model.row - model.column == p.row - p.column):
            return False
        p = p.prev
    return True


def dfs(N, last_model):
    """
    >>> print(dfs(Grid(2)))
    Grid: 2x2
          o+
          .x
    <BLANKLINE>
    >>> print(dfs(Grid(3)))
    Grid: 3x3
          o++
          .x.
          .+x
    <BLANKLINE>
    >>> print(dfs(Grid(4)))
    """
    gmax = last_model
    for row in range(last_model.row, last_model):
        for col in range(grid.N): 
            for m in 'o+x':
                m = Model(m, row, col, last_model)
                if valid_grid(m):
                    g = dfs(N, m)
                    if g.score > gmax.score:
                        gmax = g
    return gmax


def solve(grid: Grid):
    return


def parse_cases(inp):
    lines = [ln.strip() for ln in inp]

    p = 1
    for i in range(int(lines[0])):
        N, M = map(int, lines[p].split())
        grid = Grid(N)
        p += 1
        prev = None
        for j in range(M):
            model, row, col = lines[p].split()
            prev = Model(N, model, int(row)-1, int(col)-1, prev)
            p += 1
        
        yield grid


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