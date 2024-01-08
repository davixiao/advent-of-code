from collections import defaultdict, deque

flipflops = {}

conjunctions = {}

adj = defaultdict(list)

while line := input():
    src, _, *targets = line.split()

    if src[0] == '%':
        src = src[1:]
        flipflops[src] = False
    elif src[0] == '&':
        src = src[1:]
        conjunctions[src] = {} # false = low

    for target in targets:
        adj[src].append(target.replace(',', ''))

adj["button"].append("broadcaster")

for src, targets in adj.items():
    for target in targets:
        if target in conjunctions:
            conjunctions[target][src] = False

def bfs(start, pulse):
    global adj, flipflops, conjunctions, 
    queue = deque([(start, pulse, "")])
    lo, hi = 0, 0
    while queue:
        curr, pulse_type, prev = queue.popleft()
        # print(prev, pulse_type, curr)
        if pulse_type:
            hi += 1
        elif not pulse_type and curr != "button":
            lo += 1

        send = True
        if curr in flipflops:
            if not pulse_type:
                flipflops[curr] = not flipflops[curr]
                pulse_type = flipflops[curr]
            else:
                send = False
        elif curr in conjunctions:
            conjunctions[curr][prev] = pulse_type
            if all(conjunctions[curr].values()):
                pulse_type = False
            else:
                pulse_type = True
        if send:
            for nxt in adj[curr]:
                queue.append((nxt, pulse_type, curr))
        
    return [lo, hi]
los, his = 0, 0
for _ in range(1000):
    lo, hi = bfs("button", False)
    los += lo
    his += hi
print(los*his)
