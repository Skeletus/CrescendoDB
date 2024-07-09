#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Record.h"
#include "Varchar.h"
#include "BinaryWriter.h"
#include "CrescendoDBProject.h"

int main()
{   
    Record obj;
    obj.AddAttribute("age", Attribute::Type::INT);
    obj.AddAttribute("height", Attribute::Type::DOUBLE);
    obj.AddAttribute("name", Attribute::Type::VARCHAR, 4);

    const char* xd = "xd121212";
    if (sizeof(xd) > 4)
    {
        std::cout << "error exceeds varchar capacity: " << 4;
    }
    else
    {
        obj.SetValue("age", 30);
        obj.SetValue("height", 5.9);
        obj.SetValue("name", xd);
    }

    obj.PrintValues();
    
    
    return 0;

}