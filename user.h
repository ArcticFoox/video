#ifndef __USER_H__
#define __USER_H__

#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<string>
using namespace std;

struct User_Node{
    string name;
    vector<string> Video_name;

    User_Node(){}

    User_Node(string name){
        this->name = name;
    }
};

void add_user(list<User_Node>& user, string name);
void User_search(list<User_Node>& user, string name);
void user_list(list<User_Node>& user);

#endif // __USER_H__