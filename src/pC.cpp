#include <bits/stdc++.h>

using namespace std;

template <typename T>
auto read() {
    T t;
    cin >> t;
    return t;
}

constexpr auto NLimit = 100'000 + 3;
constexpr auto MLimit = 100'000;

std::vector<int> nodes[NLimit] = {};
bool visited[NLimit] = {};
int costs[NLimit] = {};

int main() {
    auto const N = read<int>();
    auto const M = read<int>();

    for (int C = M; C --> 0; ) {
        auto const u = read<int>();
        auto const v = read<int>();

        nodes[u].push_back(v);
        nodes[v].push_back(u);
    }

    visited[1] = true;
    auto next = queue<int>{};
    next.push(1);

    while (!next.empty()) {
        int const cur = next.front();
        next.pop();

        if (cur == N) break;

        for (int to : nodes[cur]) {
            if (visited[to]) continue;
            costs[to] = costs[cur] + 1;
            visited[to] = true;
            next.push(to);
        }
    }

    cout << (costs[N] - 1) << '\n';
}
