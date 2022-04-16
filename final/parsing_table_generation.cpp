#include<iostream>
using namespace std;

class production{
    int nonterminal;
    int rules[20];
    int length;
    public:
        int getnonterminal(){
            return nonterminal;
        }
        int* getrules(){
            return rules;
        }
        int getlength(){
            return length;
        }
};



/*this is for one single production A->ABa like that*/
class prod_lr0{
    int nonterminal;
    int rule[20];
    int length;
    int left_of_production;
    public:
        prod_lr0(){
            left_of_production=-1;
        }
        int getnonterminal(){
            return nonterminal;
        }
        int* getrules(){
            return rule;
        }
        int getleft_of_production(){
            return left_of_production;
        }
        int getlength(){
            return length;
        }
        void putdott(int left_of_production){
            this->left_of_production=left_of_production;
        }
        void getdata(int nonterminal,int* rule,int length){
            this->nonterminal=nonterminal;
            for(int i=0;i<length;i++){
                this->rule[i]=rule[i];
            }
            this->length=length;
        }
        bool compare(prod_lr0 production){
            if(production.getnonterminal()!=nonterminal || production.getlength()!=length || production.getleft_of_production()!=left_of_production)
                return false;
            for(int i=0;i<length;i++){
                if(production.rule[i]!=rule[i])
                    return false;
            }
            return true;
        }
};

/*it is for lr0 items eg A->.BCa,B->.bAC*/
class lr0item{
    prod_lr0 rules[100];
    int length;
    public:
        lr0item(){
            length=0;
        }
        prod_lr0* getproduction(){
            return rules;
        }
        void additem(prod_lr0 rule){
            rules[length++]=rule;
        }
        bool compare(lr0item item){
            if (item.length!=length)
                return false;
            for(int i=0;i<length;i++){
                if(!rules[i].compare(item.getproduction()[i]))
                    return false;
            }
            return true;
        }

};

//it is the final item set;
class lr0itemset{
    lr0item item[100];
};

lr0itemset lr0generation(production* productions,int length){
        prod_lr0 items[100];
        for(int i=0;i<length;i++){
            items[i].getdata(productions[i].getnonterminal(),productions[i].getrules(),productions[i].getlength());
        }

}


//prod_lr0------lr0item-----lr0itemset
int main(){
    // cout<<"hello world";
    production p[100];

    return 0;
}