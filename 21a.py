grid = []
start = (-1, -1)
while line := input():
    grid.append(line)

for i in range(len(grid)):
    for j in range(len(grid[i])):
        if grid[i][j] == "S":
            start = (i, j)
vis = set()
cnt = 0
def dfs(r, c, dist):
    global vis, cnt
    if dist == 64:
        cnt += 1
 
    dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    for dr, dc in dirs:
        nr, nc = r+dr, c+dc
        if dist + 1 > 64:
            break
        if not (0 <= nr < len(grid) and 0 <= nc < len(grid[0])):
            continue
        if grid[nr][nc] == "#":
            continue
        if (nr, nc, dist + 1) in vis:
            continue
        vis.add((nr, nc, dist + 1))
        dfs(nr, nc, dist + 1)

dfs(start[0], start[1], 0)

print(cnt)
