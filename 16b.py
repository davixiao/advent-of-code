import sys
sys.setrecursionlimit(4000)

N = 110

reflections = {
    "/UP": "RIGHT",
    "/DOWN": "LEFT",
    "/LEFT": "DOWN",
    "/RIGHT": "UP",
    "\\UP": "LEFT",
    "\\DOWN": "RIGHT",
    "\\LEFT": "UP",
    "\\RIGHT": "DOWN",
}

def travel_dir(r, c, direction):
    if direction == "UP":
        return (r-1, c)
    if direction == "DOWN":
        return (r+1, c)
    if direction == "LEFT":
        return (r, c-1)
    if direction == "RIGHT":
        return (r, c+1)


grid = []
for i in range(N):
    grid.append(input())

visited = set()


def recurse(r, c, direction):
    global grid
    global visited
    if not(0 <= r < len(grid)) or not(0 <= c < len(grid)):
        return
    if (r, c, direction) in visited:
        return
    visited.add((r, c, direction))
    if grid[r][c] in ("\\", "/"):
        reflect = reflections[grid[r][c] + direction]
        rr, rc = travel_dir(r, c, reflect)
        recurse(rr, rc, reflect)
    elif grid[r][c] == "|" and direction in ("LEFT", "RIGHT"):
        ur, uc = travel_dir(r, c, "UP")
        dr, dc = travel_dir(r, c, "DOWN")
        recurse(ur, uc, "UP")
        recurse(dr, dc, "DOWN")
    elif grid[r][c] == "-" and direction in ("UP", "DOWN"):
        lr, lc = travel_dir(r, c, "LEFT")
        rr, rc = travel_dir(r, c, "RIGHT")
        recurse(lr, lc, "LEFT")
        recurse(rr, rc, "RIGHT")
    else:
        nr, nc = travel_dir(r, c, direction)
        recurse(nr, nc, direction)

def calc():
    global grid
    global visited
    ret = 0
    for r in range(N):
        for c in range(len(grid[i])):
            for direction in ["UP", "DOWN", "LEFT", "RIGHT"]:
                if (r, c, direction) in visited:
                    ret += 1
                    break
    return ret
ans = 0

for i in range(N):
    params = [
        [i, 0, "RIGHT"],
        [i, N-1, "LEFT"],
        [0, i, "DOWN"],
        [N-1, i, "UP"]
    ]
    for r, c, direction in params:
        visited.clear()
        recurse(r, c, direction)
        ans = max(ans, calc())

print(ans)

