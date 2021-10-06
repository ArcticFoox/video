#include"common.h"

// 추가 목록 : 오름차순 정렬
int main(){
    list<Video_Node> video;
    list<User_Node> user;

    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;

    string name;
    string users;
    cin >> name;

    string video_name;
    bool it = true;
    while(it){
        int button;
        cout << "add_user 1, add_video 2, search_user 3, search_video 4, rent 5, return 6, video discard 7, user list 8, video list 9" << "\n";
        cin >> button;
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