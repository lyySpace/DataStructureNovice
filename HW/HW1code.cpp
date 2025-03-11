#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

class Node {
public:
    bool isLeaf;    // leaf node is end node
    int label;            
    int featureIndex;    
    double threshold;   
    unique_ptr<Node> left;  // Smart Pointer: can manage dynamic memory automatically
    unique_ptr<Node> right; 
    vector<int> indices;
       
    Node() : isLeaf(false), label(-1), featureIndex(-1), threshold(0) {}
};

class DecisionTree {
public:
    unique_ptr<Node> root; 
    int minSamples; // at least 5
    int numFeatures;

    vector<vector<double>> data; // 2D
    vector<int> labels;
    vector<string> featureNames; 
   
    DecisionTree(int minSamples = 5) : minSamples(minSamples), numFeatures(7) {}

    // 1. Load .csv
    bool loadCSV(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Cannot open the file: " << filename << endl;
            return false;
        }
        string line;

        if(getline(file, line)) {
            // header 
            stringstream ss(line);
            string token;
            for (int i = 0; i < numFeatures; i++) {
                if (getline(ss, token, ',')) {
                    featureNames.push_back(token);
                }
            }
        }

        while (getline(file, line)) {
            if(line.empty()) continue; // if the line id empty, then jump next line
            
            stringstream ss(line);  // Input stream
            string token; // temporally store ss token
            vector<double> features;
    
            // the 7 feature
            for (int i = 0; i < numFeatures; i++) {
                if (!getline(ss, token, ','))
                    break;
                features.push_back(stod(token)); // turn string to double
            }
    
            // last one if label
            if (getline(ss, token, ',')) {
                int lab = stoi(token);  // turn string to int
                labels.push_back(lab);
            }
            data.push_back(features);
        }
        file.close();
        for (string n : featureNames){
            cout << n;
        }
        cout << "\n";
        return true;
    }

    // 2. count the number of 1 and 0
    void countLabels(const vector<int>& indices, int &count0, int &count1) {
        count0 = 0; count1 = 0;
        for (int idx : indices) {
            if (labels[idx] == 0)
                count0++;
            else
                count1++;
        }
    }

    // 3. compute Gini Index
    double GiniIndex(const vector<int>& indices) {
        int count0 = 0, count1 = 0;
        countLabels(indices, count0, count1);
        int total = count0 + count1;
        if(total == 0) return 0;
        double p0 = static_cast<double>(count0) / total; // turn to int
        double p1 = static_cast<double>(count1) / total;
        return 1.0 - (p0 * p0 + p1 * p1);
    }

    

    // 4. Decision Tree
    unique_ptr<Node> buildTree(const vector<int>& indices) {
        unique_ptr<Node> node = make_unique<Node>();
        node->indices = indices; 
        
        int count0, count1;
        countLabels(indices, count0, count1);
        
        // Overfitting
        if (indices.size() < minSamples || count0 == 0 || count1 == 0) {
            node->isLeaf = true; // end
            node->label = (count1 >= count0) ? 1 : 0;
            return node;
        }
        
        // Finding the best split
        double bestGini = 1e9;
        int bestFeature = -1;
        double bestThreshold = 0;
        vector<int> bestLeftIndices, bestRightIndices;
        
        for (int f = 0; f < numFeatures; f++) {
            vector<double> values;
            for (int idx : indices) {
                values.push_back(data[idx][f]);
            }
            sort(values.begin(), values.end()); // from smallest to largest
            
            for (int i = 0; i < values.size() - 1; i++) {
                double threshold = (values[i] + values[i+1]) / 2.0;
                
                vector<int> leftIndices, rightIndices;
                for (int idx : indices) { // seperate two (left,right)
                    if (data[idx][f] < threshold)
                        leftIndices.push_back(idx);
                    else
                        rightIndices.push_back(idx);
                }
                if (leftIndices.empty() || rightIndices.empty())
                    continue;
                
                double giniLeft = GiniIndex(leftIndices);
                double giniRight = GiniIndex(rightIndices);
                double weightedGini = (giniLeft * leftIndices.size() + giniRight * rightIndices.size()) / indices.size();
                
                if (weightedGini < bestGini) {
                    bestGini = weightedGini;
                    bestFeature = f;
                    bestThreshold = threshold;
                    bestLeftIndices = leftIndices;
                    bestRightIndices = rightIndices;
                }
            }
        }
        
        // lef node
        if (bestFeature == -1) {
            node->isLeaf = true;
            node->label = (count1 >= count0) ? 1 : 0;
            return node;
        }
        
        node->featureIndex = bestFeature;
        node->threshold = bestThreshold;

        node->left = buildTree(bestLeftIndices);
        node->right = buildTree(bestRightIndices);
        return node;
    }

    // Train
    void train() {
        vector<int> indices(data.size());
        for (int i = 0; i < data.size(); i++) {
            indices[i] = i;
        }
        root = buildTree(indices);
    }

    // 對單一樣本進行預測
    int predict(const vector<double>& sample) {
        Node* current = root.get();
        while (!current->isLeaf) {
            int f = current->featureIndex;
            if (sample[f] < current->threshold)
                current = current->left.get();
            else
                current = current->right.get();
        }
        return current->label;
    }

    // Accuaracy
    double computeAccuracy() {
        double sumCorrect = 0;
        computeAccuracyHelper(root.get(), sumCorrect);
        return sumCorrect / data.size();
    }

    void computeAccuracyHelper(Node* node, double& sumCorrect) {
        if (!node)
            return;
        if (node->isLeaf) {
            int count0, count1;
            countLabels(node->indices, count0, count1);
            if (node->label == 1) {
                sumCorrect += count1;
            } else {
                sumCorrect += count0;
            }
        } else {
            computeAccuracyHelper(node->left.get(), sumCorrect);
            computeAccuracyHelper(node->right.get(), sumCorrect);
        }
    }

    // Print!!
    void printTree(Node* node, string indent = "", bool isLast = true) {
        if (!node)
            return;
        
        cout << indent;
        if (isLast) {
            cout << "└─";
            indent += "  ";
        } else {
            cout << "├─";
            indent += "│ ";
        }
        
        if (node->isLeaf) {
            int count0, count1;
            countLabels(node->indices, count0, count1);
            cout << "葉節點 (Label: " << node->label 
                 << ", n0: " << count0 << ", n1: " << count1 << ")" << endl;
        } else {
            cout << "節點 (Feature: " << node->featureIndex 
                 << ", Threshold: " << node->threshold << ")" << endl;
            // 假設左子節點不一定是最後一個分支，而右子節點是最後一個分支
            printTree(node->left.get(), indent, false);
            printTree(node->right.get(), indent, true);
        }
    }


    // ---------------------------
    // 以下為視覺化輸出：產生 DOT 檔案格式
    // ---------------------------
    
    // 遞迴產生 DOT 檔內容，並回傳該節點的唯一 ID
    int generateDot(Node* node, ofstream &out, int &nodeId) {
        int currentId = nodeId++;
        if (node->isLeaf) {
            // 葉節點標示：顯示 Label 與該節點樣本數量
            int count0, count1;
            countLabels(node->indices, count0, count1);
            out << "  node" << currentId << " [label=\"葉: " << node->label
                << "\\nn0:" << count0 << " n1:" << count1 << "\"];" << endl;
        } else {
            out << "  node" << currentId << " [label=\""
                << featureNames[node->featureIndex] << " < " << node->threshold << "\"];" << endl;
            int leftId = generateDot(node->left.get(), out, nodeId);
            int rightId = generateDot(node->right.get(), out, nodeId);
            // 畫邊：從父節點指向左右子節點
            out << "  node" << currentId << " -> node" << leftId << " [label=\"T\"];" << endl;
            out << "  node" << currentId << " -> node" << rightId << " [label=\"F\"];" << endl;
        }
        return currentId;
    }

    // 產生 DOT 檔案 (決策樹視覺化)
    void exportToDot(const string &filename) {
        ofstream out(filename);
        if (!out.is_open()) {
            cerr << "無法寫入檔案: " << filename << endl;
            return;
        }
        out << "digraph DecisionTree {" << endl;
        out << "  node [shape=box];" << endl;
        int nodeId = 0;
        generateDot(root.get(), out, nodeId);
        out << "}" << endl;
        out.close();
        cout << "已輸出 DOT 檔案: " << filename << endl;
    }

};

int main(){
    DecisionTree tree(5);
    string filename = "./Diagnosis_7features.csv";
    
    if (!tree.loadCSV(filename)) {
        cerr << "讀取資料失敗！" << endl;
        return 1;
    }
    

    tree.train();
    cout << "決策樹結構：" << endl;
    tree.printTree(tree.root.get());
    
    double accuracy = tree.computeAccuracy();
    cout << "決策樹準確度: " << accuracy * 100 << "%" << endl;

    // 將決策樹輸出成 DOT 檔案
    tree.exportToDot("decision_tree.dot");
    
    // 範例：對第一筆資料進行預測
    if (!tree.data.empty()) {
        int pred = tree.predict(tree.data[0]);
        cout << "第一筆資料預測結果: " << pred << endl;
    }
    return 0;
}