
void tick1()
{
  gv_ticked1 = true;
}

void init_ticker_count() {
  ticker1.attach(1, tick1);
  gv_ticked1 = false;
}


void check_ticker_count() {

  if (!gv_ticked1) {
    return;
  }

  if (gv_counter < 59) {
    gv_counter++;
  } else {
    gv_counter = 0;
  }

  gv_ticked1 = false;
}
