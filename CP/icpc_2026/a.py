import sys

sys.setrecursionlimit(2000000)


input = sys.stdin.readline
def print(*args, sep=" ", end="\n"):
    sys.stdout.write(sep.join(map(str, args)) + end)

def IN_INT(): return int(input())
def IN_STR(): return input().rstrip()
def IN_ARR_INT(): return list(map(int, input().split()))
def IN_ARR_STR(): return input().split()
def IN_MAP_INT(): return map(int, input().split())

def solve(tc: int):
    n: int = IN_INT()

    c, v = [0] * 100100, [0] * 100100
    for i in range(1, n + 1):
        c[i], v[i] = IN_MAP_INT()
        c[i] += c[i-1]
        v[i] += v[i-1]

    q: int = IN_INT()

    for i in range(q):
        j: int = IN_INT()
        print("NEUTRO" if c[j] == v[j] else "VENDA" if c[j] < v[j] else "COMPRA")


def main():
    t: int = 1
    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
