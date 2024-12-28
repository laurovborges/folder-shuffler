#include <iostream>
#include <filesystem>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

string allowed_characters = "abcdefghijklmnopqrstuvwxyz0123456789";
vector<string> used_names;

bool isTaken(const string &name){
    for(string &used_name : used_names){
        if(used_name == name)
            return true;
    }
    used_names.push_back(name);
    return false;
}

string randomName(){
    string random_name = "four"; // 4 characters
    do{
        for(int i = 0; i < random_name.size(); i++){
            random_name[i] = allowed_characters[rand() % 35];
        }
    }
    while(isTaken(random_name) == true);
    return random_name;
}

int main(){
    srand((unsigned) time(NULL));
    string user_confirm;

    cout << "Are you sure you want to randomly rename all the files in " << std::filesystem::current_path().string() << "?\n(y/n): ";
    cin >> user_confirm;
    for(int i = 0; i < user_confirm.size(); i++)
        user_confirm[i] = tolower(user_confirm[i]);
    if(user_confirm != "y" && user_confirm != "yes" && user_confirm != "yeah" && user_confirm != "yep" && user_confirm != "yea" && user_confirm != "yup" && user_confirm != "ye"){
        cout << "Closing...";
        auto delayBeforeExit = 1s;
        std::this_thread::sleep_for(delayBeforeExit);
        return 0;
    }

    string user_repeat;
    do{
        for(const auto& curr : std::filesystem::directory_iterator(std::filesystem::current_path())){
            if(curr.path().filename() == "FolderShuffler.cpp" || curr.path().filename() == "FolderShuffler.exe" || curr.path().filename() == ".FolderShuffler.cpp" || curr.path().filename() == ".FolderShuffler.exe"){
                continue;
            }
            else{
            std::filesystem::rename(curr.path().filename(), randomName()+curr.path().extension().string());
            }
        }

        cout << "Successfully renamed all files!" << endl << "Go again? (y/n) ";
        cin >> user_repeat;
        for(int i = 0; i < user_repeat.size(); i++)
            user_repeat[i] = tolower(user_repeat[i]);
    }
    while(user_repeat == "y" || user_repeat == "ye" || user_repeat == "yes" || user_repeat == "yep" || user_repeat == "yup" || user_repeat == "yea" || user_repeat == "yeah");
    
    cout << "Closing...";
    auto delayBeforeExit = 1s;
    std::this_thread::sleep_for(delayBeforeExit);
    return 0;
}