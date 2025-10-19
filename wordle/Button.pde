class Button {
  float x, y, w, h;
  String label;
  boolean hover = false;

  Button(float x, float y, float w, float h, String label) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.label = label;
  }

  void display() {
    hover = mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h;
    stroke(0);
    fill(hover ? color(200, 220, 255) : color(230));
    rect(x, y, w, h, 10);

    fill(0);
    textSize(20);
    text(label, x + w / 2, y + h / 2);
  }

  boolean isClicked(float mx, float my) {
    return mx > x && mx < x + w && my > y && my < y + h;
  }
}
