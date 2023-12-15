from collections import defaultdict

def hashkey(s):
    tot = 0
    for c in s:
        tot += ord(c)
        tot *= 17
        tot %= 256
    return tot
seq = input().split(",")

hashtable = defaultdict(list)
ans = 0
for s in seq:
    if s[-1] == "-":
        key = hashkey(s[:-1])
        for i in range(len(hashtable[key])):
            if hashtable[key][i][0] == s[:-1]:
                hashtable[key].pop(i)
                break
    else:
        key = hashkey(s[:-2])
        for i in range(len(hashtable[key])):
            if hashtable[key][i][0] == s[:-2]:
                hashtable[key][i][1] = int(s[-1])
                break
        else:
            hashtable[key].append([s[:-2], int(s[-1])])

ans = 0
for box, lst in hashtable.items():
    for i, v in enumerate(lst):
        ans += (box + 1) * (i + 1) * (v[1])
print(ans)
        
