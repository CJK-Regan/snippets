#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Unit {
    int x, y, value, unvalidNum;
    bool unvalid[10];
};
struct cmp {
    bool operator()(Unit a, Unit b) {
        return a.unvalidNum < b.unvalidNum;
    }
};

struct Sudoku {
    int unSolved;
    Unit unit[9][9];
    priority_queue<Unit, vector<Unit>, cmp> q;
} sudoku, tmp;
stack<Sudoku> backup;

void setUnvalid(int x, int y, int value) {
    if (!sudoku.unit[x][y].value && !sudoku.unit[x][y].unvalid[value]) {
        sudoku.unit[x][y].unvalid[value] = true;
        sudoku.unit[x][y].unvalidNum++;
        sudoku.q.push(sudoku.unit[x][y]);
    }
}
void setValue(int x, int y, int value) {
    sudoku.unSolved--;
    sudoku.unit[x][y].value = value;
    for (int i = 0; i < 9; i++) {
        setUnvalid(x, i, value);
        setUnvalid(i, y, value);
    }
    for (int i = x / 3 * 3; i < (x / 3 + 1) * 3; i++)
        for (int j = y / 3 * 3; j < (y / 3 + 1) * 3; j++)
            setUnvalid(i, j, value);
}

int main() {
    sudoku.unSolved = 81;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            sudoku.unit[i][j].x = i;
            sudoku.unit[i][j].y = j;
            int v;
            cin>>v;
            if (v)
                setValue(i, j, v);
        }

    while (sudoku.unSolved) {
        Unit choose = sudoku.q.top();
        sudoku.q.pop();
        while (sudoku.unit[choose.x][choose.y].value) {
            choose = sudoku.q.top();
            sudoku.q.pop();
        }
        if (choose.unvalidNum == 9) {
            if (backup.empty()) {
                cout<<"Failed."<<endl;
                return 0;
            }
            sudoku = backup.top();
            backup.pop();
            continue;
        }
        for (int i = 1; i <= 9; i++)
            if (!choose.unvalid[i]) {
                tmp = sudoku;
                setValue(choose.x, choose.y, i);
                backup.push(sudoku);
                sudoku = tmp;
            }
        sudoku = backup.top();
        backup.pop();
    }

    cout<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!(j % 3))
                cout<<" ";
            cout<<sudoku.unit[i][j].value;
        }
        cout<<endl;
        if (i == 2 || i == 5)
            cout<<endl;
    }
    cout<<endl;
}
