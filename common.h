#ifndef __COMMON_H__
#define __COMMON_H__

#include"user.h"
#include"video.h"

void rent_video(list<User_Node>& user, list<Video_Node>& video, string video_name, string name){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_num == 0){
            cout << video_name << " is no stock\n";
            return;
        }
        if(it_v->video_name == video_name){
            it_v->video_num -= 1;
            it_v->User_name.push_back(name);
            //sort(it_v->User_name.begin(), it_v->User_name.end());
            break;
        }
    }
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            it_u->Video_name.push_back(video_name);
            //sort(it_u->Video_name.begin(), it_u->Video_name.end());
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
                    return;
                }
                j++;
            }
        }
    }

}

#endif // __COMMON_H__

