#include "gps_data_page.h"

sm::GpsDataPage::GpsDataPage(std::shared_ptr<sm::sensor::NavPvt> nav_pvt)
    : nav_pvt_(nav_pvt) {}

void sm::GpsDataPage::DrawPage(std::shared_ptr<sm::OledScreen> screen) {
  unsigned short y_pos = sm::OledScreen::normal_font_ascent_;
  screen->Clear();
  screen->PrintLine(&y_pos, "lat: %d", nav_pvt_->lat);
  screen->PrintLine(&y_pos, "lon: %d", nav_pvt_->lon);
  screen->PrintLine(&y_pos, "sats: %d", nav_pvt_->num_sv);
  screen->PrintLine(&y_pos, "time: %d:%d:%d", nav_pvt_->hour, nav_pvt_->minute,
                    nav_pvt_->second);
  screen->Render();
}
