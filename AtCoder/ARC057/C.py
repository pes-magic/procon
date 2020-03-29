def get_input():
    try:
        return int(input())
    except:
        return None


def solve(N):
    a2 = N**2
    b2 = (N+1)**2
    zero_a = True
    zero_b = True
    av = []
    bv = []
    az = []
    bz = []
    while a2 > 0 or b2 > 0:
        av.append(a2%100)
        bv.append(b2%100)
        az.append(zero_a)
        bz.append(zero_b)
        a2 //= 100
        b2 //= 100
        zero_a &= (av[-1] == 0)
        zero_b &= (bv[-1] == 0)
    av.reverse()
    bv.reverse()
    az.reverse()
    bz.reverse()
    dif = 0
    res = 0
    for i in range(len(av)):
        dif = min(1000, 100*dif + bv[i] - av[i])
        res = 100 * res + av[i]
        if az[i]:
            return res
        if (dif == 1 and not bz[i]) or dif >= 2:
            return res+1
    return res


while True:
    N = get_input()
    if N == None:
        break
    print(solve(N))
