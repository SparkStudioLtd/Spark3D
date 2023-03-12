#include "CoreFramework.h"

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
    LoadedAsset outputFile;
    std::ifstream infile;
    infile.open(this->m_AssetFilePath, std::ios::binary);

    infile.seekg(0);

    infile.read(outputFile.type, 4);
    infile.read((char*)&outputFile.version, sizeof(uint32_t));

    uint32_t jsonlen = 0;
    infile.read((char*)&jsonlen, sizeof(uint32_t));

    uint32_t bloblen = 0;
    infile.read((char*)&bloblen, sizeof(uint32_t));

    outputFile.description.resize(jsonlen);
    infile.read(outputFile.description.data(), jsonlen);
    

    outputFile.blob.resize(bloblen);
    infile.read(outputFile.blob.data(), bloblen);
    this->m_LoadedAsset = outputFile;
    this->typeLoad();
}

void Asset::typeLoad()
{
    nlohmann::json desc = nlohmann::json::parse(this->m_LoadedAsset.description);
    AssetType type = this->getEnum(std::vector<char>(this->m_LoadedAsset.type, this->m_LoadedAsset.type+sizeof(this->m_LoadedAsset.type)));

    this->m_Name = desc["name"];
    this->m_Type = type;
    this->m_AssetInfo = desc;
}

std::vector<char> Asset::getTypeShort()
{
    std::vector<char> characters;
    switch (this->m_AssetType) {
    case FONT:
        characters.push_back('F');
        characters.push_back('O');
        characters.push_back('N');
        characters.push_back('T');
        break;
    }
    return characters;
}

std::vector<char> Asset::getBlob()
{
    std::ifstream file(this->m_ToSavePath, std::ios::ate | std::ios::binary);

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

AssetType Asset::getEnum(std::vector<char> type)
{
    if (type[0] == 'F' && type[1] == 'O' && type[2] == 'N' && type[3] == 'T') {
        return FONT;
    }
    return AssetType();
}

std::string Asset::getDescription()
{
    this->m_AssetInfo["name"] = m_Name;
    return this->m_AssetInfo.dump();
}

std::vector<Asset*> AssetManager::m_Assets;
void AssetManager::loadFromFolder()
{
    m_Assets.clear();
    std::string path = "./Content";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        Asset* asset = new Asset();
        std::cout << entry.path().string() << std::endl;
        asset->m_AssetFilePath = entry.path().string();
        asset->load();
        m_Assets.push_back(asset);
    }
}

Asset* AssetManager::getAsset(std::string m_Name)
{
    for (Asset* _asset : m_Assets) {
        if (_asset->m_Name == m_Name) {
            return _asset;
        }
    }
    return nullptr;
}

void AssetManager::loadFromResources()
{
    std::string path = "./res";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_directory()) {
            Asset* asset = new Asset();
            asset->m_Name = entry.path().filename().string();
            asset->m_ToSavePath = entry.path().string();
            asset->m_LoadedAsset.blob = asset->getBlob();
            if (entry.path().extension() == ".fbx" || entry.path().extension() == ".obj") {
                asset->m_AssetType = MODEL;
                asset->m_Type = MODEL;
            }
            m_Assets.push_back(asset);
        }
    }
}

void AssetManager::reload()
{
    AssetManager::loadFromFolder();
#ifdef SPARK_EDITOR
    AssetManager::loadFromResources();
#endif
}

void AssetManager::loadAssetHandles()
{
    for (Asset* asset : AssetManager::m_Assets) {
        switch (asset->m_AssetType) {
        case MODEL:
            asset->m_Handle = ModelLoader::loadMeshFromAsset(Spark::graphicsContext, asset);
            break;
        }
    }
}
