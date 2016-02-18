#include<iostream>
using namespace std;
int debug;
int arr[9][9];
int done[9][9];
int row[9],col[9],box[9];
//sample input->
//530070000
//600195000
//098000060
//800060003
//400803001
//700020006
//060000280
//000419005
//000080079
int bno(int x,int y)//given row,column find the box number it is in [0-8]
{
	int di=x/3;
	int dx=y/3;
	return di*3+dx;
}
int log(int x)//[find log base 2 of x]
{
	for(int i=0;i<9;i++)
	{
		if((1<<i)==x)
		return i+1;
	}
	return 0;
}
bool rec(int i,int j)//rec function
{
		if(j>=9)
		{
			i++;
			j=0;
		}
		if(debug)//for nice number jumble
		{
			cout<<i<<" "<<j<<endl;
			for(int i=0;i<9;i++)
			{
				for(int j=0;j<9;j++)
				cout<<(done[i][j]?arr[i][j]:log(arr[i][j]))<<" "<<(j%3==2?" ":"");
				cout<<endl<<(i%3==2?"\n":"");
			}
			system("cls");	
		}
	if(i>=9)//done
	{
		return true;
	}
	else
	{
		if(done[i][j])//cannot touch the input
			return rec(i,j+1);
		else
		{
			int allowed=(1<<9)-1;//max possible values
			allowed=allowed&(~(row[i]|col[j]|box[bno(i,j)]));//remove invalid values 
			while(allowed)
			{
				int val=allowed&(-allowed);//get the last bit
				int br=row[i];//next 3 lines are saving data
				int bc=col[j];
				int bb=box[bno(i,j)];
				row[i]|=val;
				col[j]|=val;
				box[bno(i,j)]|=val;//next 3 lines get new mask
				allowed-=val;
				arr[i][j]=val; 
				if(rec(i,j+1))//recurse over new possibility
				{
					return true;//got it!!!
				}
				arr[i][j]=0;//next 4 lines put back the values
				row[i]=br;
				col[j]=bc;
				box[bno(i,j)]=bb;
			}
		}
		return false;
	}
}
int main()
{
	//input 0 or " " for no value;
	cout<<"input 0 or space for empty box\n";
	cout<<"**123456789\n";
	for(int i=0;i<9;i++)
	{
		cout<<i+1<<"-";
		string s;
		getline(cin,s);
		for(int j=0;j<s.length();j++)
		{
			if(s[j]>'0' && s[j]<='9')
			{
				arr[i][j]=(s[j]-'0');
				done[i][j]=1;
				row[i]|=1<<(s[j]-'0'-1);
				col[j]|=1<<(s[j]-'0'-1);
			}
		}
	}
	cout<<"do you want to see the numbers getting jumbled ?? 1/0"<<endl;
	cin>>debug;
	if(!rec(0,0))
	{
		cout<<"no solution"<<endl;
		return  0;
	}
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		cout<<(done[i][j]?arr[i][j]:log(arr[i][j]))<<" "<<(j%3==2?" ":"");
		cout<<endl<<(i%3==2?"\n":"");
	}
	return 0;
}
