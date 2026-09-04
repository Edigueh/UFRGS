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

    pot: int = 1

    while pot * 3 <= n:
        pot *= 3

    if n <= 2 * pot:
        ans = 2 * pot + (n - pot)
    else:
        ans = pot * 3 + 3 * (n - 2 * pot)

    print(ans)

def main():
    t: int = 1
    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
