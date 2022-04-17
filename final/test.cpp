#include<iostream>
using namespace std;

void assign(int* a){
    for(int i=0;i<3;i++){
        a[i]=10;
    }
}

int main(){
    int arr[3];
    assign(&arr[0]);
    for(int i=0;i<3;i++)
        cout<<arr[i]<<endl;
    return 0;
}