
# Delay minimizer.
interv_e: list[tuple[str, int, int]] = [("a",3,6), ("b",2,8), ("c",1,9), ("d",4,9), ("e",3,14), ("f",2,15)]

# Determines a scheduling that minimizes the max delay.
def minimizes_delay(intervals: list[tuple[str, int, int]]):
    # Sorts the interval list (name, duration, deadline) by the 3rd component (deadline).
    sorted_intervals: list[tuple[str, int, int]] = sorted(intervals, key=lambda x:x[2])

    # Registered time of tasks.
    t: int = 0

    # List of selected intervals, starting with the first one.
    selected_intervals: list[tuple[str, int, int]] = []

    while len(sorted_intervals) > 0:
        cur: tuple[str, int, int] = sorted_intervals.pop(0)

        # Schedules the cur task in the interval (t, t + duration), generating a triple (cur, t, t + duration) in the output.
        selected_intervals.append((cur[0], t, t+cur[1]))

        t += cur[1]
    
    return selected_intervals

print(minimizes_delay(interv_e))
