class Box {
  float bx;
  float by;
  float bWidth;
  float bHeight;
  Letter l;
  boolean empty;
  boolean inword;
  boolean inpos;
  boolean checked;

  Box (float x, float y, float bw, float bh) {
    bx = x;
    by = y;
    bWidth = bw;
    bHeight = bh;
    l = new Letter (' ');
    empty = true;
    inpos = false;
    inword = false;
    checked = false;
  }
  void display() {
    if (!empty && !checked) {
      fill(255);
      l.colorblack();
      stroke(0);
    } else if (inword) {
      fill(181, 159, 59);
      stroke(255);
     } else if (inpos) {
      fill(83, 141, 78);
      stroke(255);
    } else if (!empty) {
      fill(#7f7f7f);
      stroke(0);
    }
    if (empty) {
      fill(255);
      stroke(0);
    }
    strokeWeight(3);
    rect(bx+95, by+12, bWidth-7, bHeight-7, 7);
    if (inpos || inword || (!empty && checked)) {
      l.colorwhite();
    }
    l.displayl(bx+(1.6*bWidth), by+bHeight*0.6, bWidth*0.66);
  }
  void eraseletter() {
    empty = true;
  }
}
