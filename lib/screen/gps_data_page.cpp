#include "gps_data_page.h"

GpsDataPage::GpsDataPage(std::shared_ptr<sensor::Gps> gps)
  : gps_(gps)
{}

void GpsDataPage::DrawPage(std::shared_ptr<OledScreen> screen)
{
  unsigned short y_pos = OledScreen::normal_font_ascent_;
  sensor::NavPvt pvt = gps_->GetNavPvt();
  screen->Clear();
  screen->PrintLine(&y_pos, "lat: %d", pvt.lat);
  screen->PrintLine(&y_pos, "lon: %d", pvt.lon);
  screen->PrintLine(&y_pos, "sats: %d", pvt.num_sv);
  screen->PrintLine(&y_pos, "time: %d:%d:%d", pvt.hour, pvt.minute, pvt.second);
  screen->Render();
}
