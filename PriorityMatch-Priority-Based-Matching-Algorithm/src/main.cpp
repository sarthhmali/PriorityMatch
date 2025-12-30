#include <bits/stdc++.h>
using namespace std;

/*
  PriorityMatch
  Priority-Based Compatibility Matching Algorithm
*/

struct User {
    int id;
    string name;
    int rating;
    int waitingTime;
    bool matched;
};

int calculatePriority(const User& u) {
    int waitingWeight = 3;
    int bonus = 11 - u.rating;
    return (u.waitingTime * waitingWeight) + bonus;
}

int compatibilityScore(const User& a, const User& b) {
    return 10 - abs(a.rating - b.rating);
}

int main() {

    vector<User> boys = {
        {1,"B1",10,2,false},{2,"B2",7,4,false},
        {3,"B3",4,6,false},{4,"B4",2,9,false},{5,"B5",1,12,false}
    };

    vector<User> girls = {
        {101,"G1",9,3,false},{102,"G2",6,5,false},
        {103,"G3",3,7,false},{104,"G4",2,10,false},{105,"G5",1,14,false}
    };

    priority_queue<pair<int,int>> pq;
    for(int i=0;i<boys.size();i++)
        pq.push({calculatePriority(boys[i]),i});

    cout<<"PRIORITYMATCH RESULTS\n---------------------\n";

    while(!pq.empty()){
        int i = pq.top().second;
        pq.pop();
        if(boys[i].matched) continue;

        int bestGirl=-1,bestScore=-1;
        for(int j=0;j<girls.size();j++){
            if(!girls[j].matched){
                int score=compatibilityScore(boys[i],girls[j]);
                if(score>bestScore){
                    bestScore=score;
                    bestGirl=j;
                }
            }
        }
        if(bestGirl==-1) break;

        boys[i].matched=true;
        girls[bestGirl].matched=true;

        cout<<boys[i].name<<" matched with "<<girls[bestGirl].name
            <<" | Compatibility Score: "<<bestScore<<endl;
    }
    return 0;
}