#include "AssetManager.h"
#include "Core/JSON.h"

std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s;
}
void Asset::save()
{
    std::string uuidAsset = random_string(16);
	std::ofstream outfile;
	outfile.open("./Content/" + uuidAsset + ".spark", std::ios::binary | std::ios::out);



    outfile.write(&this->getTypeShort()[0], 4);
    uint32_t version = 58;
    outfile.write((const char*)&version, sizeof(uint32_t));


    std::string json = this->getDescription();
    uint32_t length = json.size();
    outfile.write((const char*)&length, sizeof(uint32_t));

    std::vector<char> blob = this->getBlob();
    uint32_t bloblength = blob.size();
    outfile.write((const char*)&bloblength, sizeof(uint32_t));

    outfile.write(json.data(), length); 
    outfile.write(blob.data(), blob.size());

	outfile.close();
}

void Asset::load()
{
}

std::vector<char> Asset::getTypeShort()
{
    std::vector<char> characters;
    switch (this->m_AssetType) {
    case SHADER:
        characters.push_back('S');
        characters.push_back('H');
        characters.push_back('A');
        characters.push_back('R');
        break;
    }
    return characters;
}

std::vector<char> Asset::getBlob()
{
    std::ifstream file(this->m_Path, std::ios::ate | std::ios::binary);

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

std::string Asset::getDescription()
{
    nlohmann::json j;
    j["version"] = "430";
    return j.dump();
}

std::vector<Asset*> AssetManager::m_Assets;
void AssetManager::loadFromFolder()
{
}
