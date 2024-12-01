#include "displayer.h"

Displayer::Displayer(std::unique_ptr<Scheduler> scheduler,
                     IDataPage& data_page)
  : data_page_(data_page),
    scheduler_(std::move(scheduler)),
    screen_(std::make_shared<OledScreen>())
{}

void Displayer::InitAndSplash(const char * splash_text)
{
  screen_->Init(splash_text);
}

void Displayer::ScheduledRun()
{
  if (scheduler_->ShouldRun())
  {
    data_page_.DrawPage(screen_);
  }
}

void Displayer::SetDataPage(IDataPage& data_page)
{
  data_page_ = data_page;
}

void Displayer::Start()
{
  scheduler_->Start();
}
