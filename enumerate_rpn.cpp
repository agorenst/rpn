#include "./../cfg/cfg.h"
#include "./../cfg/parse_tree.h"

#include <iostream>
#include <list>

using namespace std;
using namespace cfg;

const cfg::grammar arithmetic{
    {"S", "S", "S", "+"},
    {"S", "S", "S", "-"},
    {"S", "S", "S", "/"},
    {"S", "S", "S", "*"},
    {"S", "n"}
};

list<parse_tree> all_develop_of_leaf(const parse_tree& p) {
    list<parse_tree> ret_val = {};
    if (!p.has_undeveloped()) { return ret_val; }
    symbol to_develop = p.undeveloped_symbol();

    assert(p.g.is_nonterminal(to_develop));

    for (auto&& production : p.g.productions_from_nonterminal(to_develop)) {
        int index = p.g.index_of(production);
        ret_val.push_back(p.apply_production(index));
    }
    return ret_val;
}

int enumerate(int sizelimit) {
    parse_tree start(arithmetic);
    std::stack<parse_tree> work_list;
    work_list.push(start);
    while(work_list.size()) {
        auto x = work_list.top();
        work_list.pop();
        if (x.leaf_count() > sizelimit) {
            continue;
        }
        if (!x.has_undeveloped()) {
            x.print_terminals_dfs(cout);
            cout << endl;
        }
        else {
            for (auto&& t : all_develop_of_leaf(x)) {
                work_list.push(t);
            }
        }
    }
    return 0;
}

int main() {
    enumerate(32);
    return 0;
}
