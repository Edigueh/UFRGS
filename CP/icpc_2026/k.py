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

def worstcase(n, sumc, c, k):
    ret: int = 0
    for i in range(n):
        ret = max(ret, sumc - c[i] + k[i])

    return ret

def solve(tc: int):
    n = IN_INT()
    sumc = 0

    c = IN_ARR_INT()

    for i in range(n):
        sumc += c[i]

    k = IN_ARR_INT()

    for i in range(n):
        if k[i] > c[i]:
            print(-1)
            return

    print(worstcase(n, sumc, c, k))

def main():
    t: int = 1
    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
