from heapq import heappush, heappop
from collections import defaultdict
N = 141

def in_range(r, c):
    global N
    return (0 <= r < N) and (0 <= c < N)

def is_backwards(bearing, idx):
    restricted = [1, 0, 3, 2]
    return restricted[bearing] == idx

grid = []
for i in range(N):
    grid.append([int(i) for i in input()])

# r, c, block count, dir
# dir: 0 down, 1 up, 2 right, 3 left
dists = defaultdict(lambda: float('inf'))

# dist, r, c, block, count ,dir
pq = [(0, 0, 0, 0, 0), (0, 0, 0, 0, 1), (0, 0, 0, 0, 2), (0, 0, 0, 0, 3)]

while pq:
    dist, r, c, cnt, bearing = heappop(pq)
    dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]]
    for idx, d in enumerate(dirs):
        dr, dc = d
        nr, nc = r + dr, c + dc
        if not in_range(nr, nc):
            continue
        if is_backwards(bearing, idx):
            continue

        if bearing == idx:
            if cnt < 10 and dists[(nr, nc, cnt+1, idx)] > dist + grid[nr][nc]:
                dists[(nr, nc, cnt+1, idx)] = dist + grid[nr][nc]
                heappush(pq, (dists[(nr, nc, cnt+1, idx)], nr, nc, cnt+1, idx))
        else:
            if cnt >= 4 and dists[(nr, nc, 1, idx)] > dist + grid[nr][nc]:
                dists[(nr, nc, 1, idx)] = dist + grid[nr][nc]
                heappush(pq, (dists[(nr, nc, 1, idx)], nr, nc, 1, idx))

ans = float('inf')
for k, v in dists.items():
    r, c, cnt, bearing = k
    if r == N - 1 and c == N - 1:
        ans = min(ans, v)
print(ans)
