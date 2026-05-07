import heapq
import time
# Partitioning intervals
interv_d = [(0,11),(0,1),(2,5),(7,10),(0,3),(4,6),(8,12),(13,16),(14,15)]

# Determines a minimum set of resources that allows the execution of all intervals of usage in the list.
def scheduleByMinimumNumberOfResources(intervals: list[tuple[int, int]]) -> list[tuple[int, int]]:
    # Sorts the interval by the first componenet (start).
    sorted_intervals: list[tuple[int, int]] = sorted(intervals, key=lambda x:x[0])

    # Heap containing a triple (release-time, resource number, task list). Key = release-time.
    allocated = []

    # Extract first interval.
    first: tuple[int, int] = sorted_intervals.pop(0)

    # Starts the heap with the first element.
    heapq.heappush(allocated,(first[1],0,[first]))
    
    while len(sorted_intervals) > 0:
        cur: tuple[int, int] = sorted_intervals.pop(0)

        # Access the first element of the heap.
        (f,r,l) = allocated[0]

        # If current start conflicts with the end of minimum resources, there is no available resources.
        if cur[0] <= f:
            # Creates a new resource number.
            n: int = len(allocated)

            # Inserts the ncur value in the new room (in the heap).
            heapq.heappush(allocated, (cur[1],n,[cur]))

        # If there is no conflict, update the resource r in the heap, including cur and updating f.
        else:
            # Removes the first element of the list.
            heapq.heappop(allocated)
            # Adds cur to the r list.
            l.insert(0, cur)

            # Includes the update in the heap.
            heapq.heappush(allocated,(cur[1],r,l))

    return allocated

print(scheduleByMinimumNumberOfResources(interv_d))
start_time = time.time() 
a = scheduleByMinimumNumberOfResources([(0,1)]*10000)
end_time = time.time()
print(a)
print(end_time - start_time, " seconds")
