#pragma once
#include "draco/io/file_writer_interface.h"
#include <memory>
#include <string>

using namespace draco;

class UD_FileWriter : public FileWriterInterface {
public:
	// Creates and returns a UD_FileWriter that writes to |file_name|.
	// Returns nullptr when |file_name| cannot be opened for writing.
	static std::unique_ptr<FileWriterInterface> Open(
		const std::string& file_name);

	UD_FileWriter() = delete;
	UD_FileWriter(const UD_FileWriter&) = delete;
	UD_FileWriter& operator=(const UD_FileWriter&) = delete;

	UD_FileWriter(UD_FileWriter&&) = default;
	UD_FileWriter& operator=(UD_FileWriter&&) = default;

	// Closes |file_|.
	~UD_FileWriter() override;

	// Writes |size| bytes to |file_| from |buffer|. Returns true for success.
	bool Write(const char* buffer, size_t size) override;

private:
	UD_FileWriter(FILE* file) : file_(file) {}

	FILE* file_ = nullptr;
	static bool registered_in_factory_;
};
