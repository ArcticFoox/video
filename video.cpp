#include"video.h"

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
        //video.sort();
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