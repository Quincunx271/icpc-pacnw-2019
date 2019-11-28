from collections import deque

N, M = map(int, input().split())
# N, M = 3, 3

graph = [[] for _ in range(N)]

for _ in range(M):
    from_, to = map(lambda s: int(s), input().split())
    graph[from_-1].append(to)
    graph[to-1].append(from_)


past = {1}

costs = [0, *([1_000_000]*(N-1))]

next_to_visit = deque([1])

while next_to_visit:
    cur = next_to_visit.popleft()

    for to in graph[cur - 1]:
        if to in past: continue
        costs[to-1] = min(costs[cur -1] + 1, costs[to -1])

        if to == N: break

        next_to_visit.append(to)
        past.add(to)

print(costs[to-1]-1)
