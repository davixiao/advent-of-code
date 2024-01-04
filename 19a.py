from collections import defaultdict

workflows = defaultdict(list)

line = input()
while line:
    line = line.replace("{", ",")
    line = line[:-1]
    temp = line.split(",")
    workflows[temp[0]] += [t.split(":") for t in temp[1:-1]]
    workflows[temp[0]].append(["True", temp[-1]])

    line = input()

ans = 0
def recurse(x, m, a, s, workflow):
    global ans
    if workflow == "A":
        ans += x + m + a + s
        return
    elif workflow =="R":
        return
    for condition, nxt in workflows[workflow]:
        if eval(condition):
            recurse(x, m, a, s, nxt)
            break

line = input()
while line:
    line = line[1:-1]
    temp = line.split(",")
    vals = [int(v.split("=")[1]) for v in temp]
    recurse(vals[0], vals[1], vals[2], vals[3], "in")
    line = input()

print(ans)
