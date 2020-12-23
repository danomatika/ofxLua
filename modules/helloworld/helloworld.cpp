// 2020 Dan Wilcox <danomatika@gmail.com>
#include "helloworld.h"
#include <ofMain.h>
#include <iostream>

void greet() {
  std::cout << "hello world" << std::endl;
}

void BitmapGreet::draw(float x, float y) {
  ofSetColor(200, 100, 100);
  ofDrawBitmapString("hello world", x, y);
}
