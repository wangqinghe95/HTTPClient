#include "FileOperation.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <regex>

bool FileOperation::isFileExist(const std::string str_filename, int mode)
{
    return (access(str_filename.data(), mode) != -1);
}

bool FileOperation::isFolderExist(const std::string str_foldername)
{
    return (0 == access(str_foldername.data(), F_OK));
}

bool FileOperation::createFile(const std::string str_filename, mode_t mode)
{
    if(isFileExist(str_filename)){
        return 0;
    }

    std::size_t path_postition = str_filename.rfind('/');
    if(path_postition != std::string::npos)
    {
        std::string folder_name = str_filename.substr(0, path_postition);
        if(false == createFolder(folder_name)){
            return false;
        }
    }

    std::ofstream new_file(str_filename);
    new_file.close();

    return true;
}

bool FileOperation::createFolder(const std::string str_foldername, mode_t mode)
{
    if(isValidFolderPath(str_foldername)) {
        return false;
    }

    size_t start_search_pos = 0;
    size_t pos = str_foldername.find('/', start_search_pos);
    while(pos != std::string::npos)
    {
        std::string check_path = str_foldername.substr(0, pos);
        if(isFolderExist(check_path) == false)
        {
            if(false == mkdirFolder(check_path))
            {
                return false;
            }
        }
        start_search_pos = pos + 1;
        pos = str_foldername.find('/', start_search_pos);
    }

    // "./test/test" and "./test/test/"
    if(start_search_pos != str_foldername.size()) {
        mkdirFolder(str_foldername);
    }
    return isFolderExist(str_foldername);
}

int FileOperation::wirteContent2File(const std::string &str_content, const std::string str_filename)
{
    std::ofstream outfile(str_filename);
    outfile << str_content;
    outfile.close();

    return 0;
}

int FileOperation::readContentFromFile(std::string& str_out_content, const std::string str_filename)
{
    str_out_content.clear();
    std::fstream readFile(str_filename);
    int res = 0;
    if(readFile.is_open()) {
        std::string readLine;
        while(getline(readFile, readLine)) {
            str_out_content += readLine;
        }
        readFile.close();
        res = str_out_content.size();
    }
    else {
        res = -1;
    }

    return res;
}

bool FileOperation::mkdirFolder(const std::string& path)
{
    return (0 == mkdir(path.data(), 0777));
}

bool FileOperation::isValidFolderPath(const std::string& path)
{
    static const std::regex pattern("^\\/([a-zA-Z0-9_-]+\\/)*[a-zA-Z0-9_-]+$");
    return std::regex_match(path, pattern);
}