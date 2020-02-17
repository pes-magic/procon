a,b,c = map(int, input().split())
print('Yes' if (a==b and b!=c) or (b==c and c!=a) or (c==a and a!=b) else 'No')