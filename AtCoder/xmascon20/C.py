from decimal import *

dig = 50
s5 = 0
for i in range(dig):
    next = 0
    for j in range(10):
        if (10*s5+j)**2 <= 10**(2*i)*5:
            next = 10*s5+j
    s5 = next

s5 -= 10**(dig-1)

def g(a):
    if a == 0:
        return 0
    v = []
    for i in range(-1,3):
        v.append(int(((a+i)*(10**(dig-1))*s5)//(2*(10**(2*(dig-1))))))
    if v[0] == v[1]:
        return 1 if v[2] == v[3] else 2
    return 0 if v[1] == v[2] else 1

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    s = 0
    for t in a:
        s ^= g(t)
    print("Black" if s > 0 else "White")
