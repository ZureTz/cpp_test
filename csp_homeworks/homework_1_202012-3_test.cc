#include <climits>
#include <deque>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
typedef unsigned long long ull;

class File {
protected:
  std::string fileName;

public:
  File(std::string fileName) : fileName(std::move(fileName)) {}
  virtual bool createSubFolder(const std::string fileName) = 0;
  virtual bool createSubNormalFile(const std::string &fileName,
                                   const ull fileSize) = 0;
  virtual ull getSize() const = 0;
  virtual bool isNormalFile() const = 0;
  virtual std::unordered_map<std::string, std::shared_ptr<File>> &
  getChild() = 0;
  virtual ull &getLD() = 0;
  virtual ull &getLR() = 0;

  // recursive search
  static std::shared_ptr<File>
  recursiveSearch(std::shared_ptr<File> filePtr,
                  const std::deque<std::string> &filenames,
                  std::deque<std::string>::const_iterator fileIt) {
    if (fileIt->empty()) {
      return filePtr;
    }
    const bool isThisANormalFile = filePtr->isNormalFile();
    if (fileIt + 1 == filenames.end()) {
      auto it = filePtr->getChild().find(*fileIt);
      if (it == filePtr->getChild().end()) {
        return nullptr;
      }
      return it->second;
    }

    // if filename not found
    if ((filePtr->getChild()).find(*fileIt) == (filePtr->getChild()).end()) {
      return nullptr;
    }

    // found recursively if the file is found but its a folder
    return recursiveSearch((filePtr->getChild()).find(*fileIt)->second,
                           filenames, fileIt + 1);
  }

  // recursive create
  static bool recursiveCreate(std::shared_ptr<File> filePtr,
                              const std::deque<std::string> &filenames,
                              std::deque<std::string>::const_iterator fileIt,
                              ull size) {

    if (fileIt->empty()) {
      return filePtr->createSubNormalFile(*fileIt, size);
    }
    // if going to last one
    if (fileIt + 1 == filenames.end()) {
      if (filePtr->isNormalFile()) {
        return false;
      }
      return filePtr->createSubNormalFile(*fileIt, size);
    }

    // basically not found the file
    if ((filePtr->getChild()).find(*fileIt) == (filePtr->getChild()).end()) {
      filePtr->createSubFolder(*fileIt);
      return recursiveCreate(filePtr->getChild().find(*fileIt)->second,
                             filenames, fileIt + 1, size);
    }

    // if found and not the last one
    // isNormalFile
    if (filePtr->getChild().find(*fileIt)->second->isNormalFile()) {
      return false;
    }
    // isFolder
    return recursiveCreate(filePtr->getChild().find(*fileIt)->second, filenames,
                           fileIt + 1, size);
  }
};

// Normal file
class NormalFile : public File {
  static std::unordered_map<std::string, std::shared_ptr<File>> undefinedChild;
  ull size;

public:
  NormalFile(std::string fileName, ull size)
      : File(std::move(fileName)), size(size) {}
  ull getSize() const override { return size; }
  ull &getLD() override { return size; }
  ull &getLR() override { return size; }

  bool createSubFolder(const std::string fileName) override { return false; }
  bool createSubNormalFile(const std::string &fileName,
                           const ull fileSize) override {
    return false;
  } // does nothing

  bool isNormalFile() const override { return true; }

  std::unordered_map<std::string, std::shared_ptr<File>> &getChild() override {
    return undefinedChild;
  }
};
std::unordered_map<std::string, std::shared_ptr<File>>
    NormalFile::undefinedChild = {};

// Folder
class Folder : public File {
  std::unordered_map<std::string, std::shared_ptr<File>> child;
  ull LD, LR;

public:
  Folder(std::string fileName, ull LD = 0, ull LR = 0)
      : File(std::move(fileName)), LD(0ull), LR(0ull) {}

  ull getSize() const override {
    // if empty specialization
    if (child.empty()) {
      return 0ull;
    }

    ull totalSize = 0ull;
    for (auto it = child.begin(); it != child.end(); it++) {
      totalSize += it->second->getSize();
    }
    return totalSize;
  }

  ull getLDSize() const {
    ull sumSize = 0ull;
    for (const auto pair : child) {
      sumSize += pair.second->isNormalFile() ? pair.second->getSize() : 0;
    }
    return sumSize;
  }

  ull &getLD() override { return LD; }
  ull &getLR() override { return LR; }

  // to create a new folder
  bool createSubFolder(const std::string fileName) override {
    auto derivedPtr = std::make_shared<Folder>(fileName);
    child.insert(
        std::make_pair(fileName, std::static_pointer_cast<File>(derivedPtr)));
    return true;
  }

  // to create a new file
  bool createSubNormalFile(const std::string &fileName,
                           const ull fileSize) override {
    if (LD && (getLDSize() + fileSize > LD)) {
      return false;
    }
    if (LR && (getSize() + fileSize > LR)) {
      return false;
    }
    auto it = child.find(fileName);
    if (it != child.end()) {
      if (!it->second->isNormalFile()) {
        return false;
      }
      child.erase(it);
    }

    auto derivedPtr = std::make_shared<NormalFile>(fileName, fileSize);
    child.insert(
        std::make_pair(fileName, std::static_pointer_cast<File>(derivedPtr)));
    return true;
  }

  bool isNormalFile() const override { return false; }

  std::unordered_map<std::string, std::shared_ptr<File>> &getChild() override {
    return child;
  }
};

namespace IO {
void decodeToArray(std::deque<std::string> &targetFilePaths,
                   const std::string &originalString) {
  std::string tempString;
  bool isReading = false;
  for (auto it = originalString.begin(); it != originalString.end(); it++) {
    if (!isReading && *it == '/') {
      isReading = true;
      continue;
    }

    if (isReading && *it != '/') {
      tempString.push_back(*it);
      continue;
    }

    targetFilePaths.push_back(tempString);
    tempString.clear();
    isReading = false;
    it--;
  }
  targetFilePaths.push_back(tempString);
}
} // namespace IO

int main(int argc, char const *argv[]) {
  int numOfInstructions;
  (cin >> numOfInstructions).get();

  std::shared_ptr<Folder> root = std::make_shared<Folder>("");
  for (int i = 0; i < numOfInstructions; i++) {
    std::string temp_input;
    std::getline(cin, temp_input);
    const char instructionType = *temp_input.begin();

    temp_input.erase(temp_input.begin(), temp_input.begin() + 1);
    std::stringstream ss(temp_input);

    if (instructionType == 'C') {
      std::string oriString;
      ull fileSize;
      ss >> oriString >> fileSize;
      std::deque<std::string> filePaths;
      IO::decodeToArray(filePaths, oriString);
      if (File::recursiveCreate(root, filePaths, filePaths.begin(), fileSize) ==
          false) {
        cout << 'N' << std::endl;
        continue;
      }
      cout << 'Y' << std::endl;
      continue;
    }

    if (instructionType == 'R') {
      std::string oriString;
      ss >> oriString;
      std::deque<std::string> filePaths;
      IO::decodeToArray(filePaths, oriString);
      std::string lastFileName = filePaths.back();
      filePaths.pop_back();
      auto ptr = File::recursiveSearch(root, filePaths, filePaths.begin());
      if (ptr == nullptr) {
        cout << 'Y' << std::endl;
        continue;
      }
      auto itChildToFind = (ptr->getChild()).find(lastFileName);
      if (itChildToFind != (ptr->getChild().end())) {
        (ptr->getChild()).erase(itChildToFind);
      }
      cout << 'Y' << std::endl;
      continue;
    }

    if (instructionType == 'Q') {
      std::string oriString;
      ull LD, LR;
      ss >> oriString >> LD >> LR;
      std::deque<std::string> filePaths;
      IO::decodeToArray(filePaths, oriString);
      auto filePtr = File::recursiveSearch(root, filePaths, filePaths.begin());
      if (filePtr == nullptr || filePtr->isNormalFile()) {
        cout << 'N' << std::endl;
        continue;
      }

      auto getLDSize = [=] {
        int sum = 0;
        for (const auto &pair : filePtr->getChild()) {
          sum += pair.second->isNormalFile() ? pair.second->getSize() : 0;
        }
        return sum;
      };

      if (LD && getLDSize() > LD) {
        cout << 'N' << std::endl;
        continue;
      }
      if (LR && filePtr->getSize() > LR) {
        cout << 'N' << std::endl;
        continue;
      }

      filePtr->getLD() = LD;
      filePtr->getLR() = LR;
      cout << 'Y' << std::endl;
      continue;
    }
  }

  return 0;
}