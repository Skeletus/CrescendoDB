#pragma once
#pragma once
#include <fstream>
#include <string>
#include <stdexcept>

template <typename T>
class BinaryWriter {
public:
    BinaryWriter(const std::string& filename) : filename(filename) {}

    void Write(int pageID, const T& obj) 
    {
        std::ofstream ofs(filename, std::ios::binary | std::ios::app);
        if (!ofs) 
        {
            throw std::runtime_error("Cannot open file for writing");
        }

        auto data = obj.Serialize();
        size_t dataSize = data.size();

        ofs.clear();
        ofs.seekp(pageID * dataSize, std::ios::beg);
        // Write the size of the data first
        ofs.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        // Write the serialized data
        ofs.write(data.data(), data.size());
        std::cout << "\nSE ESCRIBIO BYTES: " << data.size();
        if (!ofs.good()) {
            std::cerr << "Error at writing in file: " << filename << std::endl;
        }
        ofs.close();
    }

    T Read(const int& pageID) 
    {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            throw std::runtime_error("Cannot open file for reading");
        }

        ifs.clear();
        ifs.seekg(pageID * sizeof(size_t), std::ios::beg);

        size_t dataSize;
        ifs.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        if (!ifs.good()) {
            throw std::runtime_error("Error reading data size");
        }

        std::vector<char> data(dataSize);
        ifs.read(data.data(), data.size());
        if (!ifs.good()) {
            std::cerr << "Error at reading page at: " << pageID << std::endl;
        }
        ifs.close();

        return T::Deserialize(data);
        
    }

private:
    std::string filename;
};

