#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Record.h"
#include "BinaryWriter.h"
#include "CrescendoDBProject.h"

int main()
{   
    Record obj;
    obj.AddAttribute("age", Attribute::Type::INT);
    obj.AddAttribute("height", Attribute::Type::DOUBLE);
    obj.AddAttribute("name", Attribute::Type::VARCHAR, 4);

    std::string strxd = "saa";
    if (strxd.length() > 4)
    {
        std::cout << strxd.length() << " error exceeds varchar capacity: " << 4 << "\n";
    }
    else
    {
        obj.SetValue("age", 30);
        obj.SetValue("height", 5.9);
        obj.SetValue("name", strxd.c_str());
    }

    obj.PrintValues();

    std::vector<char> dataSerial = obj.Serialize();
    for (int i = 0; i < dataSerial.size(); i++)
    {
        std::cout << " data: ->" << dataSerial.data();
        std::cout << std::endl;
    }

    Record objDeserial = Record::Deserialize(dataSerial);
    objDeserial.PrintValues();
    
    
    return 0;

}