#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct User_Node{
    string name;
    string ID;
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

    Video_Node(){}

    Video_Node(string video_name){
        this->video_name = video_name;
        this->video_num = 1;
    }
};

void add_user(list<User_Node>& user, string name, string ID);
void add_video(list<Video_Node>& video, string name);


void save_user(list<User_Node>& user){
    ofstream writeFile;
    list<User_Node>::iterator it_u;
    writeFile.open("userlist.txt");
    writeFile.clear();

    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == ""){
            continue;
        }

        writeFile.write(it_u->name.c_str(), it_u->name.size());
        writeFile.write(" ", 1);
        writeFile.write(it_u->ID.c_str(), it_u->ID.size());
        writeFile.write(" ", 1);
        if(it_u->Video_name.empty()){
            writeFile.write("X", 1);
            writeFile.write("\n", 1);
        }
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

void load_user(list<User_Node>& user){
    ifstream readfromFile;
    list<User_Node>::iterator it_u;
    readfromFile.open("userlist.txt");

    if(readfromFile.is_open()){
        while(!readfromFile.eof()){
            string str1, str2, str3, tmp;

            readfromFile >> str1;
            readfromFile >> str2;
            readfromFile >> str3;

            add_user(user, str1, str2);
            if(str3 == "X"){
                continue;
            }

            else{
                for(it_u = user.begin(); it_u != user.end(); it_u++){
                    if(it_u->name == str1 && it_u->ID == str2) break;
                }

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

void save_video(list<Video_Node>& video){
    ofstream writeFile;
    list<Video_Node>::iterator it_v;
    writeFile.open("videolist.txt");
    writeFile.clear();

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == ""){
            continue;
        }

        writeFile.write(it_v->video_name.c_str(), it_v->video_name.size());
        writeFile.write(" ", 1);
        writeFile << (it_v->video_num);
        writeFile.write(" ", 1);
        if(it_v->User_name.empty()){
            writeFile.write("X", 1);
            writeFile.write("\n", 1);
        }
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

    if(readfromFile.is_open()){
        while(!readfromFile.eof()){
            int num;
            string str1, str2, tmp;

            readfromFile >> str1;
            readfromFile >> num;
            readfromFile >> str2;

            add_video(video, str1);

            for(it_v = video.begin(); it_v != video.end(); it_v++){
                if(it_v->video_name == str1) break;
            }

            if(str2 == "X"){
                it_v->video_num = num;
                continue;
            }

            else{
                it_v->video_num = num;
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

bool video_compare(const Video_Node& a, const Video_Node& b){
    return a.video_name < b.video_name;
}

bool user_compare(const User_Node& a, const User_Node& b){
    return a.name < b.name;
}

void rent_video(list<User_Node>& user, list<Video_Node>& video, string video_name, string name, string ID){
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
        if(it_u->name == name && it_u->ID == ID){
            it_u->Video_name.push_back(video_name);
            sort(it_u->Video_name.begin(), it_u->Video_name.end());
            break;
        }
    }
}

void return_video(list<User_Node>& user, list<Video_Node>& video, string name, string video_name, string ID){
    list<Video_Node>::iterator it_v;
    list<User_Node>::iterator it_u;
    vector<string>::iterator it_user_video;
    vector<string>::iterator it_video_user;
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name && it_u->ID == ID){
            for(it_user_video = it_u->Video_name.begin(); it_user_video != it_u->Video_name.end(); it_user_video++){
                if(it_user_video->data() == video_name){
                    it_u->Video_name.erase(it_user_video);
                    sort(it_u->Video_name.begin(), it_u->Video_name.end());
                    break;
                }
            }
        }
    }

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == video_name){
            for(it_video_user = it_v->User_name.begin(); it_video_user != it_v->User_name.end(); it_video_user++){
                if(it_video_user->data() == name){
                    it_v->video_num += 1; 
                    it_v->User_name.erase(it_video_user);
                    sort(it_v->User_name.begin(), it_v->User_name.end());
                    return;
                }
            }
        }
    }
}
// need to refatorying 
void add_user(list<User_Node>& user, string name, string ID){
    list<User_Node>::iterator it_u;
    User_Node tmp_user;
    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->ID == ID){
            cout << "ID is overlaped try other thing\n";
            return;
        }
    }
    tmp_user.name = name;
    tmp_user.ID = ID;
    user.push_back(tmp_user);
    user.sort(user_compare);
}

void User_search(list<User_Node>& user, string name){
    list<User_Node>::iterator it_u;
    bool find = false;

    for(it_u = user.begin(); it_u != user.end(); it_u++){
        if(it_u->name == name){
            cout << it_u->name << " " << it_u->ID << " ";
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
    }

    if(!find){
        cout << name << " is not found\n";
        return ;
    }  
}

void user_list(list<User_Node>& user){
    list<User_Node>::iterator it_u;

    for(it_u = user.begin(); it_u != user.end(); it_u++){ 
        cout << it_u->name << " " << it_u->ID << " ";
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
            return;
        }
    }
    cout << video_name << " is not found\n";
    return ;  
}

void video_list(list<Video_Node>& video){
    list<Video_Node>::iterator it_v;

    for(it_v = video.begin(); it_v != video.end(); it_v++){
        if(it_v->video_name == ""){
            continue;
        }

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

void delete_user(list<User_Node>& user, string name){
    int n;
    list<User_Node>::iterator it_u;
    vector<list<User_Node>::iterator> tmp;
    for(it_u = user.begin(); it_u != user.end(); it_u++){ 
        if(it_u->name == name){
            tmp.push_back(it_u);
        }
    }
    cout << "which one do you want to delete?\n";
    for(int i = 0; i < tmp.size(); i++){
        cout << i + 1 << " " << tmp.at(i)->name << " " << tmp.at(i)->ID << "\n";
    }
    cout << "number : ";
    cin >> n;

    user.erase(tmp.at(n - 1));
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
                add_user(user, name, ID);
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