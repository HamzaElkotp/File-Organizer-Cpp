#include <bits/stdc++.h>
#include <direct.h>

using namespace std;
using namespace filesystem;

string askPath(){
    string path;
    cout<<"Enter Folder Path to Organize it: ";
    cin>>path;
    cout<<endl;
    return path;
}

vector<directory_entry> getFolderContent(){
    vector<directory_entry> content;
    for(auto & file : directory_iterator(current_path())){
        content.push_back(file);
    }
    return content;
}

string categorization(path &ext){ // categorize files into folders
    if(ext == ".png" || ext == ".jpg" || ext == ".gif"){
        return "imgs";
    } else if(ext == ".pdf" || ext == ".md" || ext == ".docx"){
        return "docs";
    } else if(ext == ".txt" || ext == ".csv" || ext == ".dat"){
        return "data";
    } else if(ext == ".exe" || ext == ".msi"){
        return "programs";
    } else if(ext == ".mp4" || ext == ".mp3" || ext == ".flv" || ext == ".mkv" || ext == ".webm" || ext == ".wav"){
        return "multimedia";
    } else if(ext != ""){
        return "others";
    }
    return "";
}

void initFolders(vector<directory_entry> &content){
    for(auto & fl : content){
        path pth = fl;
        path ext = pth.extension();
        string category = categorization(ext);
        if(category != "" && !is_directory(category) && !exists(category)){
            mkdir(category.c_str());
        }
    }
}

void organizeContent(vector<directory_entry> &content){
    path currentPath = current_path();
    for(auto & fl : content){
        path pth = fl;
        path fileExtension = pth.extension();
        string fileName = pth.string();
        fileName = fileName.substr(fileName.find_last_of("/\\")+1);
        string folder = categorization(fileExtension);

        try{
            rename(pth, currentPath.string()+"\\"+folder+"\\"+fileName);
        }catch(filesystem_error &e){
            e.what();
        }
    }
}
int main() {
    const string FolderPath = askPath(); // get folder path
    current_path(FolderPath); // change to the new path

    vector<directory_entry> fls = getFolderContent(); // get list of files & folders
    initFolders(fls); // create organizing folders
    organizeContent(fls); // move files into their new places

    cout<<"Folder Organized Successfully"<<endl;

    return 0;
}