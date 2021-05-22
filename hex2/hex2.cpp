#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

struct Color {
    private:
        std::string name;
        std::string hex;
        int r,g,b, h,s,l;
    public:
        Color() {
            name = "Black";
            hex = "000000";
            r=g=b=h=s=l=0;
        }
        Color(std::string n, std::string h)  {
            name = n;
            hex = h;
            hex2rgb();
            rgb2hsl();
        }
        void print() {
            std::cout << name << std::endl;
            std::cout << "RGB: " << r << " " << g  << " " << b << std::endl;
            std::cout << "HSL: " << h << " " << s  << " " << l << std::endl;
            std::cout << "Hex: " << hex << std::endl;
            hex2rgb();
            rgb2hsl();
        }
        std::string html() {
            std::string ret= "<div style=\"background-color: ";
            ret+= name;
            ret+= "\"><h1>";
            ret+= name;
            ret+= "</h1></div>";

            ret+= "<div style=\"background-color: hsl(" + std::to_string(h) + ", " + std::to_string(s) + "%, " + std::to_string(l) + "%)\">";
            ret+= "<p>HSL: " + std::to_string(h) + ", " + std::to_string(s) + ", " + std::to_string(l) + "</div>";

            ret+= "<div style=\"background-color: rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")\">";
            ret+= "<p>RGB: " + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + "</p></div>";

            ret+= "<div style=\"background-color: #" + hex + "\">";
            ret+= "<p>Hex: " + hex + "</p></div>";

            return ret;
        }

        void hex2rgb() {
            r = std::stoi(hex.substr(0,2),0,16);
            g = std::stoi(hex.substr(2,2),0,16);
            b = std::stoi(hex.substr(4,2),0,16);
        }

        void rgb2hsl() {
            //Calculate temp values as double to make calculation easier
            //rgb -> range 0.0-1.0
            double rt = 1.0*r/255;
            double gt = 1.0*g/255;
            double bt = 1.0*b/255;

            double max = fmax(fmax(rt,gt),bt);
            double min = fmin(fmin(rt,gt),bt);
            double delta = max-min;

            double ht;
            double st;
            double lt = (min+max)/2;
            if (min == max) // If the min and max is 0, all values
                st = ht = 0;// are equal, and we have a shade of grey
            else {
                if (lt <= 0.5)
                    st = delta/(max+min);
                else
                    st = delta/(2.0-max-min);

                //Get distances
                double rd = (max-rt)/delta;
                double gd = (max-gt)/delta;
                double bd = (max-bt)/delta;
                if (rt == max)
                    ht = bd-gd;
                else if (gt == max)
                    ht = 2.0 + rd-bd;
                else if (bt == max)
                    ht = 4.0 + gd-rd;

                //Convert to degrees, align to circle
                ht *= 60;
                if (ht < 0)
                    ht += 360;
            }

            //Now we simply convert to decimal percentages
            h = round(ht);
            s = round(st*100);
            l = round(lt*100);
        }
};

int main(int ac, char ** av) {
    std::ifstream in;
    in.open("dcolors");
    std::string line;
    std::ofstream out;
    out.open("out.html");
    out << "<DOCTYPE html>"
           "<html><head><title>Colors, MotherFucker!</title>"
           "<style>*{padding:.5em;margin:0;font-family: sans-serif;}</style></head><body>";
    while(getline(in, line)) {
        int pos = line.find(' ');
        std::string name = line.substr(0,pos-1);
        std::string hex = line.substr(pos+1, line.length()-1);

        Color *c = new Color(name, hex);
        out << c->html() << std::endl;
    }
    out << "</body></html>";
    return 0;
}
