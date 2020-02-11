s, t = input().split()
a, b = map(int, input().split())
d = {s: a, t: b}
d[input()] -= 1
print("{} {}".format(d[s], d[t]))
