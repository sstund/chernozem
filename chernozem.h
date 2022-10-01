#ifndef CHERNOZEM_H
#define CHERNOZEM_H
#include <Arduino.h>

const char serTerm[] = {'\n', ' '};

class chernozem {
private:
  unsigned long tout;
  Stream *port;

  bool isTerm(char &c) {
    for(const char &e : serTerm) {
      if(e == c) {
        return 1;
      }
    }
    return 0;
  }

  void wantNotTerm() {
    while(1) {
      if(port->available()) {
        char c = port->peek();
        if(isTerm(c)) {
          port->read();          
        } else {
          return;
        }
      }
    }
    delay(tout);
  }
public:

  chernozem(int _tout = 50) {
    tout = _tout;
  }

  chernozem(Stream *_port, int _tout = 50) {
    port = _port;
    tout = _tout;
  }

  template<class T>
  void readInt(T &ans) {
    ans = 0;
    wantNotTerm();
    bool neg = false;
    if(port->peek() == '-') {
      neg = 1;
      port->read();
      wantNotTerm();
    }
    while(port->available()) {
      char c = port->peek();
      if(c >= '0' && c <= '9') {
        ans*=10;
        ans+=c-'0';
        port->read();
      } else {
        break;
      }
      delay(tout);
    }
    if(neg)
      ans = -ans;
    return;
  }

  void readString(String &ans) {
    ans = "";
    wantNotTerm();
    while(port->available()) {
      char c = port->peek();
      if(isTerm(c)) {
        break;
      } else {
        ans += c;
        port->read();
      }
      delay(tout);
    }
  }
  template<class T>
  void readChar(T &ans) {
    wantNotTerm();
    ans = port->read();
    return;
  }
  template<class T>
  void print(T msg) {
    port->print(msg);
  }
};

chernozem& operator>>(chernozem &ser, char &ans) {
  ser.readChar(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, unsigned char &ans) {
  ser.readChar(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, short &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, unsigned short &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, int &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, unsigned int &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, long &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, unsigned long &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, long long &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, unsigned long long &ans) {
  ser.readInt(ans);
  return ser;
}

chernozem& operator>>(chernozem &ser, String &ans) {
  ser.readString(ans);
  return ser;
}

template<class T>
chernozem& operator<<(chernozem &ser, T msg) {
  ser.print(msg);
  return ser;
}

#endif // CHERNOZEM_H