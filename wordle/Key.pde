class Key {
  char letter;
  float x, y;
  float w, h;
  int state;  // 0: default, 1: gray, 2: yellow, 3: green
  
  Key(char letter, float x, float y, float w, float h) {
    this.letter = letter;
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    state = DEFAULT;
  }
  
  void display() {
    if (state == GREEN) {
      fill(83, 141, 78);  // green 
    } else if (state == YELLOW) {
      fill(181, 159, 59); // yellow 
    } else if (state == GRAY) {
      fill(58, 58, 60);   // gray 
    } else {
      fill(200);          // default 
    }
    stroke(0);
    rect(x, y, w, h, 5);
    fill(0);
    textAlign(CENTER, CENTER);
    textSize(20);
    text(letter, x + w/2, y + h/2);
  }
}
