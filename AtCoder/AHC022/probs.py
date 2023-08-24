# Importing numpy library again
import numpy as np
from scipy.stats import norm


def prob1(i, s):
    prob = norm.cdf(0.5 + i, scale=s * s) - norm.cdf(-0.5 + i, scale=s * s)
    # if prob == 0.0:
    #     return -10.0 * i
    return round(prob, 12)


def prob2(i, s):
    prob = norm.cdf(0.5 - i, scale=s * s)
    # if prob == 0.0:
    #     return -10.0 * i
    return round(prob, 12)


prob_one = []
prob_half = []

for s in range(1, 31):
    prob_one.append([prob1(i, s) for i in range(0, 1001)] + [prob2(1000, s)])

print("[")
for v in prob_one:
    print(f"    {v},")
print("];")
