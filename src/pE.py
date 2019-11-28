import itertools, functools

groupby = itertools.groupby

S = input()
#S = 'a'*1000+'b'*1000+'c'*1000+'d'*1000+'e'*1000+"f"*1000+'g'*1000
# S = 'abcdefghijklmnopqrstuvwxyz'
S = ''.join(sorted(S))

groups = (list(g) for k, g in groupby(S))

def all_same(seq):
    return len(seq) + 1

acc = 1

PRIME = 11_092_019

for group in groups:
    acc = (acc * all_same(group)) % PRIME
    
print(acc)