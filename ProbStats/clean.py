from collections import Counter

inp = "82 70 77 72 71 80 72 72 70 77 70 72 102 72 76 77 82 80 82 95 72 76 95 71 80 83"

inp = list(map(int, inp.split(" ")))
inp.sort()

c = Counter(inp)

lower = 69.61906926
upper = 86.38093074

bounds = []
for v in inp:
    if lower <= v <= upper:
        bounds.append(v)

print(bounds)
print(len(bounds))
