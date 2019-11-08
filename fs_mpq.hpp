#pragma once

#include <vector>
#include <string>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace fs {
    namespace mpq {
        class mpq_file_system;

        class mpq_file : public std::enable_shared_from_this<mpq_file>
        {
            friend class mpq_file_system;

            mpq_file(HANDLE fileHandle);

        public:
            ~mpq_file();

            void Close();
            size_t GetFileSize() const;
            uint8_t const* GetData();
            size_t ReadBytes(size_t offset, size_t length, uint8_t* buffer, size_t bufferSize);

        private:
            HANDLE _fileHandle;
            std::vector<uint8_t> _fileData;
        };

        class mpq_file_system final
        {
        public:
            mpq_file_system(std::string_view rootFolder);
            ~mpq_file_system();

            std::shared_ptr<mpq_file> OpenFile(const std::string& filePath) const;

            bool FileExists(const std::string& relFilePath) const;

        private:
            std::vector<HANDLE> _archiveHandles;
            std::string _currentRootFolder;
        };
    }
}