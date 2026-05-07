# Scheduling Intervals
interv_a = [(0,9),(1,2),(3,4),(5,6),(7,8)]
interv_b = [(0,5),(6,10),(4,7)]
interv_c = [(0,2),(1,4),(1,4),(1,4),(3,6),(5,8),(7,10),(9,12),(9,12),(9,12),(11,14)]

# Determines a max subset of compatible intervals.
def schedule_by_max_number_of_events(interval_list: list[tuple[int, int]]) -> list[tuple[int, int]]:
    # Sorts the interval list for the 2nd component (end-time).
    sorted_intervals: list[tuple[int, int]] = sorted(interval_list, key=lambda x:x[1])

    # List of selected intervals, initialized with the first interval.
    selected_intervals: list[tuple[int, int]] = [sorted_intervals.pop(0)]

    while len(sorted_intervals) > 0:
        cur: tuple[int, int] = sorted_intervals.pop(0)

        # If the interval is compatible with the last inserted interval in the selected ones.
        if cur[0] > selected_intervals[-1][1]:
            selected_intervals.append(cur)
        
    return selected_intervals

print(schedule_by_max_number_of_events(interv_a))
print(schedule_by_max_number_of_events(interv_b))
print(schedule_by_max_number_of_events(interv_c))
