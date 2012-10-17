//
//  main.cpp
//  PSI plus password recovery
//
//  Created by Viktor Chukhantsev on 8/28/12.
//  Copyright (c) 2012 Viktor Chukhantsev. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <QString>
#include <algorithm>
#include <string>

using namespace std;

int hexChar2int(char c)
{
    if(c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if(c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if(c >= '0' && c <= '9')
        return c - '0';
    
    return 0;
}

QString decodePassword(const QString &pass, const QString &key)
{
    QString result;
    int n1, n2;
    
    if(key.length() == 0)
        return pass;
    
    for(n1 = 0, n2 = 0; n1 < pass.length(); n1 += 4) {
        ushort x = 0;
        if(n1 + 4 > pass.length())
            break;
        x += hexChar2int(pass.at(n1).toAscii())*4096;
        x += hexChar2int(pass.at(n1+1).toAscii())*256;
        x += hexChar2int(pass.at(n1+2).toAscii())*16;
        x += hexChar2int(pass.at(n1+3).toAscii());
        QChar c(x ^ key.at(n2++).unicode());
        result += c;
        if(n2 >= key.length())
            n2 = 0;
    }
    return result;
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char ** begin, char ** end, const std::string & option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[])
{
    
    if(cmdOptionExists(argv, argv+argc, "-j") && cmdOptionExists(argv, argv+argc, "-p"))
    {
        QString password = getCmdOption(argv, argv+argc, "-p");
        QString key = getCmdOption(argv, argv+argc, "-j");
        QString out = decodePassword(password,key);
        
        std::cout << "Your password is:" << out.toStdString() << std::endl;
    }

    if(cmdOptionExists(argv, argv+argc, "-h") || !cmdOptionExists(argv, argv+argc, "-j") || !cmdOptionExists(argv, argv+argc, "-p"))
    {
        std::cout << "Usage: pppr [OPTIONS]" << std::endl << std::endl;
        std::cout << " -h Help." << std::endl;
        std::cout << " -j Your Jabber ID" << std::endl;
        std::cout << " -p Your encoded password" << std::endl;        
    }

	return EXIT_SUCCESS;
}