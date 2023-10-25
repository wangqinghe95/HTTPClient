#ifndef FILE_OPERATION_HPP_
#define FILE_OEPRATION_HPP_

#include <sys/stat.h>
#include <unistd.h>
#include <string>

class FileOperation
{
public:
    bool isFileExist(const std::string str_filename, int mode = F_OK);
    bool isFolderExist(const std::string str_foldername);
    bool mkdirFolder(const std::string& path);
    bool createFile(const std::string str_filename, mode_t mode = 0777);
    bool createFolder(const std::string str_foldername, mode_t mode = 0777);
    //bool createFolder(const std::string str_foldername, mode_t mode)
    int wirteContent2File(const std::string &str_content, const std::string str_filename);
    int readContentFromFile(std::string& str_out_content, const std::string str_filename);

private:
    bool isValidFolderPath(const std::string& path);
};

#endif