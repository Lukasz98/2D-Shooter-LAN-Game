#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h> // for console writing

#define drawOnScreenFileNames 0

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

int main()
{
    char * data = readFile("files");
	std::vector<std::string> words = cutWords(data);

#if 0
	for (int i = 0; i < words.size(); i++)
		std::cout << "w" << i << " " << words[i] << std::endl;
	std::cout<<"\n\n\n\n------------------\n";
#endif

//sources    
	std::vector<std::string> sources;
	int *srcEl = findElements(words, "SOURCES");
	for (int i = *srcEl; i <= *(srcEl + 1); i++)
		sources.push_back(words[i]);

#if drawOnScreenFileNames
	std::cout << "------------------\n";
	std::cout << "SOURCES\n";
	for (int i = 0; i < sources.size(); i++)
	std::cout << sources[i] << std::endl; 
#endif


//executables
	std::vector<std::string> exec;
	int *execEl = findElements(words, "EXECUTABLE");
	for (int i = *execEl; i <= *(execEl + 1); i++)
		exec.push_back(words[i]);
  
#if drawOnScreenFileNames
	std::cout << "------------------\n";
	std::cout << "EXECUTABLE\n";
	for (int i = 0; i < exec.size(); i++)
	std::cout << exec[i] << std::endl; 
	std::cout << "------------------\n";
#endif


	std::string libPath("/lukasz/Downloads");//("/usr");
//compiling
#if 0
	for (int i = 0; i < sources.size(); i++)
	{	
		std::string compile2("g++ -c -std=c++11 " + sources[i] + ".cpp -I " + libPath + "/include");
		system(compile2.c_str());
	
		std::string compile3(
			"g++ -std=c++11 " + sources[i] + ".o -o " + exec[0] + " -L " + 
			libPath + "/lib -lsfml-graphics -lsfml-window -lsfml-system"
		); 
		
		system(compile3.c_str());
	}
#endif

#if 1
	for (int i = 0; i < sources.size(); i++)
	{
		std::string compile1("g++ -c -std=c++11 " + sources[i] + ".cpp -I" + libPath + "/include");
		system(compile1.c_str());
	}
	
	//std::string compile2("g++ -std=c++11 -o " + exec[0] + " ");
	std::string compile3("g++ -std=c++11 ");
	for (int i = 0; i < sources.size(); i++)
	{
		//compile2 += sources[i] + ".o ";
		compile3 += sources[i] + ".o ";
	}
	//compile2 += " -L " + libPath + "/lib -lsfml-graphics -lsfml-window -lsfml-system";
	compile3 += " -o " + exec[0] + " -L " + libPath + "/lib -lsfml-graphics -lsfml-window -lsfml-system";
	system(compile3.c_str());
#endif

#if 0
	std::string execut("./" + exec[0]);
	system(execut.c_str());
#endif

    std::cout << std::endl;
    return 0;
}

