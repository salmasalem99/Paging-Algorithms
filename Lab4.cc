#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <queue>
#include <vector>
#define EMPTY -5
#include <bits/stdc++.h>
int size=50;
using namespace std;
int n;
void printArr(int buffers[],int n)
{
    for(int j=0;j<n;j++){
        if(buffers[j]!=EMPTY){
            cout << std::setw(2) << std::setfill('0') << buffers[j] << " " ;
        }
    }
    cout << endl;
}
void CLOCK() {
  int val=0;
  int values[size];
  int i=0;
  while(val!=-1){
    cin >> val;
    values[i]=val;
    i++;
  }
  int pages[n];
  int faults=0;
  bool used[n];
  for(int i=0;i<n;i++){
    used[i]=false;
    pages[i]=EMPTY;
  }
  int successful_insert=0;
  int pointer=0;
  cout << "Replacement Policy = CLOCK" << endl ;
  cout <<"-------------------------------------"<<endl;
  cout <<"Page   Content of Frames"<<endl;
  cout <<"----   -----------------"<<endl;
  int m=0;
  while (values[m]!=-1){
    val=values[m];
    m++;
    cout << std::setw(2) << std::setfill('0') << val;
    int hit=0;
    int hit_pos=0;
    //check if val is already in the buffer
    for(int i=0;i<n;i++){
        if(val==pages[i]){
            hit_pos=i;
            hit=1;
            break;
        }
    }
    if(hit==1 || successful_insert<n)
        cout << "     ";
    else{
        cout << " F   ";
        faults++;
    }
    if(hit==1){
        used[hit_pos]=true;
        printArr(pages,n);
    }
    else{
        if(used[pointer]==true)
            pointer+=1;
        if(pointer>=n){
            pointer=0;
            for(int i=0;i<n;i++){
                used[i]=false;
            }
        }
        pages[pointer]=val;
        used[pointer]=true;
        successful_insert++;
        pointer++;
        printArr(pages,n);
    }
  }
  cout << "-------------------------------------" << endl;
  cout << "Number of page faults = " << faults << endl;
}
int getoptimal(int key, vector<int> v,int successful_entries){
    successful_entries+=1;
    int pos=-1;
    int notusedagain = 100000;
    for (auto i = v.begin(); i != v.end(); ++i){
        pos++;
        if(pos>=successful_entries && *i==key){
            return pos;
        }
    }
    return notusedagain;
}
int getLRU(int n,int time[]){
    int maxtime=-10000;
    int pos=0;
    for(int i=0;i<n;i++){
        if(time[i]>maxtime){
            maxtime=time[i];
            pos=i;
        }
    }
    return pos;
}
void LRU() {
  int val=0;
  int values[size];
  int i=0;
  while(val!=-1){
    cin >> val;
    values[i]=val;
    i++;
  }
  int pages[n];
  int faults=0;
  int time[n];
  for(int i=0;i<n;i++){
    time[i]=0;
    pages[i]=EMPTY;
  }
  int successful_insert=0;
  cout << "Replacement Policy = LRU" << endl ;
  cout <<"-------------------------------------"<<endl;
  cout <<"Page   Content of Frames"<<endl;
  cout <<"----   -----------------"<<endl;
  int m=0;
  while (values[m]!=-1){
    val=values[m];
    m++;
    cout << std::setw(2) << std::setfill('0') << val;
    int hit=0;
    int hit_pos=EMPTY;
    //check if val is already in the buffer
    for(int i=0;i<n;i++){
        if(val==pages[i]){
            hit_pos=i;
            hit=1;
            break;
        }
    }
    if(successful_insert<n || hit==1)
        cout << "     ";
    else{
        cout << " F   ";
        faults++;
    }
    if(hit==1){
        printArr(pages,n);
        *(time+hit_pos)=0;
    }
    else{
        if(successful_insert<n){
            pages[successful_insert]=val;
            successful_insert++;
            printArr(pages,n);
        }
        else{
            int pos=getLRU(n,time);
            pages[pos]=val;
            hit_pos=pos;
            successful_insert++;
            printArr(pages,n);
        }
    }
    for(int i=0;i<n;i++){
        if(pages[i]!=EMPTY){
            if(i==hit_pos)
                time[i]=0;
            else
                time[i]++;
        }
    }

  }
  cout << "-------------------------------------" << endl;
  cout << "Number of page faults = " << faults << endl;
}
void OPTIMAL(){
  int val=0;
  int values[size];
  int i=0;
  while(val!=-1){
    cin >> val;
    values[i]=val;
    i++;
  }
  vector<int> res;
  int d=0;
  while (1){
    val=values[d];
    d++;
    //check if eof reached
    if(val==-1){
        break;
    }
    res.push_back(val);
  }
  int pages[n];
  for(int i=0;i<n;i++){
    pages[i]=EMPTY;
  }
  int successwithoutrep=0;
  int successful_insert=0;
  int faults=0;
  cout << "Replacement Policy = OPTIMAL" << endl ;
  cout <<"-------------------------------------"<<endl;
  cout <<"Page   Content of Frames"<<endl;
  cout <<"----   -----------------"<<endl;
  int m=0;
  while(values[m]!=-1){
    val = values[m];
    m++;
    cout << std::setw(2) << std::setfill('0') << val;
    int hit=0;
    //check if val is already in the buffer
    for(int i=0;i<n;i++){
        if(val==pages[i]){
            hit=1;
        }
    }
    if(successwithoutrep<n || hit==1)
        cout << "     ";
    else{
        cout << " F   ";
        faults++;
    }
    if(hit==1){
        successful_insert++;
        printArr(pages,n);
    }
    else{
        if(successful_insert<n){
            pages[successful_insert]=val;
            successwithoutrep++;
            successful_insert++;
            printArr(pages,n);
        }
        else{
            int maxpos=-10000;
            int index=0;
            for(int it=0;it<n;it++){
                int pos=getoptimal(pages[it],res,successful_insert);
                if(pos>maxpos){
                    maxpos=pos;
                    index=it;
                }
            }
            //cout << " " << index << "     ";
            pages[index]=val;
            successful_insert++;
            successwithoutrep++;
            printArr(pages,n);
        }
    }
  }
  cout << "-------------------------------------" << endl;
  cout << "Number of page faults = " << faults << endl;
}
void FIFO(){
  int val=0;
  int values[size];
  int i=0;
  while(val!=-1){
    cin >> val;
    values[i]=val;
    i++;
  }
  int buffers[n];
  int order[n];
  for(int i=0;i<n;i++){
    order[i]=0;
    buffers[i]=EMPTY;
  }
  int order_index=0;
  int successful_insert=0;
  int faults=0;
  cout << "Replacement Policy = FIFO" << endl ;
  cout <<"-------------------------------------"<<endl;
  cout <<"Page   Content of Frames"<<endl;
  cout <<"----   -----------------"<<endl;
  int m=0;
  while (values[m]!=-1){
    val=values[m];
    m++;
    cout << std::setw(2) << std::setfill('0') << val;
    int hit=0;
    //check if val is already in the buffer
    for(int i=0;i<n;i++){
        if(val==buffers[i]){
            hit=1;
        }
    }
    if(successful_insert<n || hit==1)
        cout << "     ";
    else{
        cout << " F   ";
        faults++;
    }
    if(hit==1){
        printArr(buffers,n);
    }
    else{
        if(successful_insert<n){
            buffers[successful_insert]=val;
            order[successful_insert]=order_index;
            successful_insert++;
            order_index++;
            printArr(buffers,n);
        }
        else{
            int minorder=10000;
            int index;
            for(int x=0;x<n;x++){
                if(order[x]<minorder&&buffers[x]!=EMPTY){
                    minorder=order[x];
                    index=x;
                }
            }
            buffers[index]=val;
            order[index]=order_index;
            order_index++;
            successful_insert++;
            printArr(buffers,n);
        }
    }
  }
  cout << "-------------------------------------" <<endl;
  cout << "Number of page faults = "<< faults <<endl;
}
int main () {
    cin >> n;
    string policy;
    cin >> policy;
    if((policy.compare("OPTIMAL"))==0)
        OPTIMAL();
    if(policy.compare("FIFO")==0)
        FIFO();
    if(policy.compare("LRU")==0)
        LRU();
    if(policy.compare("CLOCK")==0)
        CLOCK();
    return 0;
}


