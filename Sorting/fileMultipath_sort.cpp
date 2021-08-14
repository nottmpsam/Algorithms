#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <string>
/* multipath sort */
#define ll long long

bool createFile(const std::string& str, int n);
bool is_fileSort(const std::string& str);
bool readFile(const std::string& str);
bool sortFile();

int main()
{
    sortFile();
    return 0;
}

bool is_fileSort(const std::string& str)
{
    std::ifstream f(str);
    if (!f.is_open())
        return false;
    ll temp;
    f >> temp;
    ll buf = temp;
    while (f >> temp) 
        if (temp < buf)
            return false;
    f.close();
    return true;
}

bool readFile(const std::string& str)
{
    std::fstream f(str, std::ios_base::in);
    ll y;
    if (f.is_open()) { 
	    while (f >> y)
	        std::cout << y << " ";
	    std::cout << std::endl;
	    f.close();
	    return true;
	}
	return false;
}

bool sortFile()
{
    int n ;
    while (!(std::cin >> n)) {
        std::cin.clear();
       while (std::cin.get() != '\n')
            continue;
    }
    n = (n <= 1 ? 3 : n);
    ll n2 = 2 * n;
    ll temp;
   
    std::string nameFile;
    std::string outputFile;
    int Range;
    std::cout << "Enter range:" << std::endl;
    std::cin >> Range;
    std::fstream f(nameFile);
    std::cout << "Enter name of file: " << std::endl;
    std::cin.get();
    getline(std::cin, nameFile);
    createFile(nameFile, Range);
    f.open(nameFile, std::ios_base::in);
    while (!f.is_open()) {
        getline(std::cin, nameFile);
        f.open(nameFile, std::ios_base::in);
    }

    std::cout << "Output file name: " << std::endl;
    while (getline(std::cin, outputFile) && outputFile == nameFile);
    std::fstream fo(outputFile, std::ios_base::out);
    std::string str = "f.txt";

    auto t2 = std::chrono::high_resolution_clock::now();
    std::fstream* nFiles = new std::fstream[n2];
    for (int i = 0; i < n; ++i) 
        nFiles[i].open(std::to_string(i) + str, std::ios_base::out);
    f >> temp;
    ll i = 0;
    nFiles[0] << temp << " "; 
    ll buf = temp;
    while (!f.eof()) {
        while (f >> temp && buf <= temp) {
            nFiles[i] << temp << " ";
            buf = temp;
        }
        i = (++i == n ? 0 : i);
        if (!f.eof()) {
            buf = temp;
            nFiles[i] << buf << " ";
        }
    }
    for (int i = 0; i < n; ++i) 
        nFiles[i].close();
    ll* array= new ll[n2];
    for (int i = 0; i < n2; ++i) 
        array[i] = i;
    ll* values = new ll[n];
    ll* arrayFlags = new ll[n];

    ll countEof;
    ll countCurrentSegments;
    ll countTotal;
    
    bool flag = true;
    bool firstflag = true;

    while (firstflag)
    {
        countTotal = 0;
        countEof= 0;
        countCurrentSegments = 0;

        for (int i = 0; i < n; ++i) 
            arrayFlags[i] = 0;
        for (int i = 0; i < n; ++i)
            nFiles[array[i]].open(std::to_string(array[i])+str, std::ios_base::in);
        for (int i = n; i < n2; ++i)  
            nFiles[array[i]].open(std::to_string(array[i])+str, std::ios_base::out);
        for (int i = 0; i < n; ++i) {
            if (nFiles[array[i]] >> temp) 
                values[i] = temp;
            else 
            {
                arrayFlags[i] = -1;
                values[i] = -1;
                if (++countEof== n)
                    firstflag = false;

            }
        }

        ll ny = array[n];
        flag = true;
        while (flag && firstflag)
        {
            ll x; 
            for (x = 0; x < n && arrayFlags[x]; ++x);
            ll min = values[x];
            for (int i = x + 1; i < n; ++i) 
            {
                if (min > values[i] && !arrayFlags[i])
                {
                    min = values[i];
                    x = i; 
                }
            }
            nFiles[ny] << values[x] << " ";
            if (nFiles[array[x]] >> temp) 
            {
                if (values[x] > temp) 
                {
                    ++countCurrentSegments;
                    arrayFlags[x] = 1;
                }
                values[x] = temp;
            } 
            else
            {
                ++countEof;
                arrayFlags[x] = -1;
            }
            if (countCurrentSegments + countEof == n) 
            {
                if (++ny == n2 || ny == n)
                    ny = array[n];
                for (int i = 0; i < n; ++i)
                {
                    if (arrayFlags[i] != -1)
                        arrayFlags[i] = 0;
                }
                ++countTotal;
            }
            if (countEof== n)
            {
                flag = false;
            }
        }
        if (countTotal == array[n] + 1) 
        {
            firstflag = false;
            ll k = array[n];
            nFiles[k].close();
            nFiles[k].open(std::to_string(array[n])+str, std::ios_base::in);
            while (nFiles[k] >> temp) 
            {
                fo << temp << " ";
            }
            fo.close();
        }
        else 
        {
            for (int i = 0; i < n; ++i) 
            {
                ll temp = array[i];
                array[i] = array[i+n];
                array[i+n] = temp;
            }
        }
        for (int i = 0; i < n2; ++i) 
            nFiles[i].close();
    }
    delete [] arrayFlags;
    delete [] values;
    delete [] nFiles;
    delete [] array;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::micro> elapsed = t1 - t2;
    std::cout << elapsed.count() / 1000000 << " sec. " << std::endl;
    bool rf = is_fileSort(outputFile);
    std::cout << "Sorted: " << std::boolalpha << rf << std::endl;
    std::cout << "Reading file... \"" << outputFile << "\":" << std::endl;
    for (int i = 0; i < n2; ++i) 
    {
        std::string tstr = std::to_string(i) + str;
        remove(tstr.c_str());
    }
    readFile(outputFile);
    return rf;
    
}

bool createFile(const std::string& str, int n)
{
	std::ofstream f(str);
	srand(time(0));
	for (int i = 0; i < n; ++i) {
		f << -500 +rand() % 1000 << " ";		
	}
	f.close();
	return true;
}
