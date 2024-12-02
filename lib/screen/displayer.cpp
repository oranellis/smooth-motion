#include "displayer.h"

sm::Displayer::Displayer(IDataPage &data_page)
    : data_page_(data_page),
      screen_(std::make_shared<sm::OledScreen>())
{
}

void sm::Displayer::InitAndSplash(const char *splash_text)
{
  screen_->Init(splash_text);
}

void sm::Displayer::Display()
{
  data_page_.DrawPage(screen_);
}

void sm::Displayer::SetDataPage(sm::IDataPage &data_page)
{
  data_page_ = data_page;
}