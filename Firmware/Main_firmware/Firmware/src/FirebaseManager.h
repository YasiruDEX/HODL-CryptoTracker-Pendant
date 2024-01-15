#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <ESP8266Firebase.h>

class FirebaseManager {
public:
  FirebaseManager(const char* referenceUrl);
  String getString(const String& path);
private:
  Firebase firebase;
};

#endif
