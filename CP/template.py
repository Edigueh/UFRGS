import os
import sys

# 1. OPTIMIZATIONS
# Increase recursion depth for deep DFS/trees
sys.setrecursionlimit(2000000)

# Fast I/O configuration
input = sys.stdin.readline
def print(*args, sep=" ", end="\n"):
    sys.stdout.write(sep.join(map(str, args)) + end)

# 2. INPUT PARSING SHORTHANDS
def IN_INT(): return int(input())
def IN_STR(): return input().rstrip()
def IN_ARR_INT(): return list(map(int, input().split()))
def IN_ARR_STR(): return input().split()
def IN_MAP_INT(): return map(int, input().split())

# 3. CORE LOGIC
def solve(tc: int):
    """
    Write your problem-solving logic here.
    tc: The current test case number (1-indexed).
    """
    # Example input retrieval:
    # n, m = IN_MAP_INT()
    # arr = IN_ARR_INT()
    
    # Your logic goes here
    pass

# 4. EXECUTION FRAMEWORK & LOCAL TESTING
def main():
    # Toggle local file I/O if running on a local machine
    # Looks for an 'input.txt' file in the execution folder
    if os.path.exists('input.txt') and 'ONLINE_JUDGE' not in os.environ:
        sys.stdin = open('input.txt', 'r')
        # Uncomment below if you also want to redirect output to a file
        # sys.stdout = open('output.txt', 'w')

    try:
        # Multi-test case handling
        # Change to `t = 1` if the problem has a fixed single testcase
        t = int(input()) 
    except (ValueError, TypeError):
        t = 1

    for tc in range(1, t + 1):
        solve(tc)

if __name__ == '__main__':
    main()
