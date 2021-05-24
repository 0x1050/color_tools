#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

struct Color {
    private:
        std::string name;
        std::string hex;
        int r,g,b;
        double h,s,l;
    public:
        Color() {
            name = "Black";
            hex = "000000";
            r=g=b=h=s=l=0;
        }
        Color(std::string n, std::string h)  {
            name = n;
            hex = h;
        }
        std::string two_places(double d) {
            std::string s =std::to_string(d);
            int pos = s.find('.');
            std::string ret = "\"";
            if (s[pos+1] == '0')
                ret += s.substr(0,pos);
            else
                ret += s.substr(0,pos+2);
            ret += "\"";
            return ret;
        }

        std::string jsonify() {
            std::string ret = "\"" + name + "\": {\n";
            ret += "  \"Name\": \"" + name + "\",\n";
            ret += "  \"RGB\": [\""
                + std::to_string(r) + "\",\""
                + std::to_string(g) + "\",\""
                + std::to_string(b) + "\"],\n";
            ret += "  \"HSL\": [\""
                + std::to_string(int(h)) + "\","
                + two_places(s) + ","
                + two_places(l) + "],\n";
            ret += "  \"hex\": \"" + hex + "\"";
            ret += "}";
            std::cout << ret << std::endl;

            return ret;
        }

        void hex2rgb() {
            this->r = std::stoi(hex.substr(0,2),0,16);
            this->g = std::stoi(hex.substr(2,2),0,16);
            this->b = std::stoi(hex.substr(4,2),0,16);
        }

        void rgb2hsl() {
            double rtmp = 1.0*r/255;
            double gtmp = 1.0*g/255;
            double btmp = 1.0*b/255;

            double max = fmax(fmax(rtmp,gtmp),btmp);
            double min = fmin(fmin(rtmp,gtmp),btmp);
            double delta = max-min;

            double h;
            double s;
            double l = (min+max)/2;
            if (min == max) {// If the min=max, we have a shade of grey
                s = h = 0;
            }
            else {
                if (l <= 0.5)
                    s = delta/(max+min);
                else
                    s = delta/(2.0-max-min);

                double rdistance = (max-rtmp)/delta;
                double gdistance = (max-gtmp)/delta;
                double bdistance = (max-btmp)/delta;
                if (rtmp == max)
                    h = bdistance-gdistance;
                else if (gtmp == max)
                    h = 2.0 + rdistance-bdistance;
                else if (btmp == max)
                    h = 4.0 + gdistance-rdistance;

                h *= 60;
                if (h < 0)
                    h += 360;
                h = roundf(h);

            }
                this->h = h;
                this->s = s*100;
                this->l = l*100;
        }
        void printVals() {
            std::cout << "Name: " << name << std::endl;
            std::cout << "RGB: " << r << ' ' << g << ' ' << b << std::endl;
            std::cout << "HSL: " << h << ' ' << s << ' ' << l << std::endl;
        }
};

int main(int ac, char ** av) {
    std::ifstream in;
    in.open("dcolors");
    std::string line;
    std::ofstream out;
    std::vector<Color> colors;
    int count = 0;

    while(getline(in, line)) {
        int pos = line.find(' ');
        std::string name = line.substr(0,pos-1);
        std::string hex = line.substr(pos+1, line.length()-1);
        Color *c = new Color(name, hex);
        c->hex2rgb();
        c->rgb2hsl();
        colors.push_back(*c);
        count++;
    }

    out.open("colors.json");
    out << "{\n";
    for (int i=0; i<count;i++) {
        out << colors[i].jsonify();
        if (i == count-2)
            break;
        out << ",";
        out << std::endl;
    }
    out << "}\n";
    out.close();
    return 0;
}
