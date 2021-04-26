l = int(input())
nums = list(map(int, input().split()))

inv = 0

def merge_sort(n):
    global inv
    nl = len(n) - 1

    m = nl//2

    l = n[:m+1]
    r = n[m+1:]

    ll = len(l)
    rl = len(r)

    if ll > 1:
        l = merge_sort(l)
    if rl > 1:
        r = merge_sort(r)
    
    i = 0
    j = 0
    res = []

    while i < ll and j < rl:
        if r[j] < l[i]:
            res.append(r[j])
            inv += m + 1 - i
            j += 1
        else:
            res.append(l[i])
            i += 1
    
    while i < ll:
        res.append(l[i])
        i += 1
    while j < rl:
        res.append(r[j])
        j += 1
    
    return res

merge_sort(nums)
print(inv)
