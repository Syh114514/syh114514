#include<iostream>
#include<string.h>
using namespace std;
char rule1[33],rule2[33];		//全局变量（规则集IP） 
char data1[33],data2[33];		//全局变量（数据集IP） 
typedef struct rule_set{		//规则集IP地址 
	int fst;
	int snd;
	int trd;
	int fth;
	int bit;
} rule_ip;
void rule_binary(rule_ip k);	//规则集IP地址二进制转换函数 
void data_binary(long long k);	//数据集IP地址二进制转换函数
void match(char k1[],char k2[]);//IP地址匹配函数 
char data_bi[33],rule_bi[33];
int main(){
	return 0;
} 
void rule1_binary(rule_ip k){	//规则集原IP地址二进制转换函数 
	for(int i=31;i>=24;i--){
		rule1[i]=(char)(k.fth%2+48);
		k.fth/=2;
	}
	for(int i=23;i>=16;i--){
		rule1[i]=(char)(k.trd%2+48);
		k.trd/=2;
	}
	for(int i=15;i>=8;i--){
		rule1[i]=(char)(k.snd%2+48);
		k.snd/=2;
	}
	for(int i=7;i>=0;i--){
		rule1[i]=(char)(k.fst%2+48);
		k.fst/=2;
	}
}
void rule2_binary(rule_ip k){	//规则集目的IP地址二进制转换函数
	//scanf("@%d.%d.%d.%d/%d",&k.fst,&k.snd,&k.trd,&k.fth,&k.bit);
	for(int i=31;i>=24;i--){
		rule2[i]=(char)(k.fth%2+48);
		k.fth/=2;
	}
	for(int i=23;i>=16;i--){
		rule2[i]=(char)(k.trd%2+48);
		k.trd/=2;
	}
	for(int i=15;i>=8;i--){
		rule2[i]=(char)(k.snd%2+48);
		k.snd/=2;
	}
	for(int i=7;i>=0;i--){
		rule2[i]=(char)(k.fst%2+48);
		k.fst/=2;
	}
}
void data1_binary(long long k){	//数据集原IP地址进制转换函数
	data1[32]='\0';
	for(int i=31;i>=0;i--){
		data1[i]=(char)k%2+'0';
		k/=2;
	}
}
void data2_binary(long long k){	//数据集目的IP地址进制转换函数
	data2[32]='\0';
	for(int i=31;i>=0;i--){
		data2[i]=(char)k%2+'0';
		k/=2;
	}
}
int match(){					//IP地址匹配函数 
	if(strcmp(rule1,data1)==0&&strcmp(rule2,data2)==0) return 1;
	else return 0;
}
