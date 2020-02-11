N, K = map(int, input().split())
A = list(map(int, input().split()))
res = 0
sum = 0
for i in range(N):
    sum += A[i]
    if i-K >= 0:
        sum -= A[i-K]
    res = max(res, sum)
print(0.5*(res+K))
