#include "displayer.h"

sm::Displayer::Displayer()
    : data_page_(nullptr), screen_(std::make_shared<sm::OledScreen>()) {}

void sm::Displayer::InitAndSplash(const char *splash_text) {
  screen_->Init(splash_text);
}

void sm::Displayer::Display() {
  if (data_page_) {
    data_page_->DrawPage(screen_);
  } else {
    screen_->Clear();
    unsigned short y_pos = OledScreen::normal_font_ascent_;
    screen_->PrintLine(&y_pos, (char *)"No data page");
    screen_->Render();
  }
}

void sm::Displayer::SetDataPage(sm::IDataPage &data_page) {
  data_page_ = &data_page;
}
