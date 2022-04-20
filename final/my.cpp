#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
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

lr0itemset generate(vector<production>p){
    map<int,vector<vector<int>>>rules;
    vector<lr0item>items;
    lr0item first,second;
    for(auto i:p){
        rules[i.getnonterminal()].push_back(i.getrules());
        prod_lr0 pdt;
        pdt.getdata(i.getnonterminal(),i.getrules());
        first.additem(pdt);
    }
    items.push_back(first);
    first.print();
    cout<<endl<<endl;


    //produce itemset
    map<int,vector<prod_lr0>>temp;
    for(auto i:first.getproduction()){
        if(i.getrules().size()>i.getleft_of_production()+1){
            i.putdott(i.getleft_of_production()+1);
            temp[i.getrules()[i.getleft_of_production()]].push_back(i);
        }
    }
    lr0itemset itemset;
    for(auto i:temp){
        lr0item temp1;
        int symbol=i.first;
        queue<int> q;
        for(auto j:i.second){
            temp1.additem(j);
            if(j.getleft_of_production()+1<j.getrules().size()){
                q.push(j.getrules()[j.getleft_of_production()+1]);
            }
        }
        while(!q.empty()){
            int sym=q.front();
            q.pop();
            for(auto i:rules[sym]){
                q.push(i[0]);
                prod_lr0 pdt;
                pdt.getdata(sym,i);
                temp1.additem(pdt);
            }
        }
        items.push_back(temp1);

        cout<<endl<<endl;
        temp1.print();
        cout<<endl<<endl;
    }
    return itemset;
}


int main(){
    vector<production>pdlist;
    production p;
    p.nonterminal=200;
    p.rules.push_back(201);
    pdlist.push_back(p);
    production p1;
    p1.nonterminal=201;
    p1.rules={202,202};
    pdlist.push_back(p1);
    production p2;
    p2.nonterminal=202;
    p2.rules={203,202};
    pdlist.push_back(p2);
    production p3;
    p3.nonterminal=202;
    p3.rules={204};
    pdlist.push_back(p3);

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