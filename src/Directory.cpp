//
// Created by Aviv Israel on 14/11/2017.
//
#include "../include/Files.h"
#include <algorithm>




using namespace std;


// compare by name function
bool compareByName( BaseFile *lhs,  BaseFile *rhs);





// compare by size function
bool compareBySize( BaseFile *lhs, BaseFile *rhs);

Directory::Directory(string name, Directory *parent) : BaseFile(name), parent(parent){
	if (parent != nullptr) {
		depth = parent->getDepth() + 1;
	}
}

Directory *Directory::getParent() const {
    return parent;
}

int Directory::getDepth() {
	return depth;
}

void Directory::setParent(Directory *newParent) {
    parent = newParent;

}

bool Directory::isFile() {
	return false;
}

void Directory::addFile(BaseFile *file) {
	if (file != NULL) {
		children.push_back(file);
	}
}

void Directory::removeFile(string name) {
    for(vector<BaseFile*>::iterator iterator1 = children.begin(); iterator1 != children.end(); ++iterator1){
        if((*iterator1)->getName() == name){
            children.erase(iterator1);
        }

    }
}

void Directory::removeFile(BaseFile *file) {
    if(file != NULL) {
        removeFile(file->getName());
    }
}

void Directory::sortByName() {
    sort(children.begin(), children.end(), compareByName);

}
void Directory::sortBySize() {
    sort(children.begin(), children.end(), compareBySize);

}

vector<BaseFile *> Directory::getChildren() {
    return children;
}

int Directory::getSize() {
    int totalSize = 0;

    for(vector<BaseFile*>::iterator iterator1 = children.begin(); iterator1 != children.end(); ++iterator1){
        totalSize += (*iterator1)->getSize();
    }
    return totalSize;
}

string Directory::getAbsolutePath() {
    string absolutePath;

    if(parent == nullptr){		
		return "/";
    }

	absolutePath = parent->getAbsolutePath();
	if (absolutePath != "/") {
		return absolutePath + "/" + getName();
	}
    return absolutePath + getName();
}

bool Directory::isContainDirectory(string fileName) {
	for (vector<BaseFile*>::iterator it = children.begin(); it != children.end(); ++it) {
		if ((*it)->getName() == fileName && !(*it)->isFile()) {
			return true;
		}
	}
	return false;
}

bool Directory::isContainFile(string fileName) {
	for (vector<BaseFile*>::iterator it = children.begin(); it != children.end(); ++it) {
		if ((*it)->getName() == fileName && (*it)->isFile()) {
			return true;
		}
	}
	return false;
}

BaseFile* Directory::getFileByName(string fileName) {
	for (vector<BaseFile*>::iterator it = children.begin(); it != children.end(); ++it) {
		if ((*it)->getName() == fileName ) {
			return *it;
		}
	}
	return nullptr;
}

bool compareByName(BaseFile *lhs, BaseFile *rhs) { return lhs->getName() < rhs->getName(); }

bool compareBySize( BaseFile *lhs, BaseFile *rhs) { return lhs->getSize() < rhs->getSize(); }