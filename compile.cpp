#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h> // for console writing

// 62 row do REPERACJI

char * readFile(const char * _name);
std::vector<std::string> cutWords(const char *_text);
int * findElements(const std::vector<std::string> & _array, const char * _elementName);


int main()
{
    char * data = readFile("files");
	std::vector<std::string> words = cutWords(data);

	std::vector<std::string> sources;
	int *srcEl = findElements(words, "SOURCES");
	for (int i = *srcEl; i <= *(srcEl + 1); i++)
		sources.push_back(words[i]);
	delete [] srcEl;
    
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

	std::string obj("obj/");
	for (int i = 0; i < sources.size(); i++)
	{
		std::string compile1("g++ -c -std=c++11 " + sources[i] + ".cpp");
        if (includePath.size() > 0)
            compile1 += " -I " + includePath[0];
        compile1 += " -o " + obj + sources[i] + ".o";
        std::cout << "LOG: " << compile1 << std::endl;
		system(compile1.c_str());
	}
	
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

