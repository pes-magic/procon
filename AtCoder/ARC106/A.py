n = int(input())
f = False
for i in range(1, 60):
  for j in range(1, 60):
    if not f and 3**i + 5**j == n:
      print(f'{i} {j}')
      f = True

if not f:
  print(-1)
