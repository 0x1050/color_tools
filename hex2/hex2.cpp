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
            fromHex();
        }
        void print() {
            std::cout << name << std::endl;
            std::cout << "RGB: " << r << " " << g  << " " << b << std::endl;
            std::cout << "HSL: " << h << " " << s  << " " << l << std::endl;
            std::cout << "Hex: " << hex << std::endl;
            fromHex();
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
        void fromHex() {
            //get rgb
            r = std::stoi(hex.substr(0,2),0,16);
            g = std::stoi(hex.substr(2,2),0,16);
            b = std::stoi(hex.substr(4,2),0,16);
            //get hsl
            double rt = round((1.0*r)/255 * 100)/100;
            double gt = round((1.0*g)/255 * 100)/100;
            double bt = round((1.0*b)/255 * 100)/100;

            //Get min/max
            double ma;
            if (rt > gt && rt > bt)
                ma = rt;
            else if (gt > bt)
                ma = gt;
            else
                ma = bt;
            double mi;
            if (rt < gt && rt < bt)
                mi = rt;
            else if (gt < bt)
                mi = gt;
            else
                mi = bt;

            //Calculate luminance
            l = round((mi+ma)/2*100);

            //Calculate saturation
            if (mi == ma)
                s = 0;
            else { //Remember that luminance is a percentage
                if (l <= 50)
                    s = round((ma-mi)/(ma+mi)*100);
                else
                    s = round((ma-mi)/(2.0-ma-mi)*100);
            }

            //Calculate hue
            double ht;
            if (ma == rt)
                ht = (gt-bt)/(ma-mi);
            else if (ma == gt)
                ht = 2.0+(rt-gt)/(ma-mi);
            else
                ht = 4.0+(rt-gt)/(ma-mi);

            ht = round(ht*60);
            while (ht < 0) ht += 360;
            h = ht;
//            //******************************* temporary for debugging ***********/
//            std::string max;
//            if (rt == ma)
//                max = "red";
//            else if (bt == ma)
//                max = "blue";
//            else
//                max = "green";
//            std::string min;
//            if (rt == mi)
//                min = "red";
//            else if (bt == mi)
//                min = "blue";
//            else
//                min = "green";
//
//            std::cout << "max: " << max << " min: " << min << std::endl;
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
