#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define LEN 100
int a[LEN][LEN];
int str_int(string str, int n, int len){
	string tmp(str.begin()+n, str.begin()+n+len+1);
	int value;
	stringstream os;
	os<<tmp;
	os>>value;
	return value;
}

int split(string str, int n, int k){
	int max = 0, tmp = 0;
	if(k == 1){
		if(a[n][k] == 0)
			a[n][k] = str_int(str, n, str.size()-n);
		return a[n][k];
	}
	for(int i=0 ; i<=str.size()-n-k; i++){
		if(a[n+i+1][k-1] == 0)
			tmp = str_int(str, n, i)*split(str, i+n+1, k-1);
		else tmp = str_int(str, n, i)*a[n+i+1][k-1];
		if(max < tmp)
			max = tmp;
	}
	a[n][k] = max;
	return max;
}
int main(void){
	string str;
	int max, k;
	cout<<"please input str:"<<endl;
	cin>>str;
	cout<<"please input k:"<<endl;
	cin>>k;
	max = split(str, 0, k);
	cout<<"max:"<<max<<endl;
	return 0;
}
