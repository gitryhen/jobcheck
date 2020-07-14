#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "stringsplit.hpp"

using namespace std;

int use_message();
string altorientation(string);

int main(int argc, char** argv)
{
    const string configfilename="jobcheck.cfg";
    ifstream file(configfilename);
    string singleline {};
    getline(file, singleline);
    vector<string> conf{split(singleline, '=')};
    if(conf[0]!="jobsdirectory")
    {
        cout << "Directory with jobs not found.\n";
    }
    if(argc<1) use_message();
    for(int i=1; i<argc;++i)
    {
        string jobfile = conf[1]+'/'+argv[i]+'/'+argv[i]+'/'+"convert.cfg";
        string paramfile = conf[1]+'/'+argv[i]+'/'+argv[i]+'/'+"convert_param.log";
//        cout << conf[1] << '\n';
//        cout << "my convert file is " << jobfile << '\n';
        vector<string> setting, filenameelement;
        ifstream myparamfile(paramfile);
        string specfromfilename;
        while(getline(myparamfile, singleline))
        {
            setting = split(singleline, '=');
            if (setting[0]=="Source Name ")
            {
                cout << setting[1] << '\t';
                filenameelement = split(setting[1],'_');
                specfromfilename = filenameelement[1].substr(1,7);
            }
        }
        ifstream myjobfile(jobfile);
        bool mirrorx, mirrory, darkfield;
        while(getline(myjobfile, singleline))
        {
            setting = split(singleline, ':');
            if (setting[0]=="mirroring at x axis (yes|no) .................. ")
            {
                if (setting[1]==" no")
                    {mirrorx=false;}
                else
                    {mirrorx=true;}
            }
            if (setting[0]=="mirroring at y axis (yes|no) .................. ")
            {
                if (setting[1]==" no")
                    {mirrory=false;}
                else
                    {mirrory=true;}
            }
            if (setting[0]=="exposure mode (inverted|noninverted) .......... ")
            {
                if (setting[1]==" 2")
                {
                    darkfield=false;
                }
                else if (setting[1]==" 0")
                {
                    darkfield=true;
                }
            }
        }
        string settingconvertcfg;
        if (darkfield)
        {
            cout << "DF";
            settingconvertcfg="DF";
        }
        else
        {
            cout << "BF";
            settingconvertcfg="BF";
        }
        if (mirrorx==mirrory)
        {
               cout << "CDWR\t";
               settingconvertcfg+="CDWR";
        }
        if (mirrorx!=mirrory)
        {
            cout << "CDRR\t";
            settingconvertcfg+="CDRR";
        }
        if (settingconvertcfg==specfromfilename)
        {
            cout << "Great success\n";
        }
        else
        {
            if (settingconvertcfg==altorientation(specfromfilename))
            {
                cout << "Also success.\n";
            }
            else
            {
                cout << "ERROR\n";
            }
        }
    }
}

int use_message()
{
    cout << "Usage: jc [JOBNAME1] [JOBNAME2] [JOBNAME3]\n";
    cout << "print out the file name and the settings of the job.\n";
    return 0;
}


string altorientation(string orientation)
{
    string out {orientation.substr(0,2)};
    if (orientation.substr(2,4)=="CUWR")
    {
        out+="CDRR";
    }
    if (orientation.substr(2,4)=="CURR")
    {
        out+="CDWR";
    }
    return out;
}
