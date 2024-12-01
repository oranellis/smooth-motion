#pragma once

#include "data_page.h"
#include "scheduler.h"
#include "screen.h"

#include <memory>

class Displayer
{
  private:
  IDataPage& data_page_;
  std::unique_ptr<Scheduler> scheduler_;
  std::shared_ptr<OledScreen> screen_;

  public:
  Displayer(std::unique_ptr<Scheduler> scheduler, IDataPage& data_page);
  void InitAndSplash(const char * splash_text);
  void ScheduledRun();
  void SetDataPage(IDataPage& data_page);
  void Start();
};