from collections import deque

queue: list[str] = ["A", "B", "C", "B", "C", "A"]

def farthest_in_future(queue: list[str], cache_size: int = 2) -> int:
    """Greedy algorithm to minimize Cache Miss.
    O(n * k), where n is the queue size and k is the cache size.

    Returns an integer representing the number of minimal Cache Miss.
    """

    # Maps each task to a list of indexes where it shows up in the queue.
    task_times: dict[str, list[int]] = {}
    for i in range(len(queue)):
        if queue[i] in task_times:
            task_times[queue[i]].append(i)
        else:
            task_times[queue[i]] = deque([i])

    cache: list[str] = []
    misses: int = 0

    for i, task in enumerate(queue):
        # Removes the index of task appearing.
        task_times[task].popleft()

        if task in cache: # Cache Hit
            continue
        else:            # Cache Miss
            misses += 1

            # If there is space in cache, includes the task.
            if len(cache) < cache_size:
                cache.append(task)
            
            # Removes the task which next index in the queue is bigger (farthest in future task).
            else:
                farthest_task: int | str = -1
                farthest_time: int = -1

                for t in cache:
                    next_appearing: int = task_times[task][0] if len(task_times[t]) > 0 else -1
                    if next_appearing > farthest_time:
                        farthest_task = t
                        farthest_time = next_appearing
                if farthest_task != -1:
                    # Removes the task that will have the biggest delay to appear again.
                    cache.remove(farthest_task)
                    cache.append(task)

    return misses

print(farthest_in_future(queue))
