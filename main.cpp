#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
// 사용자 구조체
struct User_Node{
    string name;
    string ID;
    vector<string> Video_name;

    User_Node(){}

    User_Node(string name){
        this->name = name;
    }

    // User_Node(string name, string ID){
    //     this->name = name;
    //     this->ID = ID;
    // }
};
// 비디오 구조체
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

bool add_user(list<User_Node>& user, string name, string ID);
bool add_video(list<Video_Node>& video, string name);

// 사용자 저장 함수
void save_user(list<User_Node>& user){
    ofstream writeFile;
    list<User_Node>::iterator it_u;
    writeFile.open("userlist.txt");
    writeFile.clear();

    for(it_u = user.begin(); it_u != user.end(); it_u++){
        // 인자가 없는데 입력받는 경우 대비
        if(it_u->name == ""){
            continue;
        }

        writeFile.write(it_u->name.c_str(), it_u->name.size());
        writeFile.write(" ", 1);
        writeFile.write(it_u->ID.c_str(), it_u->ID.size());
        writeFile.write(" ", 1);
        //빌린 비디오가 없으면 X 출력
        if(it_u->Video_name.empty()){
            writeFile.write("X", 1);
            writeFile.write("\n", 1);
        }
        //빌린 목록을 모두 출력
        else{
            for(int i = 0; i < it_u->Video_name.size(); i++){
                if(i == it_u->Video_name.size() - 1){
                    writeFile.write(it_u->Video_name.at(i).c_str(), it_u->Video_name.at(i).size());
                    writeFile.write("\n", 1);
                    break;
                }
                writeFile.write(it_u->Video_name.at(i).c_str(), it_u->Video_name.at(i).size());
                writeFile.write(",", 1);
            }
        }
    }
    writeFile.close();
}
// 사용자 불러오기 함수
void load_user(list<User_Node>& user){
    ifstream readfromFile;
    list<User_Node>::iterator it_u;
    readfromFile.open("userlist.txt");
    // 불러올 파일이 있을 시 시행
    if(readfromFile.is_open()){
        while(!readfromFile.eof()){
            string str1, str2, str3, tmp;
            //한 줄에 세가지 정보가 있기 때문에 전부 받기 위해 세개 선언 및 불러오기
            readfromFile >> str1;
            readfromFile >> str2;
            readfromFile >> str3;

            add_user(user, str1, str2);
            //빌린 비디오가 없을 경우
            if(str3 == "X"){
                continue;
            }
            //빌린 비디오가 있을 경우
            else{
                //현재 유저의 iterator 검색
                for(it_u = user.begin(); it_u != user.end(); it_u++){
                    if(it_u->name == str1 && it_u->ID == str2) break;
                }
                //불러온 string을 ',' 기준으로 나누어 vector 안에 삽입
                for(int i = 0; i < str3.size(); i++){
                    if(str3[i] == ','){
                        it_u->Video_name.push_back(tmp);
                        tmp = "";
                    }
                    else
                        tmp += str3[i];

                    if(i == str3.size() - 1){
                        it_u->Video_name.push_back(tmp);
                    }
                }
            }
            
        }
        readfromFile.close();
    }
    return;
};
//비디오 저장 함수
void save_video(list<Video_Node>& video){
    ofstream writeFile;
    list<Video_Node>::iterator it_v;
    writeFile.open("videolist.txt");
    writeFile.clear();

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        // 인자가 없는데 입력받는 경우 대비
        if(it_v->video_name == ""){
            continue;
        }

        writeFile.write(it_v->video_name.c_str(), it_v->video_name.size());
        writeFile.write(" ", 1);
        writeFile << (it_v->video_num);
        writeFile.write(" ", 1);
        // 빌린 유저가 없을 경우
        if(it_v->User_name.empty()){
            writeFile.write("X", 1);
            writeFile.write("\n", 1);
        }
        // 빌린 유저가 있을 경우
        else{
            for(int i = 0; i < it_v->User_name.size(); i++){
                if(i == it_v->User_name.size() - 1){
                    writeFile.write(it_v->User_name.at(i).c_str(), it_v->User_name.at(i).size());
                    writeFile.write("\n", 1);
                    break;
                }
                writeFile.write(it_v->User_name.at(i).c_str(), it_v->User_name.at(i).size());
                writeFile.write(",", 1);
            }
        }
    }
    writeFile.close();
}

void load_video(list<Video_Node>& video){
    ifstream readfromFile;
    list<Video_Node>::iterator it_v;
    readfromFile.open("videolist.txt");
    // 불러올 파일이 있을 시 시행
    if(readfromFile.is_open()){
        while(!readfromFile.eof()){
            int num;
            string str1, str2, tmp;
            //한 줄에 세가지 정보가 있기 때문에 전부 받기 위해 세개 선언 및 불러오기
            readfromFile >> str1;
            readfromFile >> num;
            readfromFile >> str2;

            add_video(video, str1);
            //현재 비디오의 iterator 검색
            for(it_v = video.begin(); it_v != video.end(); it_v++){
                if(it_v->video_name == str1) break;
            }
            //빌린 유저가 없을 경우
            if(str2 == "X"){
                it_v->video_num = num; //비디오의 개수 저장
                continue;
            }

            else{
                it_v->video_num = num; //비디오의 개수 저장
                //불러온 string을 ',' 기준으로 나누어 vector 안에 삽입
                for(int i = 0; i < str2.size(); i++){
                    if(str2[i] == ','){
                        it_v->User_name.push_back(tmp);
                        tmp = "";
                    }
                    else
                        tmp += str2[i];

                    if(i == str2.size() - 1){
                        it_v->User_name.push_back(tmp);
                    }
                }
            }
            
        }
        readfromFile.close();
    }
    return;
};
//정렬을 하기 위한 함수
bool video_compare(const Video_Node& a, const Video_Node& b){
    return a.video_name < b.video_name;
}
//정렬을 하기 위한 함수
bool user_compare(const User_Node& a, const User_Node& b){
    return a.name < b.name;
}
//대여 함수
void rent_video(list<User_Node>& user, list<Video_Node>& video, string video_name, string name, string ID){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    bool find = false;
    //Video_Node를 돌면서 video_name를 가진 Node 검색
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            //비디오 재고가 없을 경우
            if(it_v->video_num == 0){
                cout << video_name << " is no stock\n";
                return;
            }
            //비디오 재고가 있는 경우
            it_v->video_num -= 1;
            it_v->User_name.push_back(name);
            sort(it_v->User_name.begin(), it_v->User_name.end());
            find = true;
            break;
        }
    }
    //Video_Node에 video_name를 가진 Node가 있을 경우
    if(find){
        //User_Node에서 name과 ID가 일치하는 유저의 Video_name에 video_name 삽입
        for(it_u = user.begin(); it_u != user.end(); it_u++){
            if(it_u->name == name && it_u->ID == ID){
                it_u->Video_name.push_back(video_name);
                sort(it_u->Video_name.begin(), it_u->Video_name.end());
                break;
            }
        }
        cout << "It is rented\n";
    }
    //Video_Node에 video_name를 가진 Node가 없을 경우
    else
        cout << "The video is not found\n";
}
//반납 함수
void return_video(list<User_Node>& user, list<Video_Node>& video, string name, string video_name, string ID){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    vector<string>::iterator it_user_video;
    vector<string>::iterator it_video_user;
    bool find = false;
    //User_Node를 돌면서 name과 ID를 가진 Node 검색
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name && it_u->ID == ID){
            //name과 ID를 가진 Node 찾았으면 그 Node의 Video_name 중 입력받은 값이 있는지 검색
            for(it_user_video = it_u->Video_name.begin(); it_user_video != it_u->Video_name.end(); it_user_video++){
                if(it_user_video->data() == video_name){
                    it_u->Video_name.erase(it_user_video);
                    sort(it_u->Video_name.begin(), it_u->Video_name.end());
                    find = true;
                    break;
                }
            }
        }
    }
    //name과 ID를 가진 Node가 있을 경우
    if(find){
        //Video_Node를 돌면서 video_name를 가진 Node 검색
        for(it_v = video.begin(); it_v != video.end(); it_v++){
            if(it_v->video_name == video_name){
                //video_name를 가진 Node 찾았으면 그 Node의 User_name 중 입력받은 값이 있는지 검색
                for(it_video_user = it_v->User_name.begin(); it_video_user != it_v->User_name.end(); it_video_user++){
                    if(it_video_user->data() == name){
                        it_v->video_num += 1; 
                        it_v->User_name.erase(it_video_user);
                        sort(it_v->User_name.begin(), it_v->User_name.end());
                        cout << "It is returned\n";
                        return;
                    }
                }
            }
        }
    }
    //name과 ID를 가진 Node가 없을 경우
    else
        cout << "The name or ID is not found\n";
}
//유저 추가 함수
bool add_user(list<User_Node>& user, string name, string ID){
    list<User_Node>::iterator it_u;
    User_Node tmp;
    //User_Node 중 같은 ID 유무 검색
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        // 같은 ID일 경우
        if(it_u->ID == ID){
            cout << "ID is overlaped try other thing\n";
            return false;
        }
    }
    // 같은 ID가 없을 경우
    tmp.name = name;
    tmp.ID = ID;
    user.push_back(tmp);
    user.sort(user_compare);
    return true;
}
//유저 검색 함수
void User_search(list<User_Node>& user, string name){
    list<User_Node>::iterator it_u;
    bool find = false;
    //User_Node중 name이 같은 Node 검색 및 출력
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            cout << it_u->name << " " << it_u->ID << " ";
            //Node의 video_name 순환 및 출력
            for(int i = 0; i < it_u->Video_name.size(); i++){
                if(i == it_u->Video_name.size() - 1){
                    cout << it_u->Video_name.at(i);
                    break;
                }
                cout << it_u->Video_name.at(i) << ",";
            }
            cout << "\n";
            find = true;
            //검색한 대상을 찾았을 경우
        }
    }
    //검색한 대상을 찾지 못했을 경우
    if(!find){
        cout << name << " is not found\n";
        return ;
    }  
}
//유저 목록 출력 함수
void user_list(list<User_Node>& user){
    list<User_Node>::iterator it_u;
    //모든 User_Node 순환 및 출력
    for(it_u = user.begin(); it_u != user.end(); it_u++){ 
        //비어 있는 경우 대비
        if(it_u->name == ""){
            continue;
        }
        cout << it_u->name << " " << it_u->ID << " ";
        //Node의 video_name 순환 및 출력
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
//비디오 추가 함수
bool add_video(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    //Video_Node 중 같은 video_name 유무 검색
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        //같은 video_name일 경우
        if(it_v->video_name == video_name){
            it_v->video_num++;
            return false;
        }
    }
    //없던 video_name일 경우
    video.push_back(video_name);
    video.sort(video_compare);
    return true;
}
//비디오 삭제 함수
void Video_discard(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    //Video_Node 중 같은 video_name 유무 검색
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            //그 Video_Node의 User_Node가 비어 있을 경우
            if(it_v->User_name.empty()){
                video.erase(it_v);
                cout << "discard it\n";
                return;
            }
            //그 Video_Node의 User_Node가 비어 있지 않을 경우
            else{
                cout << "can't discard it\n";
                return;
            }
        }
    }
    //Video_Node 중 같은 video_name가 없을 경우
    cout << video_name << " is not found\n";
    return ;
}
//비디오 검색 함수
void Video_search(list<Video_Node>& video, string video_name){
    list<Video_Node>::iterator it_v;
    //Video_Node 중 같은 video_name 유무 검색
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        //같은 video_name가 있을 경우
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
            return;
        }
    }
    //같은 video_name가 없을 경우
    cout << video_name << " is not found\n";
    return ;  
}
//비디오 목록 출력 함수
void video_list(list<Video_Node>& video){
    list<Video_Node>::iterator it_v;
    //Video_Node 순환 및 출력
    for(it_v = video.begin(); it_v != video.end(); it_v++){
        //비어 있는 경우 대비
        if(it_v->video_name == ""){
            continue;
        }
        //Node의 video_name 순환 및 출력
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
// 유저 삭제 함수
void delete_user(list<User_Node>& user, string name){
    int n;
    list<User_Node>::iterator it_u;
    vector<list<User_Node>::iterator> tmp;
    //User_Node 중 name 유무 검색
    for(it_u = user.begin(); it_u != user.end(); it_u++){ 
        if(it_u->name == name){
            tmp.push_back(it_u);
        }
    }
    //tmp에 있는 같은 name의 유저 중 삭제할 유저 선택
    cout << "which one do you want to delete?\n";
    for(int i = 0; i < tmp.size(); i++){
        cout << i + 1 << " " << tmp.at(i)->name << " " << tmp.at(i)->ID << "\n";
    }
    cout << "number : ";
    cin >> n;

    user.erase(tmp.at(n - 1));
    cout << "Delete it\n";
}

int main(){
    list<Video_Node> video;
    list<User_Node> user;
    string name;
    string video_name;
    string ID;
    bool it = true;
    load_user(user);
    load_video(video);
    while(it){
        save_user(user);
        save_video(video);
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
                cout << "Enter the name and ID doesn't overlap\n";
                cin >> name >> ID;
                if(add_user(user, name, ID)){
                    cout << "add it\n";
                }
                break;
            case 2:
                cout << "Enter the video name\n";
                cin >> video_name;
                if(add_video(video, video_name)){
                    cout << "add it\n";
                }
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
                cout << "Enter the name, ID and video name\n";
                cin >> name >> ID >> video_name;
                rent_video(user, video, video_name, name, ID);
                break;
            case 6:
                cout << "Enter the name, ID and video name\n";
                cin >> name >> ID >> video_name;
                return_video(user, video, name, video_name, ID);
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
                cout << "Enter the name\n";
                cin >> name;
                delete_user(user, name);
                break;
            case 11: //왜 에러 표기가 뜨는지 알아 봐야 함
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