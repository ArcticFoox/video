#ifndef __VIDEO_H__
#define __VIDEO_H__

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

void add_video(list<Video_Node>& video, string video_name);
void Video_discard(list<Video_Node>& video, string video_name);
void Video_search(list<Video_Node>& video, string video_name);
void video_list(list<Video_Node>& video);

#endif  // __VIDEO_H__