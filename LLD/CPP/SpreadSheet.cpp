#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
using namespace std;

class SpreadSheet {
    unordered_map<string, string> cells;

    int evaluateExpr(const string &expr, unordered_map<string, int> &memo) {
        // If it's just a number
        if (isdigit(expr[0]) || expr[0] == '-') {
            return stoi(expr);
        }

        // If it's a formula, strip '='
        string s = expr[0] == '=' ? expr.substr(1) : expr;

        int res = 0;
        int sign = 1;
        string token;

        for (int i = 0; i <= (int)s.size(); i++) {
            if (i == (int)s.size() || s[i] == '+' || s[i] == '-') {
                if (!token.empty()) {
                    res += sign * getValue(token, memo);
                    token.clear();
                }
                if (i < (int)s.size()) sign = (s[i] == '+') ? 1 : -1;
            } else {
                token += s[i];
            }
        }
        return res;
    }

    int getValue(const string &cellId, unordered_map<string, int> &memo) {
        if(isdigit(cellId[0])) return stoi(cellId);
        if (!cells.count(cellId)) return 0; // empty cell defaults to 0
        if (memo.count(cellId)) return memo[cellId];

        string expr = cells[cellId];
        return memo[cellId] = evaluateExpr(expr, memo);
    }

public:
    void setCell(const string &cellId, const string &expr) {
        if (expr.empty()) return;
        cells[cellId] = expr;
    }

    int getCell(const string &cellId) {
        unordered_map<string, int> memo;
        return getValue(cellId, memo);
    }
};

int main() {
    SpreadSheet sp;
    sp.setCell("A1", "23");
    sp.setCell("B1", "20");
    sp.setCell("C1", "=-1-A1");

    cout << sp.getCell("C1") << "\n"; // 3
}
