# Mistakes:
# I used [:]... Not a deep copy!
# I thought "=" was a rule...


from collections import defaultdict
import math

workflows = defaultdict(list)

line = input()
while line:
    line = line.replace("{", ",")
    line = line[:-1]
    temp = line.split(",")
    workflows[temp[0]] += [t.split(":") for t in temp[1:-1]]
    workflows[temp[0]].append(["True", temp[-1]])

    line = input()

def idx(symbol):
    return ["x", "m", "a", "s"].index(symbol)

ans = 0
# x is a list [lo, hi]
def recurse(vals, workflow):
    global ans
    if workflow == "A":
        ans += math.prod([b-a+1 for a,b in vals])
        return
    elif workflow =="R":
        return
    
    vals = [lst[:] for lst in vals]
    for condition, nxt in workflows[workflow]:
        if condition == "True":
            recurse(vals, nxt)
            break
        ind = idx(condition[0])
        newv = vals[ind][:]
        value = int(condition[2:])

        if condition[1] == "<":
            newv[1] = min(value-1, vals[ind][1])
            vals[ind][0] = max(vals[ind][0], value)
        else:
            vals[ind][1] = min(value, vals[ind][1])
            newv[0] = max(vals[ind][0], value+1)

        
        if newv[0] <= newv[1]:
            recurse(vals[:ind] + [newv] + vals[ind+1:], nxt)
        if vals[ind][0] > vals[ind][1]:
            break
recurse([[1, 4000], [1, 4000], [1, 4000], [1, 4000]], "in")

print(ans)
