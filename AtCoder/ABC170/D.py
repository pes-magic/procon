N = int(input())
A = list(map(int, input().split()))
A.sort()
check = [0] * 1000001
res = 0
for i in range(N):
    if check[A[i]]:
        continue
    if i == N-1 or A[i] != A[i+1]:
        res += 1
    for j in range(A[i], 1000001, A[i]):
        check[j] = 1
print(res)