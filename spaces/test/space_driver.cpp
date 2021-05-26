#include "../lib/spaces.h"
#include <vector>


int main(int ac, char ** av) {
    std::string line;
    std::vector<Color> colors;
    int count = 0;

    while(getline(std::cin, line)) {
        Color *c = new Color(line);
        c->hex2rgb();
        c->rgb2hsl();
        colors.push_back(*c);
        count++;
    }

    std::cout << "[\n";
    if (colors.size() == 1)
        std::cout << colors[0].jsonify();
    else {
        for (int i=0; i<count;i++) {
            std::cout << colors[i].jsonify();
            if (i == count-2)
                break;
            std::cout << ",";
            std::cout << std::endl;
        }
    }
    std::cout << "\n]\n";
    return 0;
}

