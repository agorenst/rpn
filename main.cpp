#include <string>
#include <set>
#include <stack>
#include <cassert>
#include <list>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

const set<string> operators = {"+", "-", "/", "*"};

// Sequence is some type that is iterable and contains a sequence
// of strings.

// We make this a class rather than a function because we have a collection
// of helper methods...

template<typename Sequence, typename Output>
class rpn_to_tac {
    private:

        bool is_operator(std::string s) const {
            return operators.find(s) != operators.end();
        }
        int temporary_counter = 0;

        Output& o;

        string generate(string op, string l, string r) {
            auto res = "t"+std::to_string(temporary_counter++);
            o = res + " = " + l + " " + op + " " + r + "\n";
            return res;
        }

        void terminate(string return_value) {
            o = "return " + return_value + "\n";
        }
    public:

        // Weird programming approach: do all the work in the constructor.
        rpn_to_tac(const Sequence& seq, Output& o): o(o) {
            stack<string> symbol_stack;
            for (auto&& v : seq) {
                if (is_operator(v)) {
                    assert(symbol_stack.size() >= 2);
                    auto l = string{symbol_stack.top()};
                    symbol_stack.pop();
                    auto r = string{symbol_stack.top()};
                    symbol_stack.pop();

                    auto res = string{generate(v, r, l)};
                    symbol_stack.push(res);
                }
                else {
                    symbol_stack.push(v);
                }
            }
            assert(symbol_stack.size() == 1);
            auto return_value = string{symbol_stack.top()};
            symbol_stack.pop();
            terminate(return_value);
        }

};

list<string> example_input = list<string>{"5", "1", "2", "+", "4", "*", "+", "3", "-"};

list<string> tokenize(string input) {
    stringstream strstr(input);
    istream_iterator<string> start(strstr);
    istream_iterator<string> finish;
    return list<string>(start, finish);
}

int main() {
    string input;
    ostream_iterator<string> out(cout);
    while(getline(cin, input)) {
        list<string> expr = tokenize(input);
        rpn_to_tac<list<string>, ostream_iterator<string>>(expr, out);
        cout << endl;
    }
}
