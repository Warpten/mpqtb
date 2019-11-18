#include "fs_casc.hpp"

#include <filesystem>
#include "casclib/src/CascLib.h"

namespace fs {
    namespace casc {
        using tstring = std::basic_string<TCHAR>;

        casc_file_system::casc_file_system(std::string_view rootFolder, std::string_view product)
        {
            if (rootFolder.length() == 0)
                return;

            if (rootFolder == _currentRootFolder)
                return;

            _currentRootFolder = rootFolder;

            std::string str{ rootFolder };
            str += ":";
            str += product;

            if (!CascOpenStorage(str.c_str(), 0, &_storageHandle))
                return;
        }

        casc_file_system::~casc_file_system()
        {
            CascCloseStorage(_storageHandle);
        }

        std::shared_ptr<casc_file> casc_file_system::open_file(std::string_view filePath) const
        {
            HANDLE fileHandle;
            if (CascOpenFile(_storageHandle, filePath.data(), 0, CASC_OPEN_BY_NAME, &fileHandle))
                return std::shared_ptr<casc_file>(new casc_file(fileHandle));

            throw std::runtime_error("file not found");
        }

        std::shared_ptr<casc_file> casc_file_system::open_file(casc_file_system::content_key ckey) const
        {
            HANDLE fileHandle;
            if (CascOpenFile(_storageHandle, ckey, 0, CASC_OPEN_BY_CKEY, &fileHandle))
                return std::shared_ptr<casc_file>(new casc_file(fileHandle));

            throw std::runtime_error("file not found");

        }

        std::shared_ptr<casc_file> casc_file_system::open_file(casc_file_system::encoding_key ekey) const
        {
            HANDLE fileHandle;
            if (CascOpenFile(_storageHandle, ekey, 0, CASC_OPEN_BY_EKEY, &fileHandle))
                return std::shared_ptr<casc_file>(new casc_file(fileHandle));

            throw std::runtime_error("file not found");
        }

        std::shared_ptr<casc_file> casc_file_system::open_file(size_t fdid) const
        {
            HANDLE fileHandle;
            if (CascOpenFile(_storageHandle, CASC_FILE_DATA_ID(fdid), 0, CASC_OPEN_BY_FILEID, &fileHandle))
                return std::shared_ptr<casc_file>(new casc_file(fileHandle));

            throw std::runtime_error("file not found");
        }

        casc_file::casc_file(HANDLE fileHandle)
        {
            _fileHandle = fileHandle;

            ULONGLONG fileSize = 0;
            if (!CascGetFileSize64(_fileHandle, &fileSize))
                throw std::runtime_error("oof");
            
            _fileData.resize(fileSize);

            DWORD bytesRead;
            if (!CascReadFile(_fileHandle, _fileData.data(), _fileData.size(), &bytesRead))
                throw std::runtime_error("Unable to read file");
            
            _fileData.resize(bytesRead);

            // Immediately close the handle, but don't call Close() - this would clear the buffer
            CascCloseFile(_fileHandle);
            _fileHandle = nullptr;
        }

        casc_file::~casc_file()
        {
            Close();
        }

        void casc_file::Close()
        {
            _fileData.clear();

            if (_fileHandle == nullptr)
                return;

            CascCloseFile(_fileHandle);
            _fileHandle = nullptr;
        }

        size_t casc_file::GetFileSize() const
        {
            return _fileData.size();
        }

        uint8_t const* casc_file::GetData()
        {
            return _fileData.data();
        }

        size_t casc_file::ReadBytes(size_t offset, size_t length, uint8_t* buffer, size_t bufferSize)
        {
            auto availableDataLength = GetFileSize() - offset;
            if (bufferSize < availableDataLength)
                availableDataLength = bufferSize;

            memcpy(buffer, _fileData.data() + offset, availableDataLength);

            return availableDataLength;
        }
    }
}