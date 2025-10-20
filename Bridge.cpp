#include <iostream>
#include <memory>
#include <string>

// Abstract implementation
class Storage {
public:
    // abstract method DownloadFile
    virtual File* DownloadFile(std::string filename) const = 0;
    // abstract method Save
    virtual std::string Save() const = 0;
};

// Implementation of class Storage
class CloudStorage : public Storage {
public:
    // download file from remote storage logic
    virtual File* DownloadFile(std::string filename) const override {
        // logic
    }
    // saving file in the cloud storage logic
    virtual std::string Save() const override {
        return "cloud storage";
    }
};

// Implementation of class Storage
class LocalStorage : public Storage {
public:
    // download file from local storage logic
    virtual File* DownloadFile(std::string filename) const override {
        // logic
    };
    // saving file in the local storage logic
    virtual std::string Save() const override {
        return "local storage";
    }
};

// Implementation of class Storage
class FTPStorage : public Storage {
public:
    // download file from ftp storage logic
    virtual File* DownloadFile(std::string filename) const override {
        // logic
    };
    // saving file in the ftp storage logic
    virtual std::string Save() const override {
        return "ftp storage";
    }
};

// Abstraction class
class File {
protected:
    std::shared_ptr<Storage> storage;

public:
    File(std::shared_ptr<Storage> storage) : storage(storage) {}
    virtual ~File() = default;

    virtual void Save() const {
        std::cout << "File has been saved in the " << storage->Save() << '\n';
    }
};

// Redefined Abstraction class Document
class Document : public File {
public:
    Document(std::shared_ptr<Storage> storage) : File(storage) {}

    virtual void Save() const override {
        std::cout << "Document has been saved in the " << storage->Save() << '\n';
    }
};

// Redefined Abstraction class AudioFile
class AudioFile : public File {
public:
    AudioFile(std::shared_ptr<Storage> storage) : File(storage) {}

    virtual void Save() const override {
        std::cout << "Audio file has been saved in the " << storage->Save() << '\n';
    }
};

// Redefined Abstraction class TextFile
class TextFile : public File {
public:
    TextFile(std::shared_ptr<Storage> storage) : File(storage) {}
    
    virtual void Save() const override {
        std::cout << "Text file has been saved in the " << storage->Save() << '\n';
    }
};

// Redefined Abstraction class ImageFile
class ImageFile : public File {
public:
    ImageFile(std::shared_ptr<Storage> storage) : File(storage) {}

    virtual void Save() const override {
        std::cout << "Image file has been saved in the " << storage->Save() << '\n';
    }
};

// Redefined Abstraction class VideoFile
class VideoFile : public File {
public:
    VideoFile(std::shared_ptr<Storage> storage) : File(storage) {}

    virtual void Save() const override {
        std::cout << "Video file has been saved in the " << storage->Save() << '\n';
    }
};

// demostrates client's interaction with File
void ClientCode(File& file) {
    file.Save();
}

int main() {
    // creating LocalStorage instance and object File
    std::shared_ptr<Storage> storage = std::make_shared<LocalStorage>();
    std::unique_ptr<File> file = std::make_unique<File>(storage);
    
    ClientCode(*file);
    // creating CloudStorage and object Document
    storage = std::make_shared<CloudStorage>();
    file = std::make_unique<Document>(storage);

    ClientCode(*file);
    // creating TextFile | storage = CloudStorage
    file = std::make_unique<TextFile>(storage);
    
    ClientCode(*file);
    // creating FTPStorage and object VideoFile
    storage = std::make_shared<FTPStorage>();
    file = std::make_unique<VideoFile>(storage);

    ClientCode(*file);
    // creating ImageFile | storage = FTPStorage
    file = std::make_unique<ImageFile>(storage);

    ClientCode(*file);
    return 0;
}