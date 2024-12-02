#include "displayer.h"

sm::Displayer::Displayer(std::unique_ptr<sm::Scheduler> scheduler,
                     IDataPage& data_page)
  : data_page_(data_page),
    scheduler_(std::move(scheduler)),
    screen_(std::make_shared<sm::OledScreen>())
{}

void sm::Displayer::InitAndSplash(const char * splash_text)
{
  screen_->Init(splash_text);
}

void sm::Displayer::ScheduledRun()
{
  if (scheduler_->ShouldRun())
  {
    data_page_.DrawPage(screen_);
  }
}

void sm::Displayer::SetDataPage(sm::IDataPage& data_page)
{
  data_page_ = data_page;
}

void sm::Displayer::Start()
{
  scheduler_->Start();
}
