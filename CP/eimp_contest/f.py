def solve():
    s = input().strip()
    ans = float('inf')
    
    # These are the only 4 valid two-digit endings for multiples of 25
    targets = ["00", "25", "50", "75"]
    
    for target in targets:
        # Step 1: Find the right-most digit of the target (e.g., '5' for "25")
        last_digit_idx = s.rfind(target[1])
        
        if last_digit_idx != -1:
            # Step 2: Find the right-most first digit of the target BEFORE the last digit
            # (e.g., '2' before the '5')
            first_digit_idx = s.rfind(target[0], 0, last_digit_idx)
            
            if first_digit_idx != -1:
                # Calculate deletions needed:
                # (total length) - (index of the first digit) - 2 (for the two digits we keep)
                deletions = len(s) - first_digit_idx - 2
                ans = min(ans, deletions)
                
    print(ans)

tc = int(input())
for _ in range(tc):
    solve()