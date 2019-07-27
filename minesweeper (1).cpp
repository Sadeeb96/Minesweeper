#include<bits/stdc++.h>
using namespace std;
char Grid[10][10];
struct Tile
{
    int adjacent_mines;
    bool revealed;
    bool isMine;
};
struct GameState
{
    Tile tiles[10][10];
} s;
void find_adjacent(int x,int y)
{
    int dy[]= {1,-1,0,0,1,-1,1,-1};
    int dx[]= {0,0,1,-1,1,-1,-1,1};
    int c=0;
    for(int i=0; i<8; i++)
    {
        if(x+dx[i]>=1 && x+dx[i]<=9 && y+dy[i]>=1 && y+dy[i]<=9)
        {
            //cout<<s.tiles[x+dx[i]][y+dy[i]].isMine<<" ";
            if(s.tiles[x+dx[i]][y+dy[i]].isMine==true)
                c++;
        }
    }
    if(c>0)
    {
        Grid[x][y]=c+'0';
        s.tiles[x][y].revealed=true;
        return;
    }
    else
    {
        Grid[x][y]='0';
        s.tiles[x][y].revealed=true;
        for(int i=0; i<8; i++)
        {
            if(x+dx[i]>=1 && x+dx[i]<=9 && y+dy[i]>=1 && y+dy[i]<=9)
            {
                if(s.tiles[x+dx[i]][y+dy[i]].isMine==false && s.tiles[x+dx[i]][y+dy[i]].revealed==false)
                {
                   // cout<<x+dx[i]<<" "<<y+dy[i]<<endl;
                    find_adjacent(x+dx[i],y+dy[i]);
                }
            }
        }
    }

}
void expand(int x,int y)
{
    int dy[]= {1,-1,0,0,1,-1,1,-1};
    int dx[]= {0,0,1,-1,1,-1,-1,1};
    queue<int> q;
    q.push(x);
    q.push(y);
    while(!q.empty())
    {
        int a=q.front();
        q.pop();
        int b=q.front();
        q.pop();
        int c=0;
        for(int i=0; i<8; i++)
        {

            if(a+dx[i]>=1 && a+dx[i]<=9 && b+dy[i]>=1 && b+dy[i]<=9)
            {
                if(s.tiles[a+dx[i]][b+dy[i]].isMine==true)
                {
                    c++;
                }
            }
        }
        Grid[a][b]=c+'0';
        //s.tiles[a][b].revealed=true;
        if(c==0)
        {
            Grid[a][b]='0';
            // s.tiles[a][b].revealed=true;
            for(int i=0; i<8; i++)
            {

                if(a+dx[i]>=1 && a+dx[i]<=9 && b+dy[i]>=1 && b+dy[i]<=9)
                {
                    q.push(a+dx[i]);
                    q.push(b+dy[i]);
                }
            }
        }
        else
        {
            return;
        }
    }
}
void place_mine()
{
    for(int i=0; i<10; i++)
    {
        int x,y;
        do
        {
            x=1+rand()%9;
            y=1+rand()%9;
        }
        while(s.tiles[x][y].isMine==true);
        s.tiles[x][y].isMine=true;
    }
}
void printBoard()
{
    for(int i=0; i<=9; i++)
    {
        if(i>0)
        {
            char x='A'+i-1;
            cout<<x;
        }
        for(int j=0; j<=9; j++)
        {
            if(i==0)
            {
                //if(j==0){cout<<"";continue;}
                if(j==0)
                    cout<<"  ";
                else
                {
                    cout<<j;
                }
            }
            else
            {
                cout<<Grid[i][j];
            }
        }
        cout<<endl;
    }
}
bool complete()
{
    for(int i=1; i<=9; i++)
    {
        for(int j=1; j<=9; j++)
        {
            if(s.tiles[i][j].revealed==false && s.tiles[i][j].isMine==false)
                return false;
                //cout<<i<<" "<<j<<endl;
        }
    }
    return true;

}
bool winner()
{
    for(int i=1; i<=9; i++)
    {
        for(int j=1; j<=9; j++)
        {
            if(Grid[i][j]!='+' && s.tiles[i][j].isMine)
              //  cout<<i<<"x"<<j<<endl;
            return false;
        }
    }
    return true;
}
int main()
{
    place_mine();
    for(int i=1; i<=9; i++)
    {
        for(int j=1; j<=9; j++)
        {
            cout<< s.tiles[i][j].isMine;
            // Grid[i][j]='*';
           // if(s.tiles[i][j].isMine)
             //   Grid[i][j]='+';
        }
        cout<<endl;
    }
   // winner();

    clock_t start=clock();
    while(!complete() && !winner())
    {
        printBoard();
        cout<<endl;
        cout<<"Choose an Option:"<<endl;
        cout<<"<R> Reveal Tile"<<endl;
        cout<<"<P> Put Flag"<<endl;
        cout<<"<R> Quit"<<endl;
        cout<<"Option(R,P,Q):";
        char o;
        cin>>o;
        if(o=='R')
        {
            char a;
            int x,y;
            cout<<"Enter Tile Cordinate:";
            cin>>a>>y;
            x=a-64;
            if(s.tiles[x][y].revealed==true)
            {
                cout<<"Error: Already Revealed"<<endl;
            }
            else if(s.tiles[x][y].isMine==true)
            {
                cout<<"Game Over";
                break;
            }
            expand(x,y);
            s.tiles[x][y].revealed=true;
        }
        if(o=='P')
        {
            char a;
            int x,y;
            cout<<"Input:";
            cin>>a>>y;
            x=a-64;
            Grid[x][y]='+';
        }
        if(o=='Q')
        {
            break;
        }
    }
    double duration=clock()-start;
    if(winner())
    {
        cout<<"Congratulations! You have Located all mines.";
        cout<<"You won in"<<duration/1000<<" seconds!"<<endl;
    }
}
