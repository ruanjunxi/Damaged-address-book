// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "json.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool iszhixiashi = false;
string str;//地址信息
string zhixiashi[4] = { "北京","上海","重庆","天津" };
string helper(string key)
{
	//string key = "省";
	string address;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == key[0] && str[i + 1] == key[1]) {//说明此时地址包括“省/市/县”这个字
			int index = i + 1;
			for (int i = 0; i <= index; i++) {
				address += str[i];
			}
			//this->province = province;
			str.erase(0, index + 1);
			return address;
		}
	}
	return "";
}
class Info
{
private:
		string Name;
		string  PhoneNum;
		string province;
		string city;
		string county;
		string town;
		string road;
		string housenum;
		string detail;
		
public: string SetName(string str);
		string SetPhoneNum(string str);
		string GetName();
		string GetPhoneNum();
		string GetProvince();
		string GetCity();
		string GetCounty();
		string GetTown();
		string GetRoad();
		string GetHouseNum();
		string GetDetail();
		void isShenhui();
		void SetProvince();
		void SetCity();
		void SetCounty();
		void SetTown();
		void SetRoad();
		void SetHouseNum();
		void SetDetail();
		
};
void Info::SetCounty()
{
	bool flag = false;
	string key[2] = { "县","区" };
	string address;
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] == key[0][0] && str[i + 1] == key[0][1])||(str[i] == key[1][0] && str[i + 1] == key[1][1])) {//说明此时地址包括"县/区”这个字
			flag = true;
			int index = i + 1;
			for (int i = 0; i <= index; i++) {
				address += str[i];
			}
			if (flag) {
				this->county = address;
			}
			else {
				this->county = "";
			}
			str.erase(0, index + 1);
			break;
		}
	}

}
void Info::isShenhui()
{
	string province;
	province += str[0];
	province += str[1];
	province += str[2];
	province += str[3];
	//cout << province << endl;
	if (province == zhixiashi[0] || province == zhixiashi[1] || province == zhixiashi[2] || province == zhixiashi[3]) {
		iszhixiashi = true;
	}
}
void Info::SetProvince()
{
	if (iszhixiashi) {  //此时为直辖市
		bool flag = false;
		string key = "市";
		string province;
		province += str[0];
		province += str[1];
		province += str[2];
		province += str[3];
		this->province = province;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == key[0] && str[i + 1] == key[1]) {//说明此时地址包括“市”这个字
				str.erase(0, i + 2);
				flag = true;
				break;
			}
		}
		if (!flag) {
			str.erase(0, 4);
		}
	}
	else {
		string key = "省";
		//string province;
		//for (int i = 0; i < str.length(); i++) {
		//	if (str[i] == key[0] && str[i + 1] == key[1]) {//说明此时地址包括“省”这个字
		//		int index = i + 1;
		//		for (int i = 0; i <= index; i++) {
		//			province += str[i];
		//		}
		//		this->province = province;
		//		str.erase(0, index + 1);
		//	}
		//}
		this->province = helper(key);
	}
}
void Info::SetTown()
{
	bool flag = false;
	string key[4] = { "镇","乡","街","道" };
	string address;
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] == key[0][0] && str[i + 1] == key[0][1]) || (str[i] == key[1][0] && str[i + 1] == key[1][1])) {//说明此时地址包括"乡/镇”这个字
			flag = true;
			int index = i + 1;
			for (int i = 0; i <= index; i++) {
				address += str[i];
			}
			if (flag) {
				this->town = address;
			}
			else {
				this->town = "";
			}
			str.erase(0, index + 1);
			break;
		}
		else if (str[i] == key[2][0] && str[i + 1] == key[2][1]) {  //匹配街道
			if (str[i+2] == key[3][0] && str[i + 3] == key[3][1]) {
				flag = true;
				int index = i + 3;
				for (int i = 0; i <= index; i++) {
					address += str[i];
				}
				if (flag) {
					this->county = address;
				}
				else {
					this->county = "";
				}
				str.erase(0, index + 1);
				break;
			}
		}
	}
}
void Info::SetCity()
{
	string key = "市";
	if (iszhixiashi) {  //直辖市直接传值
		this->city = this->province;
		this->city += key;
	}
	else {
		this->city = helper(key);
	}
}
void Info::SetDetail()
{
	this->detail = str;
}
void Info::SetRoad()
{
	string key = "路";
	this->road = helper(key);
}
void Info::SetHouseNum()
{
	string key = "号";
	this->housenum = helper(key);
}
string Info::GetProvince()
{
	return province;
}
string Info::GetCity()
{
	return city;
}
string Info::GetCounty()
{
	return county;
}
string Info::GetTown()
{
	return town;
}
string Info::GetRoad()
{
	return road;
}
string Info::GetHouseNum()
{
	return housenum;
}
string Info::GetDetail()
{
	return detail;
}
string Info::SetName(string str)
{
	string name;
	int count = 0;
	for (int i = 0; i < str.length() - 1; i++)
	{
		if (str[i] == ',') break;
		else {
			count++;
			name += str[i];
		}
	}
	this->Name = name;
	str.erase(0, count + 1);
	return str;
}
string Info:: SetPhoneNum(string str)
{
	int count = 0;
	int index = 0;
	int flag = 0;//退出判断
	string phone;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9' && str[i+1] >= '0' && str[i+1] <= '9')
		{
			count++;
			if (count == 1) {//记录第一个数字的下标
				index = i;
			}
			if (count >= 10) {   //判断出是电话，则从第一个数字开始遍历
				count = 11;
				/*提取出电话号码*/
				for (int j = index;; j++)
				{
					phone += str[j];
					count--;
					if (count == 0) break;
				}
				this->PhoneNum = phone;
				str.erase(index, 11);
			}
		}
		else 
		{
			count = 0;
			index = 0;
		}
	}
	return str;
}
string Info::GetName()
{
	return this->Name;
}
string Info::GetPhoneNum()
{
	return this->PhoneNum;
}
int SetLevel()
{
	int x;
	x = str[0];
	x -= 48;
	return x;
}
Info disposeLevel1(Info info)
{
	info.SetDetail();  //一级地址只需要设置详细地址
	return info;
}
Info disposeLevel2(Info info)
{
	//二级地址需要设置道路信息，门牌号，详细信息
	info.SetRoad();
	info.SetHouseNum();
	info.SetDetail();
	return info;
}
Info dispose(Info info)
{
	int Level;//提取题目难度
	Level = SetLevel();
	str.erase(0, 2);//去除题目难度的字符串
	str = info.SetName(str);//提取name
	str = info.SetPhoneNum(str);//提取电话
	info.isShenhui();
	info.SetProvince();
	info.SetCity();
	info.SetCounty();
	info.SetTown();
	cout << str << endl;
	if (Level == 1) {
		info=disposeLevel1(info);
		//cout << info.detail<< endl;
	}
	else if (Level == 2) {
		info = disposeLevel2(info);
		//cout << info.detail << endl;
	}
	return info;
}
void output(Info info , int level)
{
	Json::StyledWriter writer;
	Json::Value  value;
	value["手机"] = info.GetPhoneNum();
	value["姓名"] = info.GetName();
	if (level == 1) {
		value["地址"].append(info.GetProvince());
		value["地址"].append(info.GetCity());
		value["地址"].append(info.GetCounty());
		value["地址"].append(info.GetTown());
		value["地址"].append(info.GetDetail());
	}
	else if(level==2) {
		value["地址"].append(info.GetProvince());
		value["地址"].append(info.GetCity());
		value["地址"].append(info.GetCounty());
		value["地址"].append(info.GetTown());
		value["地址"].append(info.GetRoad());
		value["地址"].append(info.GetHouseNum());
		value["地址"].append(info.GetDetail());
	}

	ofstream ofs; //标准输出流
	ofs.open("2.json",ios::app); //创建文件
	ofs << value.toStyledString(); //输出
	ofs.close();
	//cout << value.toStyledString() << endl;
	//Json::Value value;
}
int main()
{
	
	ifstream in("1.txt");
	while (!in.eof())
	{
		getline(in, str);
		int level = SetLevel();
		Info info;
		iszhixiashi = false;
		info=dispose(info);
		output(info,level);
		/*cout << info.GetName() << endl;
		cout << info.GetPhoneNum() << endl;
		cout << Level << " " << str << endl;*/
	}
	
	return 0;
	
}
