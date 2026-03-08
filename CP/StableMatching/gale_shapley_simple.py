from collections import deque

def gale_shepley(p_prefs: dict[str, list[str]], r_prefs: dict[str, list[str]]) -> set[tuple]:
    r_rank = {r: {p: i for i, p in enumerate(pref)} for r, pref in r_prefs.items()}
    free_p = deque(p_prefs.keys())
    next_idx = {p: 0 for p in p_prefs}
    engaged_to = {}  # receiver -> proposer
    while free_p:
        p = free_p.popleft()
        if next_idx[p] >= len(p_prefs[p]): continue  # proposed to everyone
        r = p_prefs[p][next_idx[p]]
        next_idx[p] += 1
        if r not in engaged_to:
            engaged_to[r] = p
        else:
            p_prime = engaged_to[r]
            if r_rank[r][p_prime] < r_rank[r][p]:
                free_p.append(p)
            else:
                engaged_to[r] = p
                free_p.append(p_prime)
    return {(p, r) for r, p in engaged_to.items()}

if __name__ == "__main__":
    p_prefs: dict[str, list[str]] = {
        "Atlanta": ["Wayne", "Val", "Yolanda", "Zeus", "Xavier"],
        "Boston": ["Yolanda", "Wayne", "Val", "Xavier", "Zeus"],
        "Chicago": ["Wayne", "Zeus", "Xavier", "Yolanda", "Val"],
        "Detroit": ["Val", "Yolanda", "Xavier", "Wayne", "Zeus"],
        "El Paso": ["Wayne", "Yolanda", "Val", "Zeus", "Xavier"]
    }

    r_prefs: dict[str, list[str]] = {
        "Val": ["El Paso", "Atlanta", "Boston", "Detroit", "Chicago"],
        "Wayne": ["Chicago", "Boston", "Detroit", "Atlanta", "El Paso"],
        "Xavier": ["Boston", "Chicago", "Detroit", "El Paso", "Atlanta"],
        "Yolanda": ["Atlanta", "El Paso", "Detroit", "Chicago", "Boston"],
        "Zeus": ["Detroit", "Boston", "El Paso", "Chicago", "Atlanta"]
    }

    result: set[tuple] = gale_shepley(p_prefs=p_prefs, r_prefs=r_prefs)

    print(f"Result: {result}")
