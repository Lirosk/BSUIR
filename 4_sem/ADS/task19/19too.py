l = int(input())
nums = list(map(int, input().split()))

def merge_sort(n, s, f, inv):
    m = (s + f) // 2

    if (m + 1 - s) > 1:
        merge_sort(n, s, m, inv)
    if (f - m) > 1:
	    merge_sort(n, m + 1, f, inv)

    i = s
    j = m + 1
    res = []

    while i < m + 1 and j <= f:
        if n[i] > n[j]:
            res.append(n[j])
            inv[0] += m + 1 - i
            j += 1
        else:
            res.append(n[i])
            i += 1
    while i < m + 1:
        res.append(n[i])
        i += 1
    while j <= f:
        res.append(n[j])
        j += 1
    _i = 0
    while _i < f - s + 1:
        n[s + _i] = res[_i]
        _i += 1
    res.clear()

inv = [0]
merge_sort(nums, 0 , l - 1, inv)
print(inv[0])
