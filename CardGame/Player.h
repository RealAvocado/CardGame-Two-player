#pragma once
#ifndef _PLAYER
#define _PLAYER
using namespace std;
#include <iostream>
#include<string>
#include"Card.h"
#include<vector>
#include<fstream>
#include <algorithm>    // std::sort
class Player
{
	//friend void sendCard(vector<Player>& player);   //��Ԫ����

private:
	string name;

public:
	int score;
	vector<Card> handCard;

public:
	string getName();
	void setName(string name);
	Player();
	Player(string name);

	void Hit();
	void Fold(Player &p1, Player &p2);
	string showCard();                                                              //��ʾ�Լ��������п�����Ϣ ����[1][4][7]
	bool Quit();                                //�˳���Ϸ
	bool hasPair(vector<Card> vec);                                     //�ж����е����Ƿ��ж���
	bool isMinTie(Player &p1, Player &p2);                             //�����С���ظ��ˣ�tie�������·���
	bool minLargerThanOther(Player& p);        //�ж�this��������Сֵ�Ƿ����other
	vector<Card> sortValue(vector<Card> &vec);                  //��С��������
};
#endif
