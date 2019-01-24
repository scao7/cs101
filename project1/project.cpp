#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
void print(int array[],int len){
	cout<<"{";
	int i;	
	for(i=0;i<len;i++){
		cout<<array[i];
		if (i!=len-1)	cout<<",";
		else cout<<"}";
	}
	cout<<endl;
}
int main(int argc,char *argv[]){
	int N;
	cin>>N;
	int i;
	int D[N];
	char ch;

	for(i=0;i<N;i++)	cin>>D[i];
	
	int len=1;		//array lenth
	for(i=0;i<N;i++)	len=len*D[i];

	int array[len];
///////////////////////////////////////////////////////////////////////////
	if (N==1){
	for(i=0;i<D[0];i++){	
		cin>>ch;
		cin>>array[i];
	}
	cin>>ch;	
	int move[2];
	int count=0;
	cout<<count<<": ";
	if (argc==1)	print(array,len);	
	while(!feof(stdin)){
		count++;
	cin>>move[0]>>move[1];
		int pos;
		for(i=0;i<D[0];i++){
			if (array[i]==0){
				pos=i;
			}
		}
		cout<<count<<": ";
		if (move[0]==0){
			while(move[1]<0){
				move[1]=D[0]+move[1];
			}
			if (move[1]>=0){
				array[pos]=array[(pos+move[1])%D[0]];
				array[(pos+move[1])%D[0]]=0;
			}
		}	
		if (argc==1)	print(array,len);
		
	
		int flag=0;
		for(i=1;i<D[0];i++){
			if (array[i-1]<=array[i])	flag++;
		}
		if (flag==D[0]-1)	cout<<"Success after "<<count<<" move"<<endl;
		}
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (N==2){
		int k=0;
		int i,j;
		for(i=0;i<D[0];i++){
			cin>>ch;
			for(j=0;j<D[1];j++){
				cin>>ch;
				cin>>array[k];
				k++;
			}
			cin>>ch;
		}
		cin>>ch;	
////////////////////////////////////////////////////////////////////////////
		int move[2];
		int count=0;
		k=0;
		cout<<count<<": ";
		for(i=0;i<D[0];i++){
			if (i==0) cout<<"{";
			else cout<<",";
			for(j=0;j<D[1];j++){
				if (j==0)	cout<<"{";
				else cout<<",";
				cout<<array[k];
				k++;
			}
			cout<<"}";
		}
		cout<<"}";
		cout<<endl;
		while(!feof(stdin)){
		count++;
		cin>>move[0]>>move[1];
			int pos;
			k=0;
		for(i=0;i<D[0]*D[1];i++){
			if (array[i]==0)	pos=i;
			}
			

		if (move[0]==0){
			while (move[1]<0){
				move[1]=move[1]+D[0];	
			}
			if (move[1]>=0){
				array[pos]=array[(pos+move[1]*D[1])%len];
				array[(pos+move[1]*D[1])%len]=0;
			}
		}
		else if (move[0]==1){
			while(move[1]<0){
				move[1]=D[1]+move[1];
			}
			if (move[1]>=0){
				array[pos]=array[(pos+move[1])%D[1]+(pos/D[1])*D[1]];
				array[(pos+move[1])%D[1]+(pos/D[1])*D[1]]=0;
			}
		}	

//////////////////////////////////////////////////////////////////////////////////
		k=0;
		cout<<count<<": ";
		for(i=0;i<D[0];i++){
			if (i==0) cout<<"{";
			else cout<<",";
			for(j=0;j<D[1];j++){
				if (j==0)	cout<<"{";
				else cout<<",";
				cout<<array[k];
				k++;
			}
			cout<<"}";
		
		
		}
		cout<<"}";		
		cout<<endl;
		int flag=0;
		for(i=1;i<len;i++){
			if (array[i-1]<=array[i])	flag++;
		}
		if (flag==len-1)	cout<<"Success after "<<count<<" move"<<endl;
		}
}
return 0;
}
