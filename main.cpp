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

struct Video_Node{
    string video_name;
    int video_num;
    vector<string> User_name;

    Video_Node(string video_name){
        this->video_name = video_name;
        this->video_num = 1;
    }
};

bool video_compare(const Video_Node& a, const Video_Node& b){
    return a.video_name < b.video_name;
}

bool user_compare(const User_Node& a, const User_Node& b){
    return a.name < b.name;
}

// 추가 목록 : 사용자 동명이인 처리
void rent_video(list<User_Node>& user, list<Video_Node>& video, string video_name, string name){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            if(it_v->video_num == 0){
                cout << video_name << " is no stock\n";
                return;
            }
            it_v->video_num -= 1;
            it_v->User_name.push_back(name);
            sort(it_v->User_name.begin(), it_v->User_name.end());
            break;
        }
    }
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            it_u->Video_name.push_back(video_name);
            sort(it_u->Video_name.begin(), it_u->Video_name.end());
            break;
        }
    }
}

void return_video(list<User_Node>& user, list<Video_Node>& video, string name, string video_name){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    vector<string>::iterator it_user_video;
    vector<string>::iterator it_video_user;
    int i = 0, j = 0;
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            for(it_user_video = it_u->Video_name.begin(); it_user_video != it_u->Video_name.end(); it_user_video++){
                if(/*it_u->Video_name.at(i)*/ it_user_video->data() == video_name){
                    it_u->Video_name.erase(it_user_video);
                    sort(it_u->Video_name.begin(), it_u->Video_name.end());
                    break;
                }
                i++;
            }
        }
    }

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            for(it_video_user = it_v->User_name.begin(); it_video_user != it_v->User_name.end(); it_video_user++){
                if(/*it_v->User_name.at(j)*/ it_video_user->data() == name){
                    it_v->video_num += 1; 
                    it_v->User_name.erase(it_video_user);
                    sort(it_v->User_name.begin(), it_v->User_name.end());
                    return;
                }
                j++;
            }
        }
    }
}

void add_user(list<User_Node>& user, string name){
    user.push_back(name);
    user.sort(user_compare);
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

void add_video(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    bool find = false;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            it_v->video_num++;
            find = true;
            break;
        }
    }
    if(!find){
        video.push_back(video_name);
        video.sort(video_compare);
    }
}
// 있지만 대여 중인 목록을 찾지 못한다는 것 보단 못 지운다는 말을 해줘야할듯함
void Video_discard(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            if(it_v->User_name.empty()){
                video.erase(it_v);
                cout << "discard it\n";
                return;
            }
            else{
                cout << "can't discard it\n";
                return;
            }
        }
    }
    cout << video_name << " is not found\n";
    return ;
}

void Video_search(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    bool find = false;

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            cout << it_v->video_name << " " << it_v->video_num << " ";
            for(int i = 0; i < it_v->User_name.size(); i++){
                if(i == it_v->User_name.size() - 1){
                    cout << it_v->User_name.at(i);
                    break;
                }
                cout << it_v->User_name.at(i) << ",";
            }
            cout << "\n";
            find = true;
            return;
        }
        else
            continue;
    }

    if(!find){
        cout << video_name << " is not found\n";
        return ;
    }  
}

void video_list(list<Video_Node>& video){
    list<Video_Node>::iterator it_v;

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        cout << it_v->video_name << " " << it_v->video_num << " ";
        for(int i = 0; i < it_v->User_name.size(); i++){
            if(i == it_v->User_name.size() - 1){
                cout << it_v->User_name.at(i);
                break;
            }
            cout << it_v->User_name.at(i) << ",";
        }
        cout << "\n";
    }
}

int main(){
    list<Video_Node> video;
    list<User_Node> user;
    string name;
    string video_name;
    bool it = true;
    while(it){
        int button;
        cout << "add_user 1, add_video 2, search_user 3, search_video 4, rent 5, return 6, video discard 7, user list 8, video list 9" << "\n";
        cin >> button;
        if(!cin){
            cout << "wrong button try again" << "\n";
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }
        switch(button){
            case 1:
                cout << "Enter the name\n";
                cin >> name;
                add_user(user, name);
                break;
            case 2:
                cout << "Enter the video name\n";
                cin >> video_name;
                add_video(video, video_name);
                break;
            case 3:
                cout << "Enter the name\n";
                cin >> name;
                User_search(user, name);
                break;
            case 4:
                cout << "Enter the video name\n";
                cin >> video_name;
                Video_search(video, video_name);
                break;
            case 5:
                cout << "Enter the name and video name\n";
                cin >> name >> video_name;
                rent_video(user, video, video_name, name);
                break;
            case 6:
                cout << "Enter the name and video name\n";
                cin >> name >> video_name;
                return_video(user, video, name, video_name);
                break;
            case 7:
                cout << "Enter the video name\n";
                cin >> video_name;
                Video_discard(video, video_name);
                break;
            case 8:
                cout << "Name Video_list\n";
                user_list(user);
                break;
            case 9:
                cout << "Video_name Stock User_name\n";
                video_list(video);
                break;
            case 10:
                it = false;
                break;
            default:
                cout << "wrong button try again" << "\n";
                break; 
        }
    }
    return 0;
}
//https://webnautes.tistory.com/1158
//https://wiserloner.tistory.com/306