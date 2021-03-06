#include <chrono>
#include <iomanip>
#include <ctime>
#include <vector>
#include <mutex>
#include <string>
#include <ostream>

class Logger {
  private:
    std::stringstream messages;
    std::mutex mutex;
    std::ostream& out;

  public:
    Logger(std::ostream& o) : out(o) { };
    ~Logger(void) { };

    bool verbose = false;

    void log(std::string msg) {
        std::lock_guard<std::mutex> lock(mutex);

        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        auto timestr = std::put_time(std::localtime(&now_c), "%T");

        messages << '[' << timestr << "] " << msg << '\n';

        if(verbose)
            out << '[' << timestr << "] " << msg << std::endl;

    };

    void dump(std::ostream& o) {
        o << messages.str() << std::flush;
    };
};
