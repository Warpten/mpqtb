#pragma once

#include <vector>
#include <string>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace fs {
    namespace casc {
        class casc_file_system;

        class casc_file : public std::enable_shared_from_this<casc_file>
        {
            friend class casc_file_system;

            casc_file(HANDLE fileHandle);

        public:
            ~casc_file();

            void Close();
            size_t GetFileSize() const;
            uint8_t const* GetData();
            size_t ReadBytes(size_t offset, size_t length, uint8_t* buffer, size_t bufferSize);

        private:
            HANDLE _fileHandle;
            std::vector<uint8_t> _fileData;
        };

        class casc_file_system final
        {
        public:
#define KEY(NAME)                                          \
            struct NAME {                                  \
                uint8_t operator [] (size_t i) const {     \
                    return bytes[i];                       \
                }                                          \
                                                           \
                inline operator uint8_t* () {              \
                    return bytes;                          \
                }                                          \
                                                           \
            private:                                       \
                uint8_t bytes[16];                         \
            };
            KEY(encoding_key);
            KEY(content_key);
#undef KEY

            casc_file_system(std::string_view rootFolder, std::string_view product = "wow");
            ~casc_file_system();

            std::shared_ptr<casc_file> open_file(std::string_view filePath) const;
            std::shared_ptr<casc_file> open_file(content_key ckey) const;
            std::shared_ptr<casc_file> open_file(encoding_key ekey) const;
            std::shared_ptr<casc_file> open_file(size_t fdid) const;

        private:
            HANDLE _storageHandle;
            std::string _currentRootFolder;
        };
    }
}