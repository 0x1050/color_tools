#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

struct Color {
    private:
        std::string name;
        std::string hex;
        int r,g,b,h,s,l;
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
            //convert RGB to temporary values, range 0-1
            //round to 2 decimal places
            float rt = 1.0*r/255;
            float gt = 1.0*g/255;
            float bt = 1.0*b/255;

            //Get min/max
            double ma = fmax(fmax(rt,gt),bt);
            double mi = fmin(fmin(rt,gt),bt);

            double chroma = ma-mi;

            if ( chroma == 0) // No saturation?
                h = s = 0;
            else {
                if (l <= .5)
                    s = chroma/(ma+mi);
                else
                    s = chroma/(2-ma-mi);

                if (ma == rt)
                    h = (gt-bt)/chroma + 2;
                else if (ma == gt)
                    h = (rt-gt)/chroma+2;
                else
                    h = (rt-gt)/chroma+4;

                h /= 6;
            }
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
