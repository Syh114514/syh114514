#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
int count1=0;								//规则计数器  
int count2=0;								//数据计数器  
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
ifstream infile;							//文件输入
ofstream outfile;							//文件输出 
void input_rule(rule_set rule[]);			//规则集输入函数
void input_data(data_set data[]);			//数据集输入函数
void output(rule_set rule[],data_set data[]);//输出函数 
long long rule_dec(rule_ip k);				//规则集IP地址二进制转换函数
int fit(long long num1,long long num2);		//IP地址匹配函数 
int port(int port1,int port2,int port3);	//端口匹配函数 
int protocol(int pro1,int pro2,int pro3);	//协议匹配函数 
int main(){ 								//主函数 
	rule_set rule[1000];
	data_set data[30000];
	input_rule(rule);
	input_data(data);
	output(rule,data);
	return 0;
}
void input_rule(rule_set rule[]){			//规则集输入函数 
	infile.open("rule1.txt");
	if(!infile.is_open()){
		cout<<"文件打开失败"<<endl;
		system("pause");
		exit(-1);
	}
	while(1){
		if(infile.eof()){
			break;
		}
		infile>>rule[count1].ip1.at;
		infile>>dec>>rule[count1].ip1.fst;
		infile>>rule[count1].ip1.dot1;
		infile>>dec>>rule[count1].ip1.snd;
		infile>>rule[count1].ip1.dot2;
		infile>>dec>>rule[count1].ip1.trd;
		infile>>rule[count1].ip1.dot3;
		infile>>dec>>rule[count1].ip1.fth;
		infile>>rule[count1].ip1.slash;
		infile>>dec>>rule[count1].ip1.bit;
		infile>>dec>>rule[count1].ip2.fst;
		infile>>rule[count1].ip2.dot1;
		infile>>dec>>rule[count1].ip2.snd;
		infile>>rule[count1].ip2.dot2;
		infile>>dec>>rule[count1].ip2.trd;
		infile>>rule[count1].ip2.dot3;
		infile>>dec>>rule[count1].ip2.fth;
		infile>>rule[count1].ip2.slash;
		infile>>dec>>rule[count1].ip2.bit;
		infile>>dec>>rule[count1].rule_port1;
		infile>>rule[count1].colon1;
		infile>>dec>>rule[count1].rule_port2;
		infile>>dec>>rule[count1].rule3;
		infile>>rule[count1].colon2;
		infile>>dec>>rule[count1].rule4;
		infile>>hex>>rule[count1].rule_protocol1;
		infile>>rule[count1].slash2;
		infile>>hex>>rule[count1].rule_protocol2;
		count1++;
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
	while(1){
		if(infile.eof()){
			break;
		}
		infile>>dec>>data[count2].ip1;
		infile>>dec>>data[count2].ip2;
		infile>>dec>>data[count2].data_port1;
		infile>>dec>>data[count2].data_port2;
		infile>>dec>>data[count2].data_protocol;
		count2++;
	}
	infile.close();
} 
void output(rule_set rule[],data_set data[]){
	outfile.open("ans1.txt");
	if(!outfile.is_open()){
		cout<<"文件打开失败！"<<endl;
		system("pause");
		exit(-1);
	}int j;
	for(int i=0;i<count2-1;i++){
		for(j=0;j<count1-1;j++){
			if(fit(rule_dec(rule[j].ip1),data[i].ip1)&&fit(rule_dec(rule[j].ip2),data[i].ip2)&&port(rule[j].rule_port1,rule[j].rule_port2,data[i].data_port1)&&port(rule[j].rule3,rule[j].rule4,data[i].data_port2)&&protocol(rule[j].rule_protocol1,rule[j].rule_protocol2,data[i].data_protocol)){
				outfile<<j<<endl;
				break;
			}
		}
		if(j==count1) cout<<"-1"<<endl;
	}
	outfile.close();
}
long long rule_dec(rule_ip k){				//规则集IP地址二进制转换函数
	int rule[32]; 
	for(int i=31;i>=24;i--){
		rule[i]=k.fth%2;
		k.fth/=2;
	}
	for(int i=23;i>=16;i--){
		rule[i]=k.trd%2;
		k.trd/=2;
	}
	for(int i=15;i>=8;i--){
		rule[i]=k.snd%2;
		k.snd/=2;
	}
	for(int i=7;i>=0;i--){
		rule[i]=k.fst%2;
		k.fst/=2;
	}
	long long dec=0,two=1; 
	for(int i=31;i>=0;i--){
		dec+=rule[i]*two;
		two*=2;
	}
	return dec;
}
int fit(long long num1,long long num2){		//IP地址匹配函数 
	if(num1==num2) return 1;
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
