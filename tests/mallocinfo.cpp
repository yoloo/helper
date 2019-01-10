#include <malloc.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

std::string bytes2M(long bytes) {
    float div = 1.0f * bytes / (1024 * 1024);

    std::ostringstream oss;
    oss << div << " M";

    return oss.str();
}

#define CALC_MEMORY_BEFORE(varname) \
struct mallinfo before##varname##info; \
before##varname##info = mallinfo(); \

#define CALC_MEMORY_AFTER(varname) \
struct mallinfo after##varname##info; \
after##varname##info = mallinfo(); \
std::cout << #varname << " used memory:" << /*bytes2M(*/after##varname##info.uordblks - before##varname##info.uordblks/*)*/ << std::endl; \


void display(std::string op) {
    struct mallinfo mi;
    mi = mallinfo();

    std::cout << "=====================================" << op << "=====================================\n";

    std::cout << "Total non-mmapped bytes (arena):"       << mi.arena    << std::endl;
    std::cout << "# of free chunks (ordblks):"            << mi.ordblks  << std::endl;
    std::cout << "# of free fastbin blocks (smblks):"     << mi.smblks   << std::endl;
    std::cout << "# of free mapped regions (hblks):"      << mi.hblks    << std::endl;
    std::cout << "Bytes in mapped regions (hblkhd):"      << mi.hblkhd   << std::endl;
    std::cout << "Free bytes held in fastbins (fsmblks):" << mi.fsmblks  << std::endl;
    std::cout << "Total allocated space (uordblks):"      << mi.uordblks << std::endl;
    std::cout << "Total free space (fordblks):"           << mi.fordblks << std::endl;
    std::cout << "Topmost releaseable block (keepcost):"  << mi.keepcost << std::endl;

    std::cout << "=====================================" << "states" << "=====================================\n";
    malloc_stats();
    std::cout << std::endl;
}

int main() {
    display("test");

    CALC_MEMORY_BEFORE(list)

    std::vector<size_t*> list;
    for (size_t i = 0; i < 1000000; ++i)
        list.push_back(new size_t(100));

    CALC_MEMORY_AFTER(list);

    return 0;
}