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

int main(int argc, char * const argv[])
{
    QString password = "your_password_from_accounts.xml";
    QString key = "your_jid_from_accounts.xml";
    QString out = decodePassword(password,key);
    
    std::cout << out.toStdString() << std::endl;
	
	return EXIT_SUCCESS;
}