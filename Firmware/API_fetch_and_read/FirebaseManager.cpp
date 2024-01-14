#include "FirebaseManager.h"

FirebaseManager::FirebaseManager(const char* referenceUrl) : firebase(referenceUrl) {
  // Initialize the 'firebase' object using the provided referenceUrl
}

String FirebaseManager::getString(const String& path) {
  return firebase.getString(path);
}
