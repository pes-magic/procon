def get_input():
    try:
        return input()
    except:
        return None


def solve(N):
    a = int(N[0]) if N[0] != '0' else 10
    for i in range(1, len(N)):
        if N[i] != '0':
            N = N[i:]
            break
        a *= 10
    else:
        return [a, 1]
    b = 0
    for i in range(len(N)):
        b = 10 * b + int(N[i])
        if a >= b:
            continue
        j = i + 1
        d = (b - a)
        c = b
        valid = True
        while valid and j < len(N):
            c += d
            s = str(c)
            for k in s:
                if k != N[j]:
                    valid = False
                    break
                j += 1
                if j == len(N):
                    break
        if valid:
            return [a, d]
    sa = str(a)
    sb = str(b)
    if len(sa) == len(sb):
        return [a, 10*b-a]
    else:
        for i in range(len(sb)):
            if int(sa[i]) > int(sb[i]):
                for j in range(len(sa)-len(sb)+1):
                    b = 10 * b
                return [a, b-a]
            elif int(sa[i]) < int(sb[i]):
                for j in range(len(sa)-len(sb)):
                    b = 10 * b
                return [a, b-a]
    return [a, 1]


while True:
    N = get_input()
    if not N:
        break
    print(' '.join(map(str, solve(N))))
