#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>

using namespace std;
vector<string> GetFileList(){
    struct dirent *ptr;
    DIR *dir;
    string PATH = "./";
    dir=opendir(PATH.c_str());
    vector <string> files;
    cout << "file list: "<< endl;
    while((ptr=readdir(dir))!=NULL)
    {

        //跳过'.'和'..'两个目录
        if(ptr->d_name[0]=='.' || ptr->d_name[10] == '.' || ptr->d_name[19] == '.')
            continue;
        //cout << ptr->d_name << endl;
        files.push_back(ptr->d_name);
    }

    for (int i = 0; i < files.size(); ++i)
    {
        cout << files[i] << endl;
    }
    closedir(dir);
    return  files;
}
int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;
    string ss;

    vector<string> files = GetFileList();
    for(auto n:files){
        in.open(n);
        if(in.fail()) cerr<<"open in file fail"<<endl;

        string outfile = "new_"+n;
        out.open(outfile,ios::out);
        if(out.fail()) cerr<<"open out file fail"<<endl;
        cout<<"reading from "<<n<<endl;
        //skip trace's metadata
        while(getline(in,ss)){
            ss=ss.substr(0,17);
            string s1;
            s1+=ss.substr(0,2);
            s1+=ss.substr(3,2);
            s1+=ss.substr(6,2);
            s1+=ss.substr(9,2);
            s1+=ss.substr(12,2);
            s1+=ss.substr(15,2);
            out<<s1<<"\n";
        }

        in.close();
        out.close();
    }
    return 0;
}