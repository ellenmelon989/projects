class Letter {
  char q;
  Letter (char letter) {
    q = Character.toUpperCase(letter);
  }
  void displayl(float x, float y, float size) {
    textSize(size);
    text(q, x, y);
  }
  void colorwhite() {
   fill(255);
   noFill();
  }
  void colorblack() {
    fill(0);
    noFill();
  }
}
