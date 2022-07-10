import sys 
for line in sys.stdin:
    a = line.split()
    s = a[0]
    size = len(s)
    num_star = 0
    for c in s:
        if c == '*':
            num_star += 1
    ans  = ['*'] * size
    i = num_star
    for c in s:
        if c != '*':
            ans[i] = c
            i += 1
    print(''.join(ans))
            