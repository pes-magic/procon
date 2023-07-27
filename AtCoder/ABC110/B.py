N,M,X,Y = map(int, input().split())
x=list(map(int, input().split())) + [X]
y=list(map(int, input().split())) + [Y]
print("No War" if max(x) < min(y) else "War")