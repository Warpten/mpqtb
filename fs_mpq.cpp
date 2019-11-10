#include "fs_mpq.hpp"

#include <filesystem>
#include "stormlib/src/StormLib.h"

namespace fs {
    namespace mpq {
        using tstring = std::basic_string<TCHAR>;

        void load_directory(std::vector<HANDLE>& handles, std::filesystem::path directory_path) {
            std::filesystem::directory_iterator end;
            for (std::filesystem::directory_iterator itr(directory_path); itr != end; ++itr)
            {
                if (std::filesystem::is_directory(itr->path())) {
                    load_directory(handles, itr->path());
                    continue;
                }

                if (itr->path().extension() != ".MPQ")
                    continue;

                HANDLE fileHandle;
                if (SFileOpenArchive(itr->path().generic_string().c_str(), 0, MPQ_OPEN_READ_ONLY, &fileHandle))
                    handles.push_back(fileHandle);
                else
                    throw std::runtime_error("Error loading archive.");
            }
        }

        mpq_file_system::mpq_file_system(std::string_view rootFolder)
        {
            if (rootFolder.length() == 0)
                return;

            if (rootFolder == _currentRootFolder)
                return;

            _currentRootFolder = rootFolder;

            for (HANDLE archiveHandle : _archiveHandles)
                SFileCloseArchive(archiveHandle);

            try {
                std::filesystem::path rootPath = rootFolder;

                _archiveHandles.clear();
                load_directory(_archiveHandles, rootPath / "Data");
            }
            catch (const std::exception & e) {
                return; // Check for more specific exceptions layer
            }
        }

        mpq_file_system::~mpq_file_system()
        {
            for (HANDLE archiveHandle : _archiveHandles)
                SFileCloseArchive(archiveHandle);

            _archiveHandles.clear();
        }

        std::shared_ptr<mpq_file> mpq_file_system::OpenFile(const std::string& filePath) const
        {
            for (HANDLE archiveHandle : _archiveHandles)
            {
                HANDLE fileHandle;
                if (SFileOpenFileEx(archiveHandle, filePath.c_str(), 0, &fileHandle))
                    return std::shared_ptr<mpq_file>(new mpq_file(fileHandle));
            }

            return { };
        }

        bool mpq_file_system::FileExists(const std::string& relFilePath) const
        {
            for (HANDLE archiveHandle : _archiveHandles)
            {
                HANDLE fileHandle;
                if (SFileOpenFileEx(archiveHandle, relFilePath.c_str(), 0, &fileHandle))
                {
                    SFileCloseFile(archiveHandle);
                    return true;
                }
            }

            return false;
        }

        mpq_file::mpq_file(HANDLE fileHandle)
        {
            _fileHandle = fileHandle;

            _fileData.resize(GetFileSize());
            DWORD bytesRead;
            if (!SFileReadFile(_fileHandle, _fileData.data(), _fileData.size(), &bytesRead, nullptr))
                throw std::runtime_error("Unable to read file");

            _fileData.resize(bytesRead);

            // Immediately close the handle, but don't call Close() - this would clear the buffer
            SFileCloseFile(_fileHandle);
            _fileHandle = nullptr;
        }

        mpq_file::~mpq_file()
        {
            Close();
        }

        void mpq_file::Close()
        {
            _fileData.clear();

            if (_fileHandle == nullptr)
                return;

            SFileCloseFile(_fileHandle);
            _fileHandle = nullptr;
        }

        size_t mpq_file::GetFileSize() const
        {
            return _fileData.size();
        }

        uint8_t const* mpq_file::GetData()
        {
            return _fileData.data();
        }

        size_t mpq_file::ReadBytes(size_t offset, size_t length, uint8_t* buffer, size_t bufferSize)
        {
            auto availableDataLength = GetFileSize() - offset;
            if (bufferSize < availableDataLength)
                availableDataLength = bufferSize;

            memcpy(buffer, _fileData.data() + offset, availableDataLength);

            return availableDataLength;
        }
    }
}