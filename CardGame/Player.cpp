#include "Player.h"
string Player::getName()
{
    return this->name;
}

void Player::setName(string name)
{
    this->name = name;
}

Player::Player()
{
}

Player::Player(string name)
{
    this->name = name;
    this->score = 0;
}

void Player::Hit()                
{
    fstream f;
    vector<int> set;                 //����ֽ����Ϣ
    f.open("cardSet.txt", ios::in | ios::out);
    int card;                             //ֽ����ֵ
    while (!f.eof()) {
        f >> card;
        set.push_back(card);     //��txt�ļ����ֽ�Ƶ��뵽vector
    }
    f.close();

    int len = set.size();
    int newRank = set[len - 1];
    Card newCard = Card(newRank);
    this->handCard.push_back(newCard);                  //��������ϼ���һ����

    if (this->hasPair(this->handCard)) {
        this->score = this->score + newRank;             //��������ƴճɶ��� �ӷ�
    }

    set.pop_back();
    f.open("cardSet.txt", ios::trunc | ios::out);             //ɾ��txt�ļ�����ĩβ��һ����
    for (int i = 0; i < set.size(); i++) {
        f << set[i];
        if (i < set.size() - 1)
            f << '\n';
    }
    f.close();
}

void Player::Fold(Player& p1, Player& p2)         
{
    if (!p1.handCard.empty() && !p2.handCard.empty()) {    //������˶�����
        p1.handCard = p1.sortValue(p1.handCard);
        p2.handCard = p2.sortValue(p2.handCard);
        if (p1.handCard[0].rank > p2.handCard[0].rank) {
            this->score = this->score + p2.handCard[0].rank;
            p2.handCard.erase(p2.handCard.begin());                         
        }
        else if (p1.handCard[0].rank < p2.handCard[0].rank) { 
            this->score = this->score + p1.handCard[0].rank;
            p1.handCard.erase(p1.handCard.begin());
        }
    }
}


string Player::showCard()                                 //��ʾ�Լ��������п�����Ϣ ����[1][4][7]
{
    if (!this->handCard.empty()) {
        string pCard = "\t";
        for (int i = 0; i < this->handCard.size(); i++) {           
         pCard = pCard.append(handCard[i].display());           
        }
        return pCard;
    }
    else {
        return "\t";
    }
}

bool Player::Quit()     //����˳���Ϸ
{
    return true;
}

bool Player::hasPair(vector<Card> vec)        //�ж�һ��Card��vector���Ƿ��ж��ӻ����ظ�   
{                                                                      //��roundOver�ĳ������֮һ
    if (vec.size() > 1) {
        for (int i = 0; i < vec.size(); i++) {
            for (int j = i + 1; j < vec.size(); j++) {
                if (vec[i].rank == vec[j].rank) {
                    return true;
                }
            }
        }
        return false;
    }
    else {
        return false;
    }
}

bool Player::isMinTie(Player& p1, Player& p2)                  //�ж���ҵ�������Сֵ�Ƿ񹹳���tie��ƽ�֣�
{
    p1.handCard = p1.sortValue(p1.handCard);
    p2.handCard = p2.sortValue(p2.handCard);
    vector<Card> mix;                                           //ÿ��������ϵ���С������һ��
    mix.push_back(p1.handCard[0]);
    mix.push_back(p2.handCard[0]);
   // mix = this->sortValue(mix);                             //ÿ�������ϵ���С������һ�����ų���С��   
    if (this->hasPair(mix)) {                                      //�����С���غ���
        return true;
    }
    else {
        return false;
    }
}

bool Player::minLargerThanOther(Player &p)     //�ж�this��������Сֵ�Ƿ����other
{
    this->handCard = this->sortValue(this->handCard);
    p.handCard = p.sortValue(p.handCard);
    if (this->handCard[0].rank > p.handCard[0].rank) {
        return true;
    }
    else {
        return false;
    }
    
}

vector<Card> Player::sortValue(vector<Card>& vec)           //��С��������
{
    if (vec.size() > 1) {
        for (int i = 0; i < vec.size(); i++) {
            int minIndex = i;
            for (int j = i + 1; j < vec.size(); j++) {
                if (vec[j].rank < vec[i].rank) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                int temp = vec[i].rank;
                vec[i].rank = vec[minIndex].rank;
                vec[minIndex].rank = temp;
            }
        }
        return vec;
    }
    else {
        return vec;
    }
}
