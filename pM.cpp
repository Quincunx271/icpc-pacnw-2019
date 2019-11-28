#include <bits/stdc++.h>

using namespace std;

template <typename T>
auto read() {
    T t;
    cin >> t;
    return t;
}

#define SIZE 1000

// Represents + 0.5, +0.5
struct cell_t {
    int r = 0;
    int c = 0;

    bool operator==(cell_t rhs) const {
        return r == rhs.r && c == rhs.c;
    }
    bool operator!=(cell_t rhs) const {
        return !(*this == rhs);
    }
};

namespace std {
    template <>
    struct hash<cell_t> {
        auto operator()(cell_t const& c) const {
            return hash<uint64_t>{}((uint64_t)(c.r) << 32 | (uint64_t(c.c) << 0));
        }
    };
}

int main() {
    char table[SIZE+4][SIZE+4] ={};

    auto R = read<int>();
    auto C = read<int>();

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            table[r+2][c+2] = read<char>();
        }
    }
    fill(begin(table[0]), end(table[0]), '.');
    fill(begin(table[1]), end(table[1]), '.');
    fill(begin(table[R+2]), end(table[R+2]), '.');
    fill(begin(table[R+3]), end(table[R+3]), '.');

    for (int r = 0; r < R + 4; ++r) {
        table[r][0] = '.';
        table[r][1] = '.';
        table[r][C+2] = '.';
        table[r][C+3] = '.';
    }

    unordered_set<cell_t> already_visited;
    unordered_set<cell_t> cur_flood;

    vector<cell_t> neighbors{};

    auto const flood_fill = [&](cell_t cell) {
        neighbors.clear();
        cur_flood.clear();

        auto pb = [&](cell_t c) {
            if (c.c < 0) return;
            if (c.r < 0) return;
            if (c.c >= C + 3) return;
            if (c.r >= R + 3) return;
            if (cur_flood.find(c) != cur_flood.end()) return;
            cur_flood.insert(c);
            neighbors.push_back(c);
        };

        if (already_visited.find(cell) != already_visited.end()) return 0;

        pb(cell);

        {
            char ul = table[cell.r][cell.c];
            char ur = table[cell.r][cell.c + 1];
            char ll = table[cell.r + 1][cell.c];
            char lr = table[cell.r + 1][cell.c + 1];
            if (ul == '\\' && lr == '\\' || ur == '/' && ll == '/') {
                return 0;
            }
        }

        if (neighbors.empty()) return 0;

        while (!neighbors.empty()) {
            auto cur = neighbors.back();
            neighbors.pop_back();

            char ul = table[cur.r][cur.c];
            char ur = table[cur.r][cur.c + 1];
            char ll = table[cur.r + 1][cur.c];
            char lr = table[cur.r + 1][cur.c + 1];

            assert(ul == '/' || ul == '\\' || ul == '.');
            assert(ur == '/' || ur == '\\' || ur == '.');
            assert(ll == '/' || ll == '\\' || ll == '.');
            assert(lr == '/' || lr == '\\' || lr == '.');

            if (ul == '\\' && ur == '/' && ll == '/' && lr == '\\') return 0;
            if (ul == '\\' && lr == '\\' || ur == '/' && ll == '/') {
                continue;
            }

            if (ul == '.') pb({cur.r - 1, cur.c - 1});
            if (ur == '.') pb({cur.r - 1, cur.c + 1});
            if (ll == '.') pb({cur.r + 1, cur.c - 1});
            if (lr == '.') pb({cur.r + 1, cur.c + 1});

            // can we go orthogonal?
            //up
            if (!(ul == '/' && ur == '\\' || ul == '\\' && ur == '/')) {
                pb({cur.r - 1, cur.c});
            }
            // right
            if (!(ur == '/' && lr == '\\' || ur == '\\' && lr == '/')) {
                pb({cur.r, cur.c + 1});
            }
            //down
            if (!(ll == '/' && lr == '\\' || ll == '\\' && lr == '/')) {
                pb({cur.r + 1, cur.c});
            }
            // left
            if (!(ul == '/' && ll == '\\' || ul == '\\' && ll == '/')) {
                pb({cur.r, cur.c - 1});
            }


            /*
            if (ul == '/') {
                if (ll != '\\') pb({cur.r, cur.c - 1});
                if (ur != '\\') pb({cur.r - 1, cur.c});
            } else if (ul == '\\') {
                if (ll != '/') pb({cur.r, cur.c - 1});
                if (ur != '/') pb({cur.r - 1, cur.c});
            }

            if (lr == '/') {
                if (ll != '\\') pb({cur.r + 1, cur.c});
                if (ur != '\\') pb({cur.r, cur.c + 1});
            }&
            else if (lr == '\\') {
                if (ll != '/') pb({cur.r + 1, cur.c});
                if (ur != '/') pb({cur.r, cur.c + 1});
            }
            */
        }

        already_visited.merge(std::move(cur_flood));
        cur_flood = std::unordered_set<cell_t>{};

        return 1;
    };
    flood_fill(cell_t{0, 0});

    uint64_t result = 0;
    for (int r = 0; r <= R; ++r) {
        for (int c = 0; c <= C; ++c) {
            result += flood_fill({r+1, c+1});
        }
    }

    cout << result << '\n';
}