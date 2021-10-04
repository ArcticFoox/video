#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<string>
using namespace std;

struct Video_Node{
    string video_name;
    int video_num;
    vector<string> User_name;

    Video_Node(){}

    Video_Node(string video_name){
        this->video_name = video_name;
        this->video_num = 1;
    }
};

struct User_Node{
    string name;
    vector<string> Video_name;

    User_Node(){}

    User_Node(string name){
        this->name = name;
    }
};

void rent_video(list<User_Node>& user, list<Video_Node>& video, string video_name, string name){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_num = 0){
            cout << video_name << " is no stock\n";
            return;
        }
        if(it_v->video_name == video_name){
            it_v->video_num--;
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
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            for(it_user_video = it_u->Video_name.begin(); it_user_video != it_u->Video_name.end(); it_user_video++){
                if(it_user_video->data() == video_name){
                    it_u->Video_name.erase(it_user_video);
                    return;
                }
               
            }
        }
    }

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            for(it_video_user = it_v->User_name.begin(); it_video_user != it_v->User_name.end(); it_video_user++){
                if(it_video_user->data() == name){
                    it_v->User_name.erase(it_video_user);
                    return;
                }
            }
        }
    }

}

void add_user(list<User_Node>& user, string name){
    user.push_back(name);
    user.sort();
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
        video.sort();
    }
}

void Video_discard(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    bool find = false;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            if(it_v->User_name.empty()){
                video.erase(it_v);
                find = true;
                return;
            }
        else
            continue;
        }
    }

    if(!find){
        cout << video_name << " is not found\n";
        return ;
    }
}

void User_loop(list<User_Node>& user){
    list<User_Node>::iterator it_u;
    for(it_u = user.begin(); it_u != user.end(); it_u++){

    }
}

int main(){
    list<Video_Node> video;
    list<User_Node> user;

    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;

    string name;
    string users;
    cin >> name;

    
    
}