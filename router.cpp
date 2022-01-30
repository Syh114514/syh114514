#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
char rule1[33],rule2[33];					//全局变量（二进制规则集IP） 
char data1[33],data2[33];					//全局变量（二进制数据集IP） 
typedef struct ruleip{						//规则集IP地址 
	char at;
	int fst;
	char dot1;
	int snd;
	char dot2;
	int trd;
	char dot3;
	int fth;
	char slash;
	int bit;
} rule_ip;
typedef struct ruleset{						//规则集 
	rule_ip ip1,ip2;						//规则集原IP、目的IP
	char colon1,colon2,slash2;				//冒号1、冒号2、斜杠 
	int rule_port1,rule_port2,rule3,rule4; 	//规则集源端口、目的端口  
	int rule_protocol1,rule_protocol2;		//规则集协议
} rule_set;
typedef struct dataset{						//数据集 
	long long ip1,ip2;						//数据集原IP、目的IP
	int data_port1,data_port2;				//数据源、目的端口
	int data_protocol;						//数据集协议
} data_set;
ifstream infile;							//读入式文件输入 
void input_rule(rule_set rule[]);			//规则集输入函数
void input_data(data_set data[]);			//数据集输入函数
void rule_binary(rule_ip k);				//规则集IP地址二进制转换函数 
void data_binary(long long k);				//数据集IP地址二进制转换函数
int match(char k1[],char k2[]);				//IP地址匹配函数 
int port(int port1,int port2,int port3);	//端口匹配函数 
int protocol(int pro1,int pro2,int pro3);	//协议匹配函数 
int main(){ 								//主函数 
	rule_set rule[1000];
	data_set data[30000];
	return 0;
}
void input_rule(rule_set rule[]){			//规则集输入函数 
	infile.open("rule1.txt");
	if(!infile.is_open()){
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(-1);
	}
	int count=0;			//计数器 
	while(1){
		infile>>rule[count].ip1.at;
		if(infile.eof()){
			break;
		}
		infile>>rule[count].ip1.fst;
		infile>>rule[count].ip1.dot1;
		infile>>rule[count].ip1.snd;
		infile>>rule[count].ip1.dot2;
		infile>>rule[count].ip1.trd;
		infile>>rule[count].ip1.dot3;
		infile>>rule[count].ip1.fth;
		infile>>rule[count].ip1.slash;
		infile>>rule[count].ip1.bit;
		infile>>rule[count].ip2.fst;
		infile>>rule[count].ip2.dot1;
		infile>>rule[count].ip2.snd;
		infile>>rule[count].ip2.dot2;
		infile>>rule[count].ip2.trd;
		infile>>rule[count].ip2.dot3;
		infile>>rule[count].ip2.fth;
		infile>>rule[count].ip2.slash;
		infile>>rule[count].ip2.bit;
		infile>>rule[count].rule_port1;
		infile>>rule[count].colon1;
		infile>>rule[count].rule_port2;
		infile>>rule[count].rule3;
		infile>>rule[count].colon2;
		infile>>rule[count].rule4;
		infile>>hex>>rule[count].rule_protocol1;
		infile>>rule[count].slash2;
		infile>>hex>>rule[count].rule_protocol2;
		count++;
	}
	infile.close();
}
void input_data(data_set data[]){			//数据集输入函数
	infile.open("packet1.txt");
	if(!infile.is_open()){
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(-1);
	}
	int count=0;
	while(1){
		infile>>data[count].ip1;
		if(infile.eof()){
			break;
		}
		infile>>data[count].ip2;
		infile>>data[count].data_port1;
		infile>>data[count].data_port2;
		infile>>hex>>data[count].data_protocol;
		count++;
	}
	infile.close();
} 
void rule1_binary(rule_ip k){				//规则集原IP地址二进制转换函数 
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
void rule2_binary(rule_ip k){				//规则集目的IP地址二进制转换函数
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
void data1_binary(long long k){				//数据集原IP地址进制转换函数
	data1[32]='\0';
	for(int i=31;i>=0;i--){
		data1[i]=(char)k%2+'0';
		k/=2;
	}
}
void data2_binary(long long k){				//数据集目的IP地址进制转换函数
	data2[32]='\0';
	for(int i=31;i>=0;i--){
		data2[i]=(char)k%2+'0';
		k/=2;
	}
}
int match(){								//IP地址匹配函数 
	if(strcmp(rule1,data1)==0&&strcmp(rule2,data2)==0) return 1;
	else return 0;
}
int port(int port1,int port2,int port3){	//端口匹配函数 
	if(port3>=port1&&port3<=port2) return 1;
	else return 0;
}
int protocol(int pro1,int pro2,int pro3){	//协议匹配函数 
	switch(pro2){
		case 0x00:
			return 1;
		case 0xFF:
			if(pro1==pro3) return 1;
			else return 0;
	}
}
