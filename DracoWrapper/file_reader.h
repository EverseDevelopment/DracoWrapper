#pragma once
#include "draco/io/file_reader_interface.h"
#include <memory>
#include <string>

using namespace draco;

class UD_FileReader : public FileReaderInterface {
public:
    // Creates and returns a UD_FileReader that reads from |file_name|.
    // Returns nullptr when the file does not exist or cannot be read.
    static std::unique_ptr<FileReaderInterface> Open(
        const std::string& file_name);

    UD_FileReader() = delete;
    UD_FileReader(const UD_FileReader&) = delete;
    UD_FileReader& operator=(const UD_FileReader&) = delete;

    UD_FileReader(UD_FileReader&&) = default;
    UD_FileReader& operator=(UD_FileReader&&) = default;

    // Closes |file_|.
    ~UD_FileReader() override;

    // Reads the entire contents of the input file into |buffer| and returns true.
    bool ReadFileToBuffer(std::vector<char>* buffer) override;
    bool ReadFileToBuffer(std::vector<uint8_t>* buffer) override;

    // Returns the size of the file.
    size_t GetFileSize() override;

private:
    UD_FileReader(FILE* file, const std::string& file_name) : file_(file), file_name_(file_name) {}

    FILE* file_ = nullptr;
    std::string file_name_;
    static bool registered_in_factory_;
};
