#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using std::cin;
using std::cout;
typedef long long ll;

struct Node {
  std::string name;
  ll LD = 0, LR = 0;
  ll sizeD = 0, sizeR = 0, size;
  std::unordered_map<std::string, Node *> child;
  Node *parent = nullptr;
  bool isFolder = true;
  // true : folder, false : normal file

  Node(std::string str, ll size = 0) : name(std::move(str)), size(size) {}
  ~Node() {
    parent = nullptr;
    if (child.empty()) {
      return;
    }
    for (auto it = child.begin(); it != child.end(); it++) {
      delete it->second;
    }
    child.clear();
  }
};

std::deque<std::string> &decodeFilePath(std::deque<std::string> &target,
                                       const std::string &oriString) {
  std::stringstream ss(oriString);
  while (ss.good()) {
    std::string tempStr;
    std::getline(ss, tempStr, '/');
    target.push_back(tempStr);
  }
  target.pop_front();
  if (target.front() == "") {
    target.clear();
  }
  return target;
}

bool isLRQualified(Node *filePtr, ll size) {
  if (filePtr == nullptr) {
    return true;
  }
  if (filePtr->LR && (filePtr->sizeR + size > filePtr->LR)) {
    return false;
  }
  return isLRQualified(filePtr->parent, size);
}

inline bool isLDQualified(Node *filePtr, ll size) {
  return (filePtr->LD == 0) || (filePtr->sizeD + size <= filePtr->LD);
}

bool create(Node *filePtr, std::deque<std::string> &filePaths, ll fileSize) {
  if (filePtr == nullptr) {
    return false;
  }

  auto it = filePtr->child.find(filePaths.front());
  if (filePaths.size() == 1) {
    bool isChecked = false;
    if (it != filePtr->child.end()) {
      // if found and it is a folder
      if (it->second->isFolder) {
        // cout << "cannot replace folder" << std::endl;
        return false;
      }

      // if found but it is a normal file
      // if not qualified
      if (!(isLDQualified(filePtr, fileSize - it->second->size) &&
            isLRQualified(filePtr, fileSize - it->second->size))) {
        // cout << "not qualified in the end" << std::endl;
        return false;
      }
      isChecked = true;
      ll size = it->second->size;
      filePtr->sizeD -= size;
      Node *tempPtr = filePtr;
      while (tempPtr != nullptr) {
        tempPtr->sizeR -= size;
        tempPtr = tempPtr->parent;
      }

      delete it->second;
      filePtr->child.erase(it);
    }

    // if not found
    // detect if satisfies LD and LR
    if (!(isChecked || (isLDQualified(filePtr, fileSize) &&
                        isLRQualified(filePtr, fileSize)))) {
      // cout << "not qualified in the end" << std::endl;
      return false;
    }

    filePtr->child.insert(
        {filePaths.front(), new Node(filePaths.front(), fileSize)});
    (filePtr->child)[filePaths.front()]->isFolder = false;
    (filePtr->child)[filePaths.front()]->parent = filePtr;

    filePtr->sizeD += fileSize;
    Node *tempPtr = filePtr;
    while (tempPtr != nullptr) {
      tempPtr->sizeR += fileSize;
      tempPtr = tempPtr->parent;
    }
    // cout << "created." << std::endl;
    return true;
  }

  // filePaths.size() != 1
  // if not found a file (folder or normal file)
  if (it == filePtr->child.end()) {
    filePtr->child.insert({filePaths.front(), new Node(filePaths.front())});
    (filePtr->child)[filePaths.front()]->isFolder = true;
    (filePtr->child)[filePaths.front()]->parent = filePtr;

    std::string temp = filePaths.front();
    filePaths.pop_front();
    if (create((filePtr->child)[temp], filePaths, fileSize) == false) {
      // cout << "deleting used garbage..." << std::endl;
      auto deleteIt = filePtr->child.find(temp);
      delete deleteIt->second;
      filePtr->child.erase(deleteIt);
      return false;
    }
    return true;
  }

  // if found but its a normal file
  if (!it->second->isFolder) {
    // cout << "cannot replace folder" << std::endl;
    return false;
  }

  // if found and its a folder
  std::string temp = filePaths.front();
  filePaths.pop_front();
  return create((filePtr->child)[temp], filePaths, fileSize);
}

bool remove(Node *filePtr, std::deque<std::string> &filePaths) {
  if (filePtr == nullptr) {
    return false;
  }
  // if deleting root
  if (filePaths.empty()) {
    for (auto it = filePtr->child.begin(); it != filePtr->child.end(); ++it) {
      delete it->second;
    }
    filePtr->LD = filePtr->LR = filePtr->sizeD = filePtr->sizeR = 0;
    filePtr->child.clear();
    return true;
  }

  auto it = filePtr->child.find(filePaths.front());
  // undefined (file not found)
  if (it == filePtr->child.end()) {
    // cout << "file not found" << std::endl;
    return true;
  }

  // last one case
  if (filePaths.size() == 1) {
    // ll size = it->second->isFolder ? 0ll : it->second->size;
    // filePtr->sizeD -= size;
    // Node *tempPtr = filePtr;
    // while (tempPtr != nullptr) {
    //   tempPtr->sizeR -= size;
    //   tempPtr = tempPtr->parent;
    // }

    ll size;
    // if it is normal file
    if (it->second->isFolder == false) {
      size = it->second->size;
      filePtr->sizeD -= size;
    } else { // otherwise, it is folder
      size = it->second->sizeR;
    }
    Node *tempPtr = filePtr;
    while (tempPtr != nullptr) {
      tempPtr->sizeR -= size;
      tempPtr = tempPtr->parent;
    }

    delete it->second;
    filePtr->child.erase(it);
    // cout << "remove sucessful" << std::endl;
    return true;
  }

  // if file found and not the last one, most common case
  // it is a normal file
  if (!it->second->isFolder) {
    // cout << "folder in the way, does nothing" << std::endl;
    return true; // does nothing
  }

  // it is a folder
  filePaths.pop_front();
  return remove(it->second, filePaths);
}

bool qualify(Node *filePtr, std::deque<std::string> &filePaths, ll LD, ll LR) {
  if (filePtr == nullptr) {
    // cout << "file pointer is null" << std::endl;
    return false;
  }
  // if the file is root specialization
  if (filePaths.empty()) {
    if (!((LD == 0 || filePtr->sizeD <= LD) &&
          (LR == 0 || filePtr->sizeR <= LR))) {
      // cout << "unqualified@root" << std::endl;
      // cout << "LD, sizeD: " << LD << ", " << filePtr->sizeD << std::endl;
      // cout << "LR, sizeR: " << LR << ", " << filePtr->sizeR << std::endl;
      return false;
    }
    filePtr->LD = LD;
    filePtr->LR = LR;
    return true;
  }

  auto it = filePtr->child.find(filePaths.front());
  // if not found (any case)
  if (it == filePtr->child.end()) {
    // cout << "Path not exist."<<std::endl;
    return false;
  }
  // if found
  // if not a folder (any case)
  if (it->second->isFolder == false) {
    // cout << "file found is not a folder" << std::endl;
    return false;
  }

  // if filePath has only one left
  if (filePaths.size() == 1) {
    if (!((LD == 0 || it->second->sizeD <= LD) &&
          (LR == 0 || it->second->sizeR <= LR))) {
      // cout << "unqualified" << std::endl;
      // cout << "LD, sizeD: " << LD << ", " << filePtr->sizeD << std::endl;
      // cout << "LR, sizeR: " << LR << ", " << filePtr->sizeR << std::endl;
      return false;
    }
    it->second->LD = LD;
    it->second->LR = LR;
    return true;
  }

  // if not have only one left
  filePaths.pop_front();
  return qualify(it->second, filePaths, LD, LR);
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  // std::string str = "/usr/bin/etc/2.exe";
  // std::deque<std::string> target;
  // decodeFilePath(target, str);
  // for (const auto &str : target) {
  // cout << '\"' << str << '\"' << '\n';
  // }

  Node *root = new Node("");
  int n;
  (cin >> n).get();
  for (int i = 0; i < n; i++) {
    std::string instruction;
    std::getline(cin, instruction);
    const char instructionType = instruction.front();
    instruction.erase(instruction.begin(), instruction.begin() + 2);

    std::stringstream ss(instruction);
    std::string oriFilePaths;
    std::deque<std::string> filePaths;

    if (instructionType == 'C') {
      ll fileSize;
      ss >> oriFilePaths >> fileSize;
      decodeFilePath(filePaths, oriFilePaths);
      cout << (create(root, filePaths, fileSize) ? 'Y' : 'N') << std::endl;
      continue;
    }
    if (instructionType == 'R') {
      ss >> oriFilePaths;
      decodeFilePath(filePaths, oriFilePaths);
      cout << (remove(root, filePaths) ? 'Y' : 'N') << std::endl;
      continue;
    }
    if (instructionType == 'Q') {
      ll LD, LR;
      ss >> oriFilePaths >> LD >> LR;
      decodeFilePath(filePaths, oriFilePaths);
      cout << (qualify(root, filePaths, LD, LR) ? 'Y' : 'N') << std::endl;
      continue;
    }
  }

  return 0;
}