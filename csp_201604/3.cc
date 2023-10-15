#include <deque>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
using std::cin;
using std::cout;

#define DEBUG false

struct FileNode {
  std::string fileName;
  FileNode *parent = nullptr;
  std::unordered_map<std::string, FileNode *> child;
  FileNode(std::string fileName, FileNode *parent)
      : fileName(fileName), parent(parent) {}

  ~FileNode() {
    parent = nullptr;
    if (child.empty()) {
      return;
    }
    for (auto &pair : child) {
      delete pair.second;
    }
    child.clear();
  }
};

std::deque<std::string> &decode(std::deque<std::string> &target,
                                const std::string &oriStr) {
  // if original string is empty string:
  if (oriStr.empty()) {
    target.push_back(".");
    return target;
  }
  // if dont start with '/', begin with "." or ".."
  if (oriStr.front() != '/') {
    target.push_back(".");
  }

  std::stringstream ss(oriStr);
  while (ss.good()) {
    std::string tempStr;
    std::getline(ss, tempStr, '/');
    if (tempStr.empty()) {
      continue;
    }
    target.push_back(tempStr);
  }
  return target;
}

FileNode *absGotoByStr(FileNode *filePtr, std::deque<std::string> &filePaths) {
  if (filePaths.empty()) {
    return filePtr;
  }
  if (filePaths.front() == ".") {
    filePaths.pop_front();
    return absGotoByStr(filePtr, filePaths);
  }
  if (filePaths.front() == "..") {
    filePaths.pop_front();
    return absGotoByStr(
        (filePtr->parent == nullptr ? filePtr : filePtr->parent), filePaths);
  }

  // if not found
  if (filePtr->child.find(filePaths.front()) == filePtr->child.end()) {
    filePtr->child.insert(
        {filePaths.front(), new FileNode(filePaths.front(), filePtr)});
  }

  std::string temp = filePaths.front();
  filePaths.pop_front();
  return absGotoByStr(filePtr->child[temp], filePaths);
}

void outputAbsPath(std::ostream &os, FileNode *filePtr) {
  // root specialization
  if (filePtr->parent == nullptr) {
    os << '/';
  }

  std::string tempStr;
  while (filePtr->parent != nullptr) {
    tempStr.insert(0, filePtr->fileName);
    tempStr.insert(0, 1, '/');
    filePtr = filePtr->parent;
  }
  os << tempStr << std::endl;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  FileNode *root = new FileNode("", nullptr);
  int nPath;
  (cin >> nPath).get();

  std::string oriDir;
  std::getline(cin, oriDir);
  std::deque<std::string> originalPathsDecoded;
  decode(originalPathsDecoded, oriDir);
#if DEBUG
  for (const auto &fileName : originalPathsDecoded) {
    cout << '\"' << fileName << '\"' << ' ';
  }
#endif

  FileNode *fallBackFilePtr = absGotoByStr(root, originalPathsDecoded);

#if DEBUG
  outputAbsPath(cout, fallBackFilePtr);
#endif

  for (int i = 0; i < nPath; i++) {
    std::string oriPath;
    std::getline(cin, oriPath);
    std::deque<std::string> decodedPath;
    decode(decodedPath, oriPath);
#if DEBUG
    for (const auto &fileName : decodedPath) {
      cout << '\"' << fileName << '\"' << ' ';
    }
#endif

    if (decodedPath.empty()) {
      outputAbsPath(cout, absGotoByStr(root, decodedPath));
      continue;
    }
    if (decodedPath.front() == ".") {
      decodedPath.pop_front();
      outputAbsPath(cout, absGotoByStr(fallBackFilePtr, decodedPath));
      continue;
    }
    outputAbsPath(cout, absGotoByStr(root, decodedPath));
  }

  delete root;
  return 0;
}