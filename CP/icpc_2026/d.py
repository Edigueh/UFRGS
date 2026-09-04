import os
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


def flip(b: list[list[str]]):
    return tuple(row[::-1] for row in b)


def rotate(b: list[list[str]]):
    return tuple("".join(x) for x in zip(*b[::-1]))

def solve(tc: int):
    n, _ = IN_MAP_INT()

    a = tuple((input().rstrip('\r\n')) for _ in range(n))
    b = a

    ans: int = 0

    for _ in range(4):
        if a == b:
            ans += 1

        b_flipped = flip(b)

        if a == b_flipped:
            ans += 1

        b = rotate(b)

    print(ans)
            

def main():
    t: int = 1
    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
