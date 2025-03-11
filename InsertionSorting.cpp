#include <iostream>
#include <list>
using namespace std;

int main(){
    list <int> newlist;
    int length = newlist.size();

    for (int i=1; i<length; i++){
        if (newlist[i]< newlist[i-1]){
            int temp = newlist[i];

        }
    }
    return 0;
}