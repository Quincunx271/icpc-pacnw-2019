import itertools, functools

#S = input()
#S = 'a'*1000+'b'*1000+'c'*1000+'d'*1000+'e'*1000+"f"*1000+'g'*1000
S = 'abcdefghijklmnopqrstuvwxyz'
S='acccegg'

M = dict()
for x in S: M[x] = 0
for x in S: M[x] += 1

'''
M = {'a': 1,
 'c': 3,
 'e': 1,
 'g': 2,
 'i': 2,
 'm': 2,
 'n': 2,
 'o': 2,
 'p': 2,
 'r': 2,
 's': 1,
 't': 2}
'''

acc = 0

PRIME = 11_092_019

for length in range(len(M)+1):
    for comb in itertools.combinations(M, length):
        asdf = [M[k] for k in comb]
        acc = (acc + functools.reduce(lambda a, b: a * b, asdf, 1)
            ) % PRIME
    #combs = map(lambda x: M.get, itertools.combinations(M, length))
    
print(acc)