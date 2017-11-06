#include "resources/resource_finder.h"

#include <boost/filesystem.hpp>
#include <iostream>

namespace ifx {

ResourceFinder::ResourceFinder(
        const std::vector<ResourceFinderRootDirectory>& root_directories,
        const std::vector<ResourceFinderExtension>& look_for_extensions) :
        root_directories_(root_directories),
        look_for_extensions_(look_for_extensions) {}

void ResourceFinder::Update(){
    for(const auto& directory : root_directories_){
        UpdateDirectory(directory.root);
    }
}

void ResourceFinder::UpdateDirectory(const std::string& root_directory){
    boost::filesystem::path root_path(root_directory);
    boost::filesystem::recursive_directory_iterator iterator(root_path);
    for (auto &&dir : iterator) {
        auto file_name = dir.path().string();
        if(IsCorrectFile(file_name)){
            found_resources_.push_back(file_name);
        }
    }
}

bool ResourceFinder::IsCorrectFile(const std::string& file_name){
    for(const auto& extension : look_for_extensions_){
        auto extension_string = "." + extension.extension;
        if(EndsWith(file_name, extension_string)){
            return true;
        }
    }
    return false;
}

bool ResourceFinder::EndsWith(const std::string &str,
                              const std::string &end) {
    auto program_extension_length = end.length();
    auto dir_name_length = str.length();

    auto substr = str.substr(dir_name_length - program_extension_length,
                             program_extension_length);

    return substr == end;
}

}