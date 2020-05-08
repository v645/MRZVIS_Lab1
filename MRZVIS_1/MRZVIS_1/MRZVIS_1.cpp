#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
int currentTick = 0;
int ti_s = 1, ti_move = 1;
string table[15][15];
int row = 0, column = 0;

string printVector(vector<bool> vectorForPrint) {
    string s = "";
    for (size_t i = 0; i < vectorForPrint.size(); i++)
    {
        if (i % 4 == 0)s = s + " ";
        s = s + (vectorForPrint[i] == 0 ? "0" : "1");
    }
    return s;
}

vector<bool> moveRight(vector<bool> initial, int moveAmount = 1) {
    vector<bool> moved;

    for (size_t i = 0; i < moveAmount; i++)
    {
        moved.emplace_back(0);
    }
    for (size_t i = 0; i < initial.size(); i++)
    {
        moved.emplace_back(initial[i]);
    }

    return moved;
}
vector<bool> moveLeft(vector<bool> initial, int moveAmount = 1) {
    vector<bool> moved;

    for (size_t i = 0; i < initial.size(); i++)
    {
        moved.emplace_back(initial[i]);
    }
    for (size_t i = 0; i < moveAmount; i++)
    {
        moved.emplace_back(0);
    }
    return moved;
}
vector<bool> HalfMultiply(vector<bool> mul, bool b) {
    for (size_t i = 0; i < mul.size(); i++)
    {
        mul[i] = mul[i] & b;
    }

    table[row][column] = printVector(mul) + " hMul";
    while (table[row][column].length() < 16) table[row][column] += " ";

    row++;
    column++;

    return mul;
}

vector<bool> Sum(vector<bool> A, vector<bool> B) {
    currentTick++;

    vector<bool> result;
    bool razr = false;
    for (size_t i = 0; i < A.size(); i++) result.emplace_back(0);
    for (size_t i = 0; i < A.size(); i++)
    {
        if (A[i] + B[i] + razr == 0) { result[i] = 0; razr = 0; }
        else if (A[i] + B[i] + razr == 3) { result[i] = 1; razr = 1; }
        else if (B[i] == 1 && A[i] == 0 && razr == 0) { result[i] = 1; razr = 0; }
        else if (B[i] == 1 && A[i] == 1 && razr == 0) { result[i] = 0; razr = 1; }
        else if (B[i] == 0 && A[i] == 1 && razr == 1) { result[i] = 0; razr = 1; }
        else if (B[i] == 0 && A[i] == 0 && razr == 1) { result[i] = 1; razr = 0; }
        else if (B[i] == 1 && A[i] == 0 && razr == 1) { result[i] = 0; razr = 1; }
        else if (B[i] == 0 && A[i] == 1 && razr == 0) { result[i] = 1; razr = 0; }
    }

    table[row][column] = printVector(result) + " Sum";
    while (table[row][column].length() < 16) table[row][column] += " ";
    row++;
    column++;

    return result;
}

int BinToDec(vector<bool> bin) {
    int res = 0;
    for (size_t i = 0; i < bin.size(); i++)
    {
        res += bin[i] == 0 ? 0 : pow(2, bin.size() - i - 1);
    }
    return res;
}

vector<bool> inverse(vector<bool> initial) {
    reverse(initial.begin(), initial.end());
    return initial;
}

vector<bool> Multiply(vector<bool> A, vector<bool> B) {
    vector<bool> resultBuffer;
    for (int i = 0; i < A.size() * 2; i++) resultBuffer.emplace_back(0);
    for (int i = A.size() - 1; i >= 0; i--)
    {
        vector<bool> res;
        vector<bool> sdwig;

        res = HalfMultiply(moveRight(A, A.size() - i - 1), B[i]);
        sdwig = moveRight(A, A.size() - i);
        table[row][column] = printVector(sdwig) + " shift";
        while (table[row][column].length() < 16) table[row][column] += " ";
        row++;
        column++;
        currentTick++;

        for (int i = res.size(); i < A.size() * 2; i++) res.emplace_back(0);

        resultBuffer = Sum(resultBuffer, res);
    }

    return inverse(resultBuffer);
}

int main()
{
    vector<vector<bool>> listA, listB;
    vector<vector<bool>> results;
    int length = 3;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++)
            table[i][j] = "                ";
    }

    for (size_t i = 0; i < length; i++)
    {
        vector<bool> A;
        A.emplace_back(i % 2);
        A.emplace_back((i) % 2);
        A.emplace_back((i + 1) % 2);
        A.emplace_back((i*i) % 2);
        vector<bool> B;
        B.emplace_back((i*i + 1) % 3);
        B.emplace_back((i * i*i)% 2);
        B.emplace_back((i) % 2);
        B.emplace_back(0);

        listA.emplace_back(A);
        listB.emplace_back(B);
    }
    cout << "---------" << endl;
    for (size_t i = 0; i < length; i++)
    {
        cout << BinToDec(listA[i]) << "*" << BinToDec(listB[i]) << "=" << BinToDec(listA[i]) * BinToDec(listB[i]) << endl;
        cout << printVector(listA[i]) << "*" << printVector(listB[i]) << endl;
    }
    cout << "---------" << endl;

    for (size_t i = 0; i < length; i++)
    {
        results.emplace_back(Multiply(listA[i], listB[i]));
        row = i + 1;
        column = 0;
        cout << endl;
    }

    cout << "---------" << endl;

    for (size_t i = 0; i < length; i++)
    {
        cout << printVector(results[i]) << "=" << BinToDec(results[i]) << endl << endl;
    }

    for (int i = 0; i < 15; i++) {
        std::cout << "\n" << i + 1;
        if (i + 1 <= 9) std::cout << " ";
        for (int j = 0; j < 15; j++)
            std::cout << "|" << table[i][j] << "|";
    }

    int n;	cin >> n;
}