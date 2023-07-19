#include "file_writer.h"
#include "pch.h"

void SplitPathPrivate(const std::string& full_path,
	std::string* out_folder_path,
	std::string* out_file_name) {
	const auto pos = full_path.find_last_of("/\\");
	if (pos != std::string::npos) {
		if (out_folder_path) {
			*out_folder_path = full_path.substr(0, pos);
		}
		if (out_file_name) {
			*out_file_name = full_path.substr(pos + 1, full_path.length());
		}
	}
	else {
		if (out_folder_path) {
			*out_folder_path = ".";
		}
		if (out_file_name) {
			*out_file_name = full_path;
		}
	}
}

bool DirectoryExists(const std::string& path) {
	struct stat path_stat;

	// Check if |path| exists.
	if (stat(path.c_str(), &path_stat) != 0) {
		return false;
	}

	// Check if |path| is a directory.
	if (path_stat.st_mode & S_IFDIR) {
		return true;
	}
	return false;
}

bool CheckAndCreatePathForFile(const std::string& filename) {
	std::string path;
	std::string basename;
	SplitPathPrivate(filename, &path, &basename);

	const bool directory_exists = DirectoryExists(path);
	return directory_exists;
}

bool UD_FileWriter::registered_in_factory_ =
draco::FileWriterFactory::RegisterWriter(UD_FileWriter::Open);

UD_FileWriter::~UD_FileWriter() { fclose(file_); }

std::unique_ptr<FileWriterInterface> UD_FileWriter::Open(
	const std::string& file_name) {
	if (file_name.empty()) {
		return nullptr;
	}
	if (!CheckAndCreatePathForFile(file_name)) {
		return nullptr;
	}

	FILE* raw_file_ptr;
	errno_t err;
	err = fopen_s(&raw_file_ptr, file_name.c_str(), "wb");
	if (err != 0)
	{
		return nullptr;
	}


	std::unique_ptr<UD_FileWriter> file(new (std::nothrow)
		UD_FileWriter(raw_file_ptr));
	if (file == nullptr) {
		//UDWARNING("Out of memory");
		fclose(raw_file_ptr);
		return nullptr;
	}

#ifndef DRACO_OLD_GCC
	return file;
#else
	return std::move(file);
#endif
}

bool UD_FileWriter::Write(const char* buffer, size_t size) {
	return fwrite(buffer, 1, size, file_) == size;
}
