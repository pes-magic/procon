N, K = map(int, input().split())
res = 0
while N > 0:
    N = N//K
    res += 1
print(res)
