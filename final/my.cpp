#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
#include <unistd.h>
using namespace std;

class production{
    public:
    int nonterminal;
    vector<int>rules;
        void setrules(vector<int>v){
            this->rules=v;
        }
        void setnonterminal(int n){
            this->nonterminal=n;
        }
        int getnonterminal(){
            return nonterminal;
        }
        vector<int> getrules(){
            return rules;
        }
};


/*this is for one single production A->ABa like that*/
class prod_lr0{
    int nonterminal;
    vector<int>rule;
    int left_of_production;
    public:
        prod_lr0(){
            left_of_production=-1;
        }
        prod_lr0(const prod_lr0 &p){
            nonterminal=p.nonterminal;
            rule=p.rule;
            left_of_production=p.left_of_production;

        }
        int getnonterminal(){
            return nonterminal;
        }
        vector<int> getrules(){
            return rule;
        }
        int getleft_of_production(){
            return left_of_production;
        }
        void putdott(int left_of_production){
            this->left_of_production=left_of_production;
        }
        void getdata(int nonterminal,vector<int>rule){
            this->nonterminal=nonterminal;
            this->rule=rule;
        }
        bool compare(prod_lr0 production){
            if(production.getnonterminal()!=nonterminal || production.getleft_of_production()!=left_of_production)
                return false;
            if(rule==production.rule)
                return true;
            else
                return false;
        }
};

/*it is for lr0 items eg A->.BCa,B->.bAC*/
class lr0item{
    vector<prod_lr0> rules;
    public:
        lr0item(const lr0item &l){
            rules=l.rules;
        }
        lr0item(){}
        vector<prod_lr0> getproduction(){
            return rules;
        }
        void additem(prod_lr0 rule){
            rules.push_back(rule);
        }
        bool compare(lr0item item){
            if (item.getproduction().size()!=rules.size())
                return false;
            for(int i=0;i<rules.size();i++){
                if(!rules[i].compare(item.getproduction()[i]))
                    return false;
            }
            return true;
        }
        void print(){
            for(auto j:rules){
                cout<<j.getnonterminal()<<"->"<<'\t';
                for(auto k:j.getrules()){
                    cout<<k<<'\t';
                }
                cout<<j.getleft_of_production();
                cout<<endl;
            }
        }
};

//it is the final item set;
class lr0itemset{
    public:
    vector<lr0item> item;
    map<int,map<int,lr0item>>itemset;
};


int addproduction(){

    return 0;
}


void generateset(vector<lr0item>&items,int& checked,map<int,vector<vector<int>>>&rules,map<int,map<int,int>>&final_map){
    map<int,vector<prod_lr0>>temp;
    lr0item first=items[++checked];
    for(auto i:first.getproduction()){
        if(i.getrules().size()>i.getleft_of_production()+1){
            i.putdott(i.getleft_of_production()+1);
            temp[i.getrules()[i.getleft_of_production()]].push_back(i);
        }
    }
    for(auto i:temp){
        lr0item temp1;
        int symbol=i.first;
        queue<int> q;
        map<int,bool>checked_nonterminal;
        for(auto j:i.second){
            temp1.additem(j);
            if(j.getleft_of_production()+1<j.getrules().size()){
                    q.push(j.getrules()[j.getleft_of_production()+1]);
            }
        }
        cout<<"hello world"<<symbol<<endl;
        while(!q.empty()){
            // cout<<"hello world";
            // sleep(0.5);
            int sym=q.front();
            cout<<sym<<'\t';
            q.pop();
            if(checked_nonterminal[sym]==false){
                for(auto i:rules[sym]){
                    if(checked_nonterminal[i[0]]==false)
                        q.push(i[0]);
                    prod_lr0 pdt;
                    pdt.getdata(sym,i);
                    temp1.additem(pdt);
                }
                checked_nonterminal[sym]=true;   
            }
        }
        int index=items.size();
        bool has=false;
        for(int i=0;i<items.size();i++){
            if(temp1.compare(items[i])){
                has=true;
                index=i;
            }
        }
        if(has==false)
            items.push_back(temp1);
        final_map[checked][symbol]=index;
        cout<<endl<<endl;
        temp1.print();
        cout<<endl<<endl;
    }
}

lr0itemset generate(vector<production>p){
    lr0itemset itemset;
    int checked=-1;
    map<int,map<int,int>> final_map;
    map<int,vector<vector<int>>>rules;
    vector<lr0item>items;
    lr0item first;
    for(auto i:p){
        rules[i.getnonterminal()].push_back(i.getrules());
        prod_lr0 pdt;
        pdt.getdata(i.getnonterminal(),i.getrules());
        first.additem(pdt);
    }
    items.push_back(first);
    first.print();
    cout<<endl<<endl;
    while (checked<int(items.size())){
        generateset(items,checked,rules,final_map);
    }

    cout<<endl<<endl<<"final items"<<endl<<endl;
    for(auto i:items){
        cout<<endl;
        i.print();
        cout<<endl;
    }
    for(auto i:final_map){
        cout<<i.first<<endl;
        for(auto j:i.second){
            cout<<j.first<<"::::::"<<j.second<<endl;
        }
        cout<<endl;
    }
    return itemset;
}


int main(){
    vector<production>pdlist(7);
    // production p;
    // p.nonterminal=200;
    // p.rules.push_back(201);
    // pdlist.push_back(p);
    // production p1;
    // p1.nonterminal=201;
    // p1.rules={202,202};
    // pdlist.push_back(p1);
    // production p2;
    // p2.nonterminal=202;
    // p2.rules={203,202};
    // pdlist.push_back(p2);
    // production p3;
    // p3.nonterminal=202;
    // p3.rules={204};
    // pdlist.push_back(p3);

    pdlist[0].nonterminal=200;
    pdlist[0].rules={201};
    pdlist[1].nonterminal=201;
    pdlist[1].rules={201,202,203};
    pdlist[2].nonterminal=201;
    pdlist[2].rules={203};
    pdlist[3].nonterminal=203;
    pdlist[3].rules={203,204,205};
    pdlist[4].nonterminal=203;
    pdlist[4].rules={205};
    pdlist[5].nonterminal=205;
    pdlist[5].rules={206,201,207};
    pdlist[6].nonterminal=205;
    pdlist[6].rules={208};

    lr0itemset final=generate(pdlist);

    return 0;
}





   // for(auto i:temp){
    //     cout<<endl<<endl<<i.first<<endl;
    //     for(auto j:i.second){
    //         cout<<j.getnonterminal()<<"->"<<'\t';
    //         for(auto k:j.getrules()){
    //             cout<<k<<'\t';
    //         }
    //         cout<<j.getleft_of_production();
    //     }
    // }
