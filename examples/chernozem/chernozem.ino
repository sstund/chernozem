#include "chernozem.h"

chernozem ss(&Serial);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char oper; ss >> oper;
  if(oper == 'X') {
    int x,y; ss >> x >> y;
    ss << '!' << x << ' ' << y << '\n';
  } else if(oper == 'Y') {
    String s; ss >> s;
    ss << "Mlya " << s << ";\n";
  }
}
  