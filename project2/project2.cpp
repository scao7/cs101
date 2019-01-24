#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

string sort(string str){
	int i;
	int len=str.length();
	for(i=0;i<len;i++){
		for(int j=0;j<len-i-1;j++){
			if (str[j]>str[j+1]){
				int temp=str[j];
				str[j]=str[j+1];
				str[j+1]=temp;
			}
		}
	}
	return str;
}

int main(){
	string allStr[1000001];
	string str;
	int i=0;
	while(!feof(stdin)){
		getline(cin,str);
		allStr[i]=str;
		i++;	
	}

/////////////////////////////////////////////////////////////
	int x=0,y;
	int max=0;
	while (x<i){
	int rep=0;
		for(y=x;y<i;y++){
			if (sort(allStr[x])==sort(allStr[y])){
				rep++;
			}
		}

		if (rep>max)	max=rep;	
		x++;
	}
////////////////
	for(x=0;x<i;x++){
		for(y=0;y<i-x-1;y++){
			if (allStr[y]>allStr[y+1]){
				string temp=allStr[y];
				allStr[y]=allStr[y+1];
				allStr[y+1]=temp;
			}
		}
	}

	
	

///////////////
	x=0;
	while(x<i){
		int rep=0;
		for(y=x;y<i;y++){
			if (sort(allStr[x])==sort(allStr[y])){
				rep++;
			}
		} 
		
		if (max==rep){
			cout<<max<<endl;
		for(y=x;y<i;y++){
			if (sort(allStr[x])==sort(allStr[y])){
				cout<<allStr[y]<<endl;
			}
		} 
		}
		x++;	
	}

					
return 0;
}
