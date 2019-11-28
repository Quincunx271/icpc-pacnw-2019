A, B = map(int, input().split())
#A, B = 2, 1

ops = 0
while True:
    if A <= B:
        print(ops + B - A)
        exit()

    if A % 2 == 0:
        A = A // 2
        ops += 1
    else:
        A = (A + 1) // 2
        ops += 2


