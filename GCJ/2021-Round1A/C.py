from fractions import Fraction

def solve():
    N, Q = map(int, input().split())
    ans = []
    score = []
    for i in range(N):
        a, b = input().split()
        ans.append(a)
        score.append(int(b))
    if N <= 2:
        s = ''
        a = 0
        for i in range(N):
            if score[i] >= Q - score[i]:
                if a < score[i]:
                    a = score[i]
                    s = ans[i]
            else:
                if a < Q - score[i]:
                    a = Q - score[i]
                    s = ''.join(['T' if c == 'F' else 'F' for c in ans[i]])
        return s, a, 1
    abc = []
    ab = []
    bc = []
    ca = []
    for i in range(Q):
        if ans[0][i] == ans[1][i] and ans[1][i] == ans[2][i]:
            abc.append(i)
        elif ans[0][i] == ans[1][i]:
            ab.append(i)
        elif ans[1][i] == ans[2][i]:
            bc.append(i)
        else:
            ca.append(i)
    comb = [[0] * 121 for i in range(121)]
    for i in range(121):
        comb[i][0] = comb[i][i] = 1
        for j in range(1, i):
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1]
    all = 0
    ex_abc = 0
    ex_ab = 0
    ex_bc = 0
    ex_ca = 0
    for i in range(len(abc)+1):
        if i > score[0]:
            break
        for j in range(len(ab)+1):
            if i+j > score[0]:
                break
            for k in range(len(ca)+1):
                if i+j+k > score[0]:
                    break
                l = score[0]-i-j-k
                if l > len(bc):
                    continue
                if i+j+len(ca)-k+len(bc)-l != score[1]:
                    continue
                if i+len(ab)-j+k+len(bc)-l != score[2]:
                    continue
                base = comb[len(abc)][i] * comb[len(ab)][j] * comb[len(bc)][l] * comb[len(ca)][k]
                all += base;
                if abc:
                    ex_abc += i * base
                if ab:
                    ex_ab += j * base
                if ca:
                    ex_ca += k * base
                if bc:
                    ex_bc += l * base
    ex = [Fraction(0, 1)] * Q
    for i in abc:
        ex[i] = Fraction(ex_abc, len(abc) * all)
    for i in ab:
        ex[i] = Fraction(ex_ab, len(ab) * all)
    for i in bc:
        ex[i] = Fraction(ex_bc, len(bc) * all)
    for i in ca:
        ex[i] = Fraction(ex_ca, len(ca) * all)
    value = Fraction(0, 1)
    result = ''
    for i in range(Q):
        if ex[i] >= Fraction(1, 2):
            result += ans[0][i]
            value += ex[i]
        else:
            result += 'F' if ans[0][i] == 'T' else 'T'
            value += Fraction(1, 1) - ex[i]
    return result, value.numerator, value.denominator

T = int(input())
for i in range(T):
    ans, a, b = solve()
    print(f'Case #{i+1}: {ans} {a}/{b}')
