#include <memory>
#include <fstream>
#include <vector>

class Header; // Forward declaration

class Section
{
private:
    /* data */
};

class elfio
{
private:
    std::unique_ptr<Header> header = nullptr;
    std::vector<std::unique_ptr<Section>> sections;
public:
    elfio(/* args */);
    ~elfio();

    int32_t save(const std::string &file_name);
    int32_t save(std::ostream &stream);
};

elfio::elfio(/* args */)
{
}

elfio::~elfio()
{
}

int32_t elfio::save(const std::string &file_name)
{
    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open())
    {
        return -1;
    }
    return save(file);
}

int32_t elfio::save(std::ostream &stream)
{
    if (header == nullptr)
    {
        return -1;
    }

    header->save(stream);

    for (const auto &section : sections)
    {
        section->save(stream);
    }


    return 0;
}
