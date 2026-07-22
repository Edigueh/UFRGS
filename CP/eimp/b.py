n = int(input())

def has_superior(employee: int, relations:dict[int, int], group_members: list[int]):
    cur = relations[employee]
    while cur != -1:
        if cur not in group_members:
            cur = relations[cur]
        else:
            return True
    return False

# group_id -> employees no grupo
groups: dict[int, list[int]] = {}
group_count = 0
# employee -> manager direto
relations: dict[int, int] = {}

for employee in range(1, n+1):
    manager = int(input())

    relations.setdefault(employee, manager)
    
    added_to_group = False
    for gp in groups.keys():
        group_members = groups[gp]
        if not has_superior(employee, relations, group_members):
            groups[gp].append(employee)
            added_to_group = True
            break

    if not added_to_group:
        groups.setdefault(group_count, [employee])
        group_count += 1

print(group_count)
