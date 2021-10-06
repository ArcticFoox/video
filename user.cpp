#include"user.h"

void add_user(list<User_Node>& user, string name){
    user.push_back(name);
    //user.sort(); <- 여기서 에러 발생
}

void User_search(list<User_Node>& user, string name){
    list<User_Node>::iterator it_u;
    bool find = false;

    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            cout << it_u->name << " ";
            for(int i = 0; i < it_u->Video_name.size(); i++){
                if(i == it_u->Video_name.size() - 1){
                    cout << it_u->Video_name.at(i);
                    break;
                }
                cout << it_u->Video_name.at(i) << ",";
            }
            cout << "\n";
            find = true;
        }
        else
            continue;
    }

    if(!find){
        cout << name << " is not found\n";
        return ;
    }  
}

void user_list(list<User_Node>& user){
    list<User_Node>::iterator it_u;

    for(it_u = user.begin(); it_u != user.end(); it_u++){ 
        cout << it_u->name << " ";
        for(int i = 0; i < it_u->Video_name.size(); i++){
            if(i == it_u->Video_name.size() - 1){
                cout << it_u->Video_name.at(i);
                break;
            }
            cout << it_u->Video_name.at(i) << ",";
        }
        cout << "\n";
    }
}