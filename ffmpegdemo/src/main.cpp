
#include "main.h"

using namespace std;


int main() {
    std::cout << "===============start============" << std::endl;
    av_log_set_level(AV_LOG_INFO);
    test_audio_resample();
    // test_video_resacle();
    std::cout << "=============== end ============" << std::endl;

    return 0;
}