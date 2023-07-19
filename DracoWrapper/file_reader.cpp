#include "file_reader.h"
#include "pch.h"

std::unique_ptr<FileReaderInterface> UD_FileReader::Open(
    const std::string& file_name) {
    if (file_name.empty()) {
        return nullptr;
    }

    FILE* raw_file_ptr;
    fopen_s(&raw_file_ptr,file_name.c_str(), "rb");

    if (raw_file_ptr == nullptr) {
        return nullptr;
    }

    std::unique_ptr<FileReaderInterface> file(new (std::nothrow) UD_FileReader(raw_file_ptr,file_name));
    if (file == nullptr)
    {
        //UDWARNING("Out of memory");
        fclose(raw_file_ptr);
        return nullptr;
    }

    return file;
}
bool UD_FileReader::ReadFileToBuffer(std::vector<char>* buffer) {
    if (buffer == nullptr)
    {
        return false;
    }
    buffer->clear();

    const size_t file_size = GetFileSize();
    if (file_size == 0) {
        //UDWARNING("Unable to obtain file size or file empty");
        return false;
    }

    buffer->resize(file_size);
    return fread(buffer->data(), 1, file_size, file_) == file_size;
}

bool UD_FileReader::ReadFileToBuffer(std::vector<uint8_t>* buffer) {
    if (buffer == nullptr) {
        return false;
    }
    buffer->clear();

    const size_t file_size = GetFileSize();
    if (file_size == 0) {
        //UDWARNING("Unable to obtain file size or file empty");
        return false;
    }

    buffer->resize(file_size);
    return fread(buffer->data(), 1, file_size, file_) == file_size;
}

size_t UD_FileReader::GetFileSize() {
    struct stat stat_buf;
    int rc = stat(file_name_.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

UD_FileReader::~UD_FileReader() {
    fclose(file_);
}