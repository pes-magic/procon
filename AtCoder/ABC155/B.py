N = int(input())
print("APPROVED" if all([x%2 == 1 or x%3 == 0 or x%5 == 0 for x in map(int, input().split())]) else "DENIED")
