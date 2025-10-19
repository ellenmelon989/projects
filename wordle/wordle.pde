// Global constants
int rows = 6;
int cols = 5;
int BOX_HEIGHT = 80;
int BOX_WIDTH = 80;
int curRow = 0;
int curCol = 0;
boolean darkmode;
boolean ifword;
boolean gameOver = false;
String[] guess;
String[] answers;
String test;   // will hold the current guess word as constructed
String ans;
Button dailyButton;
Button randomButton;
boolean daily = false;
String dailyword = null;
int rcount= 0;

Box[][] b;

ArrayList<Key> keys;  // list of on-screen keys

final int DEFAULT = 0;
final int GRAY = 1;
final int YELLOW = 2;
final int GREEN = 3;

void setup() {
  size(600, 875);

  answers = loadStrings("wordle_answer_words.txt");
  guess = loadStrings("wordle_guess_words.txt");
  
  b = new Box[rows][cols];
  boxPos();
  
  // pick a random answer
  int r = int(random(answers.length));
  ans = answers[r];
  
  keys = new ArrayList<Key>();
  String[] keyboardRows = { "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM" };
  int keyW = 40, keyH = 60, spacing = 10;
  int startY = 520;  // starting y position for the keyboard area
  for (int row = 0; row < keyboardRows.length; row++) {
    String keyRow = keyboardRows[row];
    int rowLength = keyRow.length();
    int totalRowWidth = rowLength * keyW + (rowLength - 1) * spacing;
    int startX = (width - totalRowWidth) / 2;
    int y = startY + row * (keyH + spacing);
    for (int i = 0; i < rowLength; i++) {
      char letter = keyRow.charAt(i);
      int x = startX + i * (keyW + spacing);
      keys.add(new Key(letter, x, y, keyW, keyH));
    }
  }
  dailyButton = new Button(100, 800, 200, 50, "Daily");
  randomButton = new Button(300, 800, 200, 50, "Random");
  textSize(50);
  text("Press Tab to reset", 110, 775);
  
}

void draw() {
  dailyButton.display();
  randomButton.display();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      b[i][j].display();
    }
  }
  
  test = "";
  for (int j = 0; j < cols; j++) {
    test += b[curRow][j].l.q;
  }
  
  for (Key k : keys) {
    k.display();
  }
  
}

void fetchDailyWordle() {
    String yyyy = nf(year(), 4);
    String mm = nf(month(), 2);
    String dd = nf(day(), 2);
    String dateStr = yyyy + "-" + mm + "-" + dd;

    // per date
    String url = "https://www.nytimes.com/svc/wordle/v2/" + dateStr + ".json";

    JSONObject obj = loadJSONObject(url);
    String solution = obj.getString("solution");

    dailyword = solution.toUpperCase();
    println(dailyword);
    ans = dailyword;
}

void boxPos() {
  for (int i = 0; i < rows; i++) {
    int y = i * BOX_HEIGHT;
    for (int j = 0; j < cols; j++) {
      b[i][j] = new Box(j * BOX_WIDTH, y, BOX_WIDTH, BOX_HEIGHT);
    }
  }
}

void resetGame() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      b[i][j].empty = true;
      b[i][j].inpos = false;
      b[i][j].inword = false;
      b[i][j].checked = false;
    }
  }
  curRow = 0;
  curCol = 0;
  if (daily){
    thread("fetchDailyWordle");
    //ans = dailyword;
  }
  else {
    int r = int(random(answers.length));
    ans = answers[r];
  }
  gameOver = false;
  for (Key k : keys) {
    k.state = DEFAULT;
  }
}

void keyPressed() {
  if (key == BACKSPACE) {
    if (curCol >= 1) {
      curCol--;
      b[curRow][curCol].eraseletter();
    }
  }
  if (key == TAB) {
    resetGame();
  }
  if (gameOver) {
    println(ans);
    //return; 
  }
  // case insensitive
  if ((key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z') && !gameOver) {
    if (curCol < cols && curRow < rows) {
      b[curRow][curCol].empty = false;
      b[curRow][curCol].l = new Letter(key);
      curCol++;
      //println(curCol);
    }
  }
  if (key == ENTER || key == RETURN) {
    // Only process the guess if the row is complete
    if (curCol == cols) {
      checkifword();
      if (ifword) {
        checkmatch();
        if (curRow < rows - 1) {
          curRow++;
        }
        if (curRow == rows-1){
          rcount ++;
          println(curRow);
          if (rcount ==2 && !test.equalsIgnoreCase(ans)){ 
              gameOver = true;
              println(ans);
          }
        }
        curCol = 0;
      }
    }
  }
}

void mousePressed() {
  if (dailyButton.isClicked(mouseX, mouseY)) {
    println("Daily mode selected");
    daily = true;
    resetGame();
  }
  if (randomButton.isClicked(mouseX, mouseY)) {
    println("Random mode selected");
    daily = false;
    resetGame();
  }
}

void checkifword() {
  //println(test);
  ifword = false;
  // Check if the current guess is in the guess list
  for (int i = 0; i < guess.length; i++) {
    if (guess[i].equalsIgnoreCase(test)) {
      ifword = true;
      break;
    }
  }
  //println("Answer: " + ans);
}

void checkmatch() {
  for (int i = 0; i < cols; i++) {
    char guessed = Character.toUpperCase(test.charAt(i));
    if (guessed == Character.toUpperCase(ans.charAt(i))) {
      b[curRow][i].inpos = true;     // Box shows green (handled in its display)
      updateKeyColor(guessed, GREEN);
    } else if (checkpos(guessed)) {
      b[curRow][i].inword = true;    // Box shows yellow (handled in its display)
      updateKeyColor(guessed, YELLOW);
    } else {
      updateKeyColor(guessed, GRAY);
    }
    b[curRow][i].checked = true;
  }
  if (test.equalsIgnoreCase(ans)) {
    gameOver = true;
    println(ans);
  }
}

//  true if character t is found anywhere in the answer
boolean checkpos(char t) {
  for (int i = 0; i < ans.length(); i++) {
    if (Character.toUpperCase(t) == Character.toUpperCase(ans.charAt(i))) {
      return true;
    }
  }
  return false;
}

void updateKeyColor(char letter, int newState) {
  letter = Character.toUpperCase(letter);
  for (Key k : keys) {
    if (k.letter == letter) {
      if (newState > k.state) {
        k.state = newState;
      }
      break;
    }
  }
}
