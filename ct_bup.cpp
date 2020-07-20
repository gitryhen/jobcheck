/* ************************
# ct.cpp
# compile on gcc 4.5.1
# g++ -std=c++0x ct.cpp -o ct 
***************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class File
{
	private:
		std::string filename;
		std::vector<std::string> vs;
	public:
		File(std::string f);
		~File();
		std::vector<std::string> readfile(std::string cfilename);
};

template<class T, class U>
T optel(T t, U u){
	return t+u;
}

int main(int argc, char* argv[]){
	if (argc>0)
	{
		std::cout << "Hello" << '\n';
		for (int i=1;i<argc;++i)
		{
			File myfile(argv[i]);
		}
	}
	else
	{
		std::cout << "No arguments given.\n";
	}
	return 0;
};

File::File(std::string f){
	std::string singleline;
	std::string paramsfile;
	std::string convertfile;
	std::vector<std::string> content;
	filename = f;
	paramsfile = "/home/convert/tmp_app_dir_0/Xgui/jobs/" + f + "/" + f + "_param";
	/* convert.cfg can be found in /home/convert/job/NAME/NAME/convert.cfg */
	convertfile = "/home/convert/job/" + f + "/" + f + "/" + "convert.cfg"; 
		content = readfile(convertfile);
		/* design file name */
		std::ifstream p(paramsfile);
		std::getline(p, singleline);
		std::cout << singleline << '\n';
		p.close();
		int l = content[14].length();
		std::string polarity{};
		if content[8].substr(51) == content[9].substr(51)
		{
			polarity = "CDWR";
		}
		else if content[8].substr(51) != content[9].substr(51)
		{
			polarity = "CDRR";
		}
		if (content[14].substr(l-1, l) == "0")
		{
			std::cout << "DF" << polarity << '\n';
		}
		else if (content[14].substr(l-1, l) == "2")
		{
			std::cout << "BF" << polarity << '\n';
		}
		/*
		std::getline(ifs, singleline);
		vs.push_back(singleline);
		*/
		std::cout << content[2] << '\n';
		std::cout << content[5] << '\n';
		std::cout << content[8] << '\n';
		std::cout << content[9] << '\n';
		std::cout << content[14] << '\n';
		for(int i = 10; i<14; i++){
			std::cout << content[i] << '\n';
		}
}

File::~File()
{
	std::cout << filename << " done." << std::endl;
}

std::vector<std::string> File::readfile(std::string filename){
	std::vector<std::string> vec;
	std::string singleline;
	std::ifstream ifs(filename);
	while (std::getline(ifs, singleline)){
		vec.push_back(singleline);
	}
	ifs.close();
	return vec;
}
