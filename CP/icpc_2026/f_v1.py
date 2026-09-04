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

    f, inv = [0] * (n+1), [0] * (n+2)

    f[1] = 2
    inv[2] = 1

    for i in range(2, n+1):
        if inv[i] != 0:
            f[i] = 3 * inv[i]
        else:
            f[i] = f[i-1] + 1
        if f[i] <= n:
            inv[f[i]] = i

    print(f[n])


def main():
    t: int = 1
    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
