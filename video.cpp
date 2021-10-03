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
};

void rent_video(string video_name, string name){
    
}

int main(){
    list<Video_Node> video;
    list<User_Node> user;

    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;

    string name;
    string users;
    cin >> name;

    video.push_back(Video_Node(name));
    video.sort();

    cin >> name >> users;

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == name){
            it_v->User_name.push_back(users);
            sort(it_v->User_name.begin(), it_v->User_name.end());
        }
    }
}