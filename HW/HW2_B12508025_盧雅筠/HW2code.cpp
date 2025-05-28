#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Patient {
    int id;
    int arrival;
    int priority;
};

class MinHeap {
public:
    void push(const Patient& p) {
        data.push_back(p);
        heapifyUp(data.size() - 1);
    }
    void pop() {
        if (data.empty()) return;

        data[0] = data.back();
        data.pop_back();

        if (!data.empty()) heapifyDown(0);
    }
    Patient top() const {
        return data.front();
    }
    bool empty() const { return data.empty(); }

private:
    vector<Patient> data;

    bool lessThan(const Patient& a, const Patient& b) const {
        if (a.priority != b.priority)
            return a.priority < b.priority;
        return a.arrival < b.arrival;
    }
    void heapifyUp(int i) { // i is from children
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (lessThan(data[i], data[parent])) {
                swap(data[i], data[parent]);
                i = parent;
            } else break;
        }
    }
    void heapifyDown(int i) { // i is from parent
        int n = data.size();
        while (true) {
            int l = 2*i + 1, r = 2*i + 2, smallest = i;
            if (l < n && lessThan(data[l], data[smallest])) smallest = l;
            if (r < n && lessThan(data[r], data[smallest])) smallest = r;
            if (smallest != i) {
                swap(data[i], data[smallest]);
                i = smallest;
            } else break;
        }
    }
};

int main() {
    // Read .csv
    string filename = "../Data/Scheduling for ER Patients.csv";
    ifstream file(filename);

    vector<Patient> patients;
    string line;

    // Read the first line (header) and ignore it
    if (!getline(file, line)) {
        return 1;
    }

    // Read the rest of the file
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string tok;
        Patient p;
        getline(ss, tok, ','); p.id = stoi(tok);
        getline(ss, tok, ','); p.arrival = stoi(tok);
        getline(ss, tok, ','); p.priority = stoi(tok);
        patients.push_back(p);
    }
    file.close();

    MinHeap heap;
    int idx = 0;               
    int currentTime = 0;

    printf("+---------+----------+-----------+--------+--------+\n");
    printf("| Patient | Priority | Unit time |  Start |    End |\n");
    printf("+---------+----------+-----------+--------+--------+\n");

    while (idx < (int)patients.size() || !heap.empty()) {
        // 已經在候診區 push heap
        while (idx < (int)patients.size() && patients[idx].arrival <= currentTime) {
            heap.push(patients[idx]);
            idx++;
        }
        // 如果沒有患者在候診區，則跳到下一位患者的到達時
        if (heap.empty()) {
            currentTime = patients[idx].arrival;
            continue;
        }
        // pop the top of heap
        Patient p = heap.top();
        heap.pop();
        int serviceTime = (p.priority == 1 ? 7
                          : p.priority == 2 ? 5
                                            : 3);
        int start = currentTime;
        int finish = currentTime + serviceTime;
        
        printf("| %7d | %8d | %9d | %6d | %6d |\n",
        p.id, p.priority, serviceTime, start, finish);

        currentTime = finish;
    }
    printf("+---------+----------+-----------+--------+--------+\n");

    return 0;
}
