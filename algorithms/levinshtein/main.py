"""
>>> lev('kitten', 'sitten')
1
>>> lev('katten', 'sitten')
2
>>> lev('sittin', 'sitting')
1
>>> lev('kitten', 'sitting')
3
"""


def lev(a, b):
    if len(a) == 0:
        return len(b)
    if len(b) == 0:
        return len(a)

    cost = int(a[-1] != b[-1])

    return min((
        lev(a[:-1], b) + 1,
        lev(a, b[:-1]) + 1,
        lev(a[:-1], b[:-1]) + cost
    ))
