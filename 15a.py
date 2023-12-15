def hashkey(s):
    tot = 0
    for c in s:
        tot += ord(c)
        tot *= 17
        tot %= 256
    return tot
seq = input().split(",")

ans = 0
for s in seq:
    ans += hashkey(s)

print(ans)
