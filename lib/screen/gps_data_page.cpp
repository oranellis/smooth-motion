#include "gps_data_page.h"

sm::GpsDataPage::GpsDataPage(std::shared_ptr<sm::sensor::Gps> gps)
  : gps_(gps)
{}

void sm::GpsDataPage::DrawPage(std::shared_ptr<sm::OledScreen> screen)
{
  unsigned short y_pos = sm::OledScreen::normal_font_ascent_;
  sm::sensor::NavPvt pvt = gps_->GetNavPvt();
  screen->Clear();
  screen->PrintLine(&y_pos, "lat: %d", pvt.lat);
  screen->PrintLine(&y_pos, "lon: %d", pvt.lon);
  screen->PrintLine(&y_pos, "sats: %d", pvt.num_sv);
  screen->PrintLine(&y_pos, "time: %d:%d:%d", pvt.hour, pvt.minute, pvt.second);
  screen->Render();
}
