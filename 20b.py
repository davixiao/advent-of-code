from collections import defaultdict, deque
import math

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

pointer = ""

for src, targets in adj.items():
    for target in targets:
        if target in conjunctions:
            conjunctions[target][src] = False
        if target == "rx":
            pointer = src

tracker = {key: [] for key in conjunctions[pointer].keys()}

def bfs(start, pulse):
    global adj, flipflops, conjunctions, tracker, pointer
    queue = deque([(start, pulse, "")])
    lo, hi = 0, 0
    while queue:
        curr, pulse_type, prev = queue.popleft()

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
            if curr == pointer:
                tracker[prev].append(pulse_type)

            if all(conjunctions[curr].values()):
                pulse_type = False
            else:
                pulse_type = True
            
           
        if send:
            for nxt in adj[curr]:
                queue.append((nxt, pulse_type, curr))
        
    return [lo, hi]
los, his = 0, 0

tracker2 = {key: [] for key in conjunctions[pointer].keys()}
for i in range(10000):
    tracker = {key: [] for key in conjunctions[pointer].keys()}
    lo, hi = bfs("button", False)
    for k, v in tracker.items():
        if 1 in v:
            tracker2[k].append(i)

ans = 1
for k, v in tracker2.items():
    ans = math.lcm(ans, v[1] - v[0])

print(ans)
