#include<bits/stdc++.h>
#define process 5
#define resources 4
using namespace std;

bool is_available(int available[],int need[][resources],int p)
{
    bool flag = true;
    for(int i=0; i<resources; i++)
        flag = flag && (available[i]>=need[p][i]);

    return flag;
}

void PrintSafeSequence(vector<int> safe,bool completed[],int available[],int allocated[][resources],int need[][resources])
{
    for(int i=0; i<process; i++)
    {
        if(!completed[i] && is_available(available,need,i))
        {
            completed[i]=true;
            for(int j=0; j<resources; j++)
            {
                available[j]+=allocated[i][j];
            }
            safe.push_back(i);
            PrintSafeSequence(safe,completed,available,allocated,need);
            safe.pop_back();
            for(int j=0; j<resources; j++)
            {
                available[j]-=allocated[i][j];
            }
            completed[i]=false;
        }
    }

    if(safe.size()==process)
    {
        cout<<"\n --> ";
        for(int i=0; i<process; i++)
        {
            cout<<" "<<safe[i];
        }
    }
}
int main()
{
    int i,j;
    int allocated[process][resources]= {{0,1,1,0},{1,2,3,1},{1,3,6,5},{0,6,3,2},{0,0,1,4}};
    int Max[process][resources]= {{0,2,1,0},{1,6,5,2},{2,3,6,6},{0,6,5,2},{0,6,5,6}};
    int available[resources]= {1,5,2,0};
    int need[process][resources]= {0};
    for(i=0; i<process; i++)
    {
        for(j=0; j<resources; j++)
        {
            need[i][j] = Max[i][j]-allocated[i][j];
        }
    }
    bool completed[process];
    vector<int> safe;
    memset(completed,false,sizeof(completed));
    cout<<"\n The safe sequences are : \n";
    PrintSafeSequence(safe,completed,available,allocated,need);
    cout<<"\n\n";
    return 0;
}
