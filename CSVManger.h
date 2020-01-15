#ifndef CSVMANGER_H
#define CSVMANGER_H

#include <fstream>
#include <iostream>
#include <QString>

class CSVManger
{
public:
    CSVManger();

    QString csvPath = nullptr;
    std::ofstream csvFile;
};

#endif // CSVMANGER_H
