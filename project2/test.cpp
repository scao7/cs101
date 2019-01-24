#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int main(int argc, char *argv[]){
	int num=atoi(argv[1]);
	int len=atoi(argv[2]);
	srand(clock());
	for (int k=0; k<num;k++){
		for(int j=0;j<len;j++){
			char ch=rand()%94 +33;
			cout<<ch;
		}
		cout<<endl;
	}
	return 0;

}
