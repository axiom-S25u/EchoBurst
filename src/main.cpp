#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>

using namespace geode::prelude;

class $modify(MyDeathTroll, PlayLayer) {
    struct Fields {
        int m_sessionDeaths = 0;
    };

    void resetLevel() {
        PlayLayer::resetLevel();
        
        m_fields->m_sessionDeaths++;
        
        float percent = this->getCurrentPercent();
        std::string soundToPlay = "";

        if (percent <= 10.0f) {
            int r = utils::random::generate<int>(0, 3);
            if (r == 0) soundToPlay = "bruh.mp3";
            else if (r == 1) soundToPlay = "oof.mp3";
            else soundToPlay = "disconnect.mp3";
        } 
        else if (percent > 10.0f && percent <= 70.0f) {
            int r = utils::random::generate<int>(0, 2);
            if (r == 0) soundToPlay = "fart.mp3";
            else soundToPlay = "wth.mp3";
        }
        else if (percent > 70.0f && percent <= 94.0f) {
            soundToPlay = "violin.mp3";
        }
        else if (percent >= 95.0f) {
            soundToPlay = "metalpipe.mp3";
            FMODAudioEngine::sharedEngine()->playEffect("xpshutdown.mp3");
            
            std::string msg = "death #" + std::to_string(m_fields->m_sessionDeaths) + " - seek help.";
            Notification::create(msg, NotificationIcon::Error)->show();
            
            utils::web::openLinkInBrowser("https://www.wikihow.com/Control-Anger");
        }

        if (!soundToPlay.empty()) {
            FMODAudioEngine::sharedEngine()->playEffect(soundToPlay);
        }
    }
};
// meow meow meow meow meow meow meow meow