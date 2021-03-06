/* F4 */
void bezier() {
  while (!back == 1) {
    if (show_adjust == 0) {
      display.clearDisplay();
      display.display();

      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0, 0);
      display.println("Set Variables");
      display.print("   A: F1 "); display.println(bezier_A, 3);
      display.print("   B: F2 "); display.println(bezier_B, 3);
      display.print("   C: F3 "); display.println(bezier_C, 3);
      display.print("   D: F4 "); display.println(bezier_D, 3);
      display.display();
      show_adjust = 1;
    }

    if ( char key = KP2.Getkey() ) {
      if (KP2.Key_State() == PRESSED) {
        switch (key) {
          case '0':
            show_adjust = 0;
            back = !back;
            break;
          case 'B':
            adjust_B();
            show_adjust = 0;
            break;
          case 'A':
            adjust_A();
            show_adjust = 0;
            break;
          case 'C':
            adjust_C();
            show_adjust = 0;
            break;
          case 'D':
            adjust_D();
            show_adjust = 0;
            break;
        }
      }

    }
  }
  back = !back;
}

float DoubleQuadraticBezier (float x, float a, float b, float c, float d) {
  
  // functionName = "Double Quadratic Bezier";
  // also see http://engineeringtraining.tpub.com/14069/css/14069_150.htm
  // produces mysterious values when a=0,b=1,c=0.667,d=0.417

  float xmid = (a + c) / 2.0;
  float ymid = (b + d) / 2.0;
  xmid = constrain (xmid, EPSILON, 1.0 - EPSILON);
  ymid = constrain (ymid, EPSILON, 1.0 - EPSILON);

  float y = 0;
  float om2a;
  float t;
  float xx;
  float aa;
  float bb;

  if (x <= xmid) {
    xx = x / xmid;
    aa = a / xmid;
    bb = b / ymid;
    om2a = 1.0 - 2.0 * aa;
    if (om2a == 0) {
      om2a = EPSILON;
    }
    t = (sqrt(aa * aa + om2a * xx) - aa) / om2a;
    y = (1.0 - 2.0 * bb) * (t * t) + (2 * bb) * t;
    y *= ymid;
  }
  else {
    xx = (x - xmid) / (1.0 - xmid);
    aa = (c - xmid) / (1.0 - xmid);
    bb = (d - ymid) / (1.0 - ymid);
    om2a = 1.0 - 2.0 * aa;
    if (om2a == 0) {
      om2a = EPSILON;
    }
    t = (sqrt(aa * aa + om2a * xx) - aa) / om2a;
    y = (1.0 - 2.0 * bb) * (t * t) + (2 * bb) * t;
    y *= (1.0 - ymid);
    y += ymid;
  }

  return y;
}

void adjust_A() {
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Insert number");
  display.display();
  while (!back == 1) {

    if ( char key = KP2.Getkey() ) {
      if (KP2.Key_State() == PRESSED) {
        switch (key) {

          case 'Y':
            i = 0;
            back = !back;
            break;
          case '1':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '2':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '3':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '4':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '5':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '6':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '7':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '8':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '9':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '0':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
        }
      }

    }
  }
  bezier_A = atof(insert);
  bezier_A = bezier_A / 1000;
  EEPROM.put(DIR_BEZIER_A, bezier_A);
  for ( int i = 0; i < sizeof(insert);  ++i )
    insert[i] = (char)0;
  back = !back;
}

void adjust_B() {
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Insert number");
  display.display();
  while (!back == 1) {

    if ( char key = KP2.Getkey() ) {
      if (KP2.Key_State() == PRESSED) {
        switch (key) {

          case 'Y':
            i = 0;
            back = !back;
            break;
          case '1':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '2':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '3':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '4':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '5':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '6':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '7':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '8':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '9':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '0':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
        }
      }

    }
  }
  bezier_B = atof(insert) / 1000;
  EEPROM.put(DIR_BEZIER_B, bezier_B);
  for ( int i = 0; i < sizeof(insert);  ++i )
    insert[i] = (char)0;
  back = !back;
}

void adjust_C() {
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Insert number");
  display.display();
  while (!back == 1) {

    if ( char key = KP2.Getkey() ) {
      if (KP2.Key_State() == PRESSED) {
        switch (key) {

          case 'Y':
            i = 0;
            back = !back;
            break;
          case '1':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '2':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '3':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '4':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '5':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '6':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '7':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '8':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '9':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '0':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
        }
      }

    }
  }
  bezier_C = atof(insert) / 1000;
  EEPROM.put(DIR_BEZIER_C, bezier_C);
  for ( int i = 0; i < sizeof(insert);  ++i )
    insert[i] = (char)0;
  back = !back;
}

void adjust_D() {
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Insert number");
  display.display();
  while (!back == 1) {

    if ( char key = KP2.Getkey() ) {
      if (KP2.Key_State() == PRESSED) {
        switch (key) {

          case 'Y':
            i = 0;
            back = !back;
            break;
          case '1':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '2':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '3':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '4':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '5':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '6':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '7':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '8':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '9':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
          case '0':
            insert[i] = key;
            display.print(insert[i]);
            display.display();
            i++;
            break;
        }
      }

    }
  }
  bezier_D = atof(insert) / 1000.0;
  EEPROM.put(DIR_BEZIER_D, bezier_D);
  for ( int i = 0; i < sizeof(insert);  ++i )
    insert[i] = (char)0;
  back = !back;
}
