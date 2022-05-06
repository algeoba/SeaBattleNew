#include <iostream>
#include <unistd.h>
using namespace std;

const int s = 10;
int s_1 = s - 1;
string b1o[s][s]; // own board of 1st player
string b1f[s][s]; // foe's board restored by 1st player
string b2o[s][s];
string b2f[s][s];
string brdr = string(3, ' ') + string(s * 4 + 1, '-') + string(5, ' ') +
              string(s * 4 + 1, '-') + "\n";
string ship_cell = "[+]", margin_cell = " - ", wreck_cell = "[ ]",
       blank_cell = "   ";
int x, y, a, t, dir, n, i, c, j, k, m, f = 200;
string abc[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
int timeStart, timeEnd, delta;
string info = "";
// (X)
void b_populate(string b[s][s]) {
  for (y = 0; y < s; y++) {
    for (x = 0; x < s; x++) {
      b[x][y] = blank_cell;
    }
  }
}

string timeSpan() {
  delta = timeEnd - timeStart;
  return to_string(delta / 60) + " min " + to_string(delta % 60) + " sec";
}

void b_display(string b1[s][s], string b2[s][s]) {
  cout << endl;
  // timeEnd = time(NULL);
  // system("clear");
  cout << string(3, ' ');
  for (t = 0; t < s; t++)
    cout << "  " + abc[t] + " ";
  cout << string(6, ' ');
  for (t = 0; t < s; t++)
    cout << "  " + abc[t] + " ";
  cout << endl;
  cout << brdr;
  for (y = 0; y < s; y++) {
    if (y < 9)
      cout << " ";
    cout << y + 1 << " |";
    for (x = 0; x < s; x++) {
      //(b1[x][y] == margin_cell) ? cout << blank_cell :
      cout << b1[x][y] << "|";
    }
    cout << "  ";
    if (y < 9)
      cout << " ";
    cout << y + 1 << " |";
    for (x = 0; x < s; x++) {
      //(b2[x][y] == margin_cell) ? cout << blank_cell :
      cout << b2[x][y] << "|";
    }
    (y < s - 1) ? cout << endl << brdr : cout << endl;
  }
  cout << brdr << endl;
  cout << endl << info << endl;
  // cout << timeSpan() << endl;
}

void margin_cells_mark(string b[s][s]) {
  if (x > 0)
    b[x - 1][y] = margin_cell;
  if (x < s_1)
    b[x + 1][y] = margin_cell;
  if (y > 0)
    b[x][y - 1] = margin_cell;
  if (y < s_1)
    b[x][y + 1] = margin_cell;
  if (x > 0 && y > 0)
    b[x - 1][y - 1] = margin_cell;
  if (x > 0 && y < s_1)
    b[x - 1][y + 1] = margin_cell;
  if (x < s_1 && y > 0)
    b[x + 1][y - 1] = margin_cell;
  if (x < s_1 && y < s_1)
    b[x + 1][y + 1] = margin_cell;
}

void b_update(string b[s][s], int z) {
  //  srand(time(NULL));
  // sleep(1);
  x = rand() % (s - z);
  y = rand() % (s - z);
  dir = rand() % 2;
  if (b[x][y] == blank_cell) {
    if (z == 1) {
      b[x][y] = ship_cell;
      margin_cells_mark(b);
    } else if (dir == 0) {
      c = 1;
      for (i = 1; i < z; i++)
        (b[x + i][y] == blank_cell) ? c = 1 : c = 0;
      if (c == 1) {
        b[x][y] = ship_cell;
        margin_cells_mark(b);
        for (n = 1; n < z; n++) {
          b[x + n][y] = ship_cell;
          if (x < s_1)
            b[x + 1 + n][y] = margin_cell;
          if (x < s_1 && y > 0)
            b[x + 1 + n][y - 1] = margin_cell;
          if (x < s_1 && y < s_1)
            b[x + 1 + n][y + 1] = margin_cell;
        }
      } else
        b_update(b, z);
    } else {
      c = 1;
      for (i = 1; i < z; i++)
        (b[x][y + i] == blank_cell) ? c = 1 : c = 0;
      if (c == 1) {
        b[x][y] = ship_cell;
        margin_cells_mark(b);
        for (n = 1; n < z; n++) {
          b[x][y + n] = ship_cell;
          if (y < s_1)
            b[x][y + n + 1] = margin_cell;
          if (x > 0 && y < s_1)
            b[x - 1][y + n + 1] = margin_cell;
          if (x < s_1 && y < s_1)
            b[x + 1][y + n + 1] = margin_cell;
        }
      } else
        b_update(b, z);
    }
  } else
    b_update(b, z);
}

void b_prepare(string b[s][s]) {
  j = 4;
  k = 1;
  while (j > 0) {
    if (j == 4)
      k = 1;
    else if (j == 3)
      k = 2;
    else if (j == 2)
      k = 3;
    else if (j == 1)
      k = 4;
    for (m = 0; m < k; m++) {
      b_update(b, j);
      // b_display();
    }
    j--;
  }
  for (y = 0; y < s; y++) {
    for (x = 0; x < s; x++) {
      if (b[x][y] == margin_cell)
        b[x][y] = blank_cell;
    }
  }
}

void b_hit(string bf[s][s], string bo[s][s]) {
  x = rand() % s;
  y = rand() % s;
  if (bf[x][y] == blank_cell) {
    (bo[x][y] == blank_cell) ? bf[x][y] = margin_cell : bf[x][y] = wreck_cell;
  } else {
    b_hit(bf, bo);
  }
}

void b_hit_plus(string b[s][s]) {
  x = rand() % s;
  y = rand() % s;
  if (b[x][y] == blank_cell) {
    b[x][y] = margin_cell;
    info = "fluff...";
  } else if (b[x][y] == ship_cell) {
    b[x][y] = wreck_cell;
    info = "BOOM!";
  } else {
    b_hit_plus(b);
  }
}

int main() {
  // cout << endl;
  srand(time(NULL));
  b_populate(b1o);
  b_populate(b2o);
  // b_populate(b1f);
  // b_populate(b2f);
  timeStart = time(NULL);
  b_prepare(b1o);
  b_prepare(b2o);
  system("clear");
  b_display(b1o, b1f);
  // b_display(b2o, b2f);
  sleep(1);
  // sleep(1);
  while (f) {

    sleep(1);
    //  (f % 2 == 0) ? b_hit(b1f,b2o) : b_hit(b2f,b1o);
    (f % 2 == 0) ? b_hit_plus(b1o) : b_hit_plus(b2o);
    system("clear");
    b_display(b1o, b2o);
    // b_display(b1o, b1f);
    //   b_display(b2o, b2f);
    f--;
    //
  }
  cout << endl;
}