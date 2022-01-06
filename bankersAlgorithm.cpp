//created by Amir Hossein Rafati 930122610015
#include <iostream>

using namespace std;
//____________________________________
int P;
int R;
void print(int**,int**,int**,int*);
//_____________________________________
//need Matrix :
void needCal(int **need,int **max,int **alloc){
    for (int i=0;i<P;i++)
        for(int j=0;j<R;j++)
            need[i][j]=max[i][j]-alloc[i][j];
}
//avail Array :
void availCal(int *avail,int **alloc,int *res){
    for(int i=0;i<R;i++)
        for(int j=0;j<P;j++)
            avail[i]+=alloc[j][i];
    //avail:
    for(int m=0;m<R;m++) avail[m]=res[m]-avail[m];
}
//_____________________________________
//Safe Check :
bool safeMode(int *proc,int *avail,int **alloc,int **max,int **need)
{
    //control proc finish
    bool finish[P]={0};
    //store checking order
    int stOrder[P];
    //copy of avail;
    int work[R];
    for (int i=0;i<R;i++) work[i]=avail[i];
    //
    int eFlag=0; //end flag
    int cnt=0;//finished counter
    //while for checking each proc 
    while(cnt < P && eFlag==0)
    {
        bool find=false;
        for (int p=0;p<P;p++)
        {
            if (finish[p]==0)
            {
                int r;
                for(r=0;r<R;r++)
                    if(need[p][r] > work[r]) 
                        break;
                
                if (r==R) {
                    for (int j=0;j<R;j++)
                        work[j]+=alloc[p][j];

                    stOrder[cnt++]=p;
                    finish[p]=1;
                    find=true;
                }
            }
        }
        //check end
        if (find==false) {
            cout<<"System Not Safe";
            eFlag=1;
            return false;
        }
    }
    if (eFlag==0) {
    cout << "System Is Safe\nOrder: ";
    for (int i = 0; i < P ; i++) cout << stOrder[i] <<" ";
        cout<<endl;
        print(alloc,max,need,avail);
        return true;
    }
}
//resReq_______________________________
void resReq(int *proc,int **alloc,int *avail,int **need,int **max,int *req)
{
    bool erFlag=false; //error flag
    //input :
    int pro;
    do {
    cout<<"\nEnter Proc: ";
    cin>>pro;
    }while(pro > P);
    for(int i=0;i<R;i++) {
        cout<<"\nEnter req for Res "<<i<<": ";
        cin>>req[i];
    }
    //Do :
    for(int i=0;i<R;i++)
        if(req[i]>need[pro][i]){
            erFlag=true;
        }
    for(int i=0;i<R;i++)
        if(req[i]>avail[i]){
            erFlag=true;
        }
    if (erFlag==true) cout<<"\nError\n";
    //no error :
    if (erFlag==false){
        for(int i=0;i<R;i++){
            avail[i]-=req[i];
            alloc[pro][i]+=req[i];
            need[pro][i]-=req[i];
        }
        //
        cout<<"for Process: "<<pro<<" and Reqs: ";
        for(int i=0;i<R;i++) cout <<req[i]<<" ";
        //check safe mode :
        bool safe=safeMode(proc,avail,alloc,max,need);
        //if not safe back to past :
        if (safe==false) {
            for(int i=0;i<R;i++){
            avail[i]+=req[i];
            alloc[pro][i]-=req[i];
            need[pro][i]+=req[i];
            }
        }
        print(alloc,max,need,avail);
    }
}
//_____________________________________
//matrix init :
matrix(int **alloc,int **max,int **need){
    //make 2D :
    for(int i=0;i<P;i++) 
    {
        alloc[i]=new int[R];
        max[i]=new int[R];
        need[i]=new int[R];
    }
    //put 0 :
    for (int k=0;k<P;k++)
        for(int l=0;l<R;l++)
        {
            alloc[k][l]=0;
            max[k][l]=0;
            need[k][l]=0;
        }
}
//____________________________________
//input :
void input(int **alloc,int **max,int **need,int *res,int *avail)
{
    cout<<"\nAllocation_______________\n";
    for (int k=0;k<P;k++) {
        for(int l=0;l<R;l++)
        {
            cout<<"P: "<<k<<" res: "<<l<<" =>";
            cin>>alloc[k][l];
        }
        cout<<"\n-------------------------\n";
    }
    cout<<"\nMaximom__________________\n";
    for (int k=0;k<P;k++) {
        for(int l=0;l<R;l++)
        {
            cout<<"P: "<<k<<" res: "<<l<<" =>";
            cin>>max[k][l];
        }
        cout<<"\n-------------------------\n";
    }

    cout<<"\nEnter Resources:\n";
    for(int i=0;i<R;i++) cin>>res[i];
}
//____________________________________
void print(int **alloc,int **max,int **need,int *avail){
    cout<<"\nAllocMatrix:\n";
    for (int k=0;k<P;k++) {
        for(int l=0;l<R;l++)
            cout<<alloc[k][l]<<" ";
        cout<<endl;
    }
    cout<<"\nMaxMatrix:\n";
    for (int k=0;k<P;k++) {
        for(int l=0;l<R;l++)
            cout<<max[k][l]<<" ";
        cout<<endl;
    }
    cout<<"\nNeedMatrix:\n";
    for (int k=0;k<P;k++) {
        for(int l=0;l<R;l++)
            cout<<need[k][l]<<" ";
        cout<<endl;
    }
    cout<<"\nAvailMatrix:\n";
    for (int k=0;k<R;k++) cout<<avail[k]<<" ";
    cout<<endl;
}
//_____________________________________
//main :
int main(){
    //var :
    int m,n; // P:proc R:res
    cout<<"enter Processes # , Resources # : ";
    cin>>m>>n;
    P=m;
    R=n;
    int *proc=new int[P];
    int *res=new int[R];
    int *avail=new int[R];
    int *req=new int[R];
    int **alloc=new int*[P];
    int **max=new int*[P];
    int **need=new int*[P];
    matrix(alloc,max,need);
    bool safe;
    //input :
    for(int i=0;i<P;i++) proc[i]=i;
    for(int i=0;i<R;i++) avail[i]=0;
    for(int i=0;i<R;i++) req[i]=0;
    input(alloc,max,need,res,avail);
/*
    alloc:
    0 1 0
    2 0 0
    3 0 2
    2 1 1
    0 0 2
    __________
    max:
    7 5 3
    3 2 2 
    9 0 2
    2 2 2
    4 3 3
    __________
    res:10 5 7
    avail:3 3 2
*/
    //Processes :
    availCal(avail,alloc,res);
    needCal(need,max,alloc);
    //safe :
    safe=safeMode(proc,avail,alloc,max,need);
    //reReq :
    if (safe==true){
        int yorn; //resReq yes or no
        while(1){
        cout<<"\nRes Req ?(1,0)\n";
        cin>>yorn;
        if(yorn==1) resReq(proc,alloc,avail,need,max,req);
        else exit(0);
        }
    }
    //Debug :
    return 0;
}