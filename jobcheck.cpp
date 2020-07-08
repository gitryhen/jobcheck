#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "stringsplit.hpp"

using namespace std;

int use_message();

int main(int argc, char** argv)
{
    const string configfilename="jobcheck.cfg";
    ifstream file(configfilename);
    string singleline {};
    getline(file, singleline);
    vector<string> conf{split(singleline, ' ')};
    if(conf[1]=="=")
    {
        cout << "directory is " << conf[2];
    }
    if(argc<1) use_message();
    for(int i=1; i<argc;++i)
    {
        cout << argv[i] << '\n';
    }
}

int use_message()
{
    cout << "Usage: jc [JOBNAME1] [JOBNAME2] [JOBNAME3]\n";
    cout << "print out the file name and the settings of the job.\n";
    return 0;
}
