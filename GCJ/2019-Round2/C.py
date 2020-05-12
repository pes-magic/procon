from fractions import Fraction

def solve(v):
    low = Fraction(0, 1)
    high = Fraction(2**40, 1)
    for i in range(len(v)-1):
        if v[i][1] < v[i+1][1]:
            if v[i][0] > v[i+1][0]:
                low = max(low, Fraction(v[i][0] - v[i+1][0], v[i+1][1] - v[i][1]))
        elif v[i][1] == v[i+1][1]:
            if v[i][0] >= v[i+1][0]:
                return "IMPOSSIBLE"
        else:
            if v[i][0] < v[i+1][0]:
                high = min(high, Fraction(v[i+1][0] - v[i][0], v[i][1] - v[i+1][1]))
            else:
                return "IMPOSSIBLE"
    if low >= high:
        return "IMPOSSIBLE"
    mid = (low + high) * Fraction(1, 2)
    l = 0
    h = mid.denominator
    while h - l > 1:
        m = (l+h)//2
        f = mid.limit_denominator(m)
        if low < f and f < high:
            h = m
        else:
            l = m
    return '{} {}'.format(h, (low.numerator * h)//low.denominator + 1)


T = int(input())
for t in range(T):
    N = int(input())
    v = []
    for i in range(N):
        a, b = map(int, input().split())
        v.append([a, b])
    print('Case #{}: {}'.format(t+1, solve(v)))
