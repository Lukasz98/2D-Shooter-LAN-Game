#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h> // for console writing

// for modyfication time
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

/*
	musze ogarnac zeby kompilowac cpp nawet gdy nie byl zmieniony ale zmieniony byl header tego cpp
*/

struct str_time
{
	std::string fileName;
	int sec, min, hour, day, mon, year;
	bool operator== (str_time & _t)
	{
		if (this->fileName != _t.fileName) return false;
		//if (this->sec != _t.sec) return false;
		if (this->min != _t.min) return false;
		if (this->hour != _t.hour) return false;
		if (this->day != _t.day) return false;
		if (this->mon != _t.mon) return false;
		if (this->year != _t.year) return false;
		return true;
	}
	
	bool operator> (str_time & _t)
	{
		if (this->fileName != _t.fileName) return false;
		if (this->year > _t.year) return true;
		else if (this->year == _t.year)
		{
		std::cout << "dojechalo";

			if (this->mon > _t.mon) return true;
			else if (this->mon == _t.mon)
			{
				if (this->day > _t.day) return true;
				else if (this->day == _t.day)
				{
					if (this->hour > _t.hour) return true;
					else if (this->hour == _t.hour)
					{
						if (this->min > _t.min) return true;
						else if (this->min == _t.min)
						{
							if (this->sec > _t.sec) return true;
						}
					
					}
				} 
			}
		}
		return false;
	}
};

char * readFile(const char * _name);
std::vector<std::string> cutWords(const char *_text);
int * findElements(const std::vector<std::string> & _array, const char * _elementName);

std::vector<str_time> loadCompileDates()
{
	std::vector<str_time> time;
	std::string check;
	std::fstream file("compileDate");
	if (file.is_open())
	{
		file >> check;
		if (check == "FirstCompilation")
			return time;
			
		while (check != "END")
		{
			str_time t;
			t.fileName = check;
			file >> t.sec >> t.min >> t.hour >> t.day >> t.mon >> t.year;
			time.push_back(t);
			
			file >> check;
		}
		
		file.close();
	}
	
	return time;
}


std::vector<str_time> loadModificationDates(std::vector<std::string> _src, std::vector<std::string> _hdr)
{
	std::vector<str_time> time;
	
	for (int i = 0; i < _src.size(); i++)
	{
		struct stat s;
		std::string nm(_src[i] + ".cpp");
		stat(nm.c_str(), &s);
		struct tm * t = localtime(&s.st_mtime);
		str_time str_t;
		str_t.fileName = _src[i] + ".cpp";
		str_t.sec = t->tm_sec;
		str_t.min = t->tm_min;
		str_t.hour = t->tm_hour;
		str_t.day = t->tm_mday;
		str_t.mon = t->tm_mon;
		str_t.year = t->tm_year;
		time.push_back(str_t);
	}
	
	
	for (int i = 0; i < _hdr.size(); i++)
	{
		struct stat s;
		stat(_hdr[i].c_str(), &s);
		struct tm * t = localtime(&s.st_mtime);
		str_time str_t;
		str_t.fileName = _hdr[i];
		str_t.sec = t->tm_sec;
		str_t.min = t->tm_min;
		str_t.hour = t->tm_hour;
		str_t.day = t->tm_mday;
		str_t.mon = t->tm_mon;
		str_t.year = t->tm_year;
		time.push_back(str_t);
	}
	
	return time;
}

void saveCompilationDates(std::vector<std::string> _src, std::vector<std::string> _hdr)
{
	time_t _t = time(NULL);
	struct tm * t = localtime(&_t);
	std::fstream file;
	file.open("compileDate");//, std::ios::trunc);//, std::ios::in);// | std::ios::trunc //std::ios::openmode 
	if (file.is_open())
	{
	std::cout << "src:" << _src.size() << "hdr:"<< _hdr.size() << "\n";
	std::cout <<"today: "<<t->tm_sec<<" "<<t->tm_min<<" "<<t->tm_hour<<" "<<t->tm_mday<<" "<<t->tm_mon<<" "<<t->tm_year<<"\n"; 
	//file << "huj";
		for (int i = 0; i < _src.size(); i++)
		{
			std::string name(_src[i] + ".cpp");
			file << name << " " << t->tm_sec << " " << t->tm_min << " " << t->tm_hour 
				 << " " << t->tm_mday << " " << t->tm_mon << " " << t->tm_year << (char)10; 
		}
		
		for (int i = 0; i < _hdr.size(); i++)
		{
			file << _hdr[i] << " " << t->tm_sec << " " << t->tm_min << " " << t->tm_hour
				 << " " << t->tm_mday << " " << t->tm_mon << " " << t->tm_year << (char)10; 
		}
		
		file << "END";
		
		file.close();
	}
}

int main()
{

    char * data = readFile("files");
	std::vector<std::string> words = cutWords(data);

	std::vector<std::string> sources;
	int *srcEl = findElements(words, "SOURCES");
	for (int i = *srcEl; i <= *(srcEl + 1); i++)
		sources.push_back(words[i]);
	delete [] srcEl;
	
	std::vector<std::string> headers;
	int *hdrEl = findElements(words, "HEADERS");
	if (*hdrEl != 69)
	for (int i = *hdrEl; i <= *(hdrEl + 1); i++)
		headers.push_back(words[i]);
	delete [] hdrEl;
    
    std::vector<std::string> includePath;
    int *incPathEl = findElements(words, "INCLUDE PATH");
    if (*incPathEl != 69)
    for (int i = *incPathEl; i <= *(incPathEl + 1); i++)
        includePath.push_back(words[i]); 
	delete [] incPathEl;
    
    std::vector<std::string> libPath;
    int *libPathEl = findElements(words, "LIB PATH");
    if (*libPathEl != 69)
    for (int i = *libPathEl; i <= *(libPathEl + 1); i++)
        libPath.push_back(words[i]);
	delete [] libPathEl;
    
    std::vector<std::string> fileToLink;
    int *fileLinkEl = findElements(words, "FILE TO LINK");
    if (*fileLinkEl != 69)    
    for (int i = *fileLinkEl; i <= *(fileLinkEl + 1); i++)
        fileToLink.push_back(words[i]);
	delete [] fileLinkEl;
    
	std::vector<std::string> exec;
	int *execEl = findElements(words, "EXECUTABLE");
	for (int i = *execEl; i <= *(execEl + 1); i++)
		exec.push_back(words[i]);
	delete [] execEl;

	int correct = 0;
	
	std::vector<std::string> filesToCompile;
	std::vector<str_time> compileDates = loadCompileDates();
	std::vector<str_time> modifyDates = loadModificationDates(sources, headers);
	
	for (int i = 0; i < compileDates.size(); i++)
	{
		for (int j = 0; j < modifyDates.size(); j++)
		{
			if (modifyDates[i] > compileDates[i]) // TYTAJ TYTAJ TYTAJ TYTAJ TYTAJ TYTAJ
			{
				filesToCompile.push_back(compileDates[i].fileName);
				break;
			}
		}
	}

std::cout<<"\nCompile dates:\n";
for (int i = 0; i < compileDates.size(); i++)
	std::cout<<compileDates[i].fileName<<" "<<compileDates[i].sec<<" "<<compileDates[i].min<<" "<<compileDates[i].hour<<" "<<compileDates[i].day<<" "<<compileDates[i].mon<<" "<<compileDates[i].year<<"\n";

std::cout<<"\nModify dates:\n";
for (int i = 0; i < modifyDates.size(); i++)
	std::cout<<modifyDates[i].fileName<<" "<<modifyDates[i].sec<<" "<<modifyDates[i].min<<" "<<modifyDates[i].hour<<" "<<modifyDates[i].day<<" "<<modifyDates[i].mon<<" "<<modifyDates[i].year<<"\n";


std::cout<<"\nCompile dates:"<<compileDates.size()<<"\n";
std::cout<<"\nModify dates:"<<modifyDates.size()<<"\n";
std::cout<<"\nFile to compile:"<<filesToCompile.size()<<"\n";

bool doItFirstTime = false;
if (compileDates.size() < 1)
	doItFirstTime = true;

	std::string obj("obj/");
	for (int i = 0; i < sources.size(); i++)
	{
		bool doIt = false;
		for ( int k = 0; k < filesToCompile.size(); k++)
			if (sources[i] + ".cpp" == filesToCompile[k])
				doIt = true;
		if (doIt || doItFirstTime)
		{
			std::string compile1("g++ -c -std=c++11 " + sources[i] + ".cpp");
		    if (includePath.size() > 0)
		        compile1 += " -I " + includePath[0];
		    compile1 += " -o " + obj + sources[i] + ".o";
		    std::cout << "LOG: " << compile1 << std::endl;
			correct = system(compile1.c_str());
			if (correct != 0)
				break;
		}
	}

	if (correct == 0)
	{	
		std::string compile3("g++ -std=c++11 ");
		for (int i = 0; i < sources.size(); i++)
		{
			compile3 += obj + sources[i] + ".o ";
		}

		compile3 += " -o " + exec[0];
		if (libPath.size() > 0)
		    compile3 += " -L " + libPath[0];
		for (int i = 0; i < fileToLink.size(); i++)
		{
		    compile3 += " " + fileToLink[i];
		}
	   
		std::cout << "\nLOG: " << compile3 << std::endl;   
		system(compile3.c_str());
		
		saveCompilationDates(sources, headers);
	}
	
	delete [] data;
    return 0;
}



char * readFile(const char * _name)
{
    FILE * file = fopen(_name, "r+");
    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    char * data = new char[length + 1];
    fseek(file, 0, SEEK_SET);
    memset(data, 1, length);
    fread(data, 1, length, file);
    fclose(file);
    
    return data;
}

std::vector<std::string> cutWords(const char *_text)
{
    std::vector<std::string> words;
    int i = 0;
    while (_text[i] != '|')
    {
    	// 10 - line feed, 9 - horizontal tab
    	if((int) _text[i] != 10 && (int) _text[i] != 9)
    	{
    		std::string str;
    		words.push_back(str);
    	}
    	
    	// 10 - line feed, 9 - horizontal tab
		while ((int) _text[i] != 10 && (int) _text[i] != 9)
		{
			words.back() += _text[i];
			i++;
		}
		i++;
    }
		
	return words;
}

int * findElements(const std::vector<std::string> & _array, const char * _elementName)
{
	int *tab = new int[2]; //	first/last element
	tab[0] = 69; tab[1] = 69;
	
	for (int i = 0; i < _array.size(); i++)
	{
		if (_array[i] == _elementName)
		{
			if (_array[i+1] == "{" && _array[i+2] != "}")
			{
				tab[0] = i + 2;
				int k = 2;
				while (_array[i + k] != "}")
				{
					tab[1] = i + k;
					k++;
				}
			}
		}
	}
	
	return tab;
}

