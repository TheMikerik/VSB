#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cstdlib>
#include <cmath> 

using namespace std;

/**
 * Reprezentace pojmenovaneho bodu v rovine
 */
struct Point {
    int x; ///< x-ova souradnice
    int y; ///< y-ova souradnice
    string name; ///< Nazev
};


/**
 * Operator porovnani dvou bodu
 * 
 * @param lhs Jeden z porovnavanych bodu
 * @param rhs Druhy z porovnavanych bodu
 * @retval true Pokud se body shoduji na x-ove i y-ove souradnici
 * @retval false Pokud jeden z bodu ma aspon jednu souradnici jinou nez druhy bod
 */
inline bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x &&
        lhs.y == rhs.y;
}


/**
 * Rozdil dvou bodu (lze pouzit pro vypocet vektoru v rovine)
 * 
 * @param lhs Bod, o nehoz je odecitano
 * @param rhs Bod, ktery je odecitan
 * @return Bod, jehoz x-ova souradnice je rozdilem x-ovych souradnic danych bodu a
 *         y-ova souradnice je rozdilem y-ovych souradnic danych bodu. Jmeno tohoto
 *         bodu neni nastaveno. 
 */
Point operator-(const Point& lhs, const Point& rhs)
{
    Point ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    return ret;
}


/**
 * Porovnani dvou bodu. Za mensi je povazovan ten s mensi x-ovou souradnici.
 * Je-li x-ova souradnice stejna, je mensi ten s mensi y-ovou souradnici.
 * 
 * @param a Jeden z porovnavanych bodu
 * @param b Druhy z porovnavanych bodu
 * @retval true Pokud je bod a mensi nez bod b
 * @retval false Pokud je bod a vetsi nebo roven bodu b
 */
bool compare(Point a, Point b) {
    if (a.x == b.x) return (a.y < b.y);
    return (a.x < b.x);
}


/**
 * Funkce pocitajici vzdalenost dvou bodu v rovine
 *
 * @param a Jeden z bodu, jejichz vzdalenost se pocita
 * @param b Druhy z bodu, jejichz vzdalenost se pocita
 * @return Vzdalenost mezi body a,b
 */
double dist2(Point a, Point b) {
    double dist = pow(a.x - b.x, 2) + pow (a.y - b.y, 2);
    dist = sqrt(dist);

    return dist;
}



/**
 * Funkce pocitajici determinant matice
 * | a.x a.y 1 |
 * | b.x b.y 1 |
 * | c.x c.y 1 |
 * Absolutni hodnota determinantu je dvojnasobkem obsahu trojuhelnika a,b,c.
 * Kladna hodnota determinantu znamena, ze bod c lezi nalevo od vektoru ab.
 * Zaporna hodnota determinantu znamena, ze bod c lezi napravo od vektoru ab. 
 * Determinant bude 0, lezi-li bod c na primce spojujici body a,b.
 *
 * @param a Souradnice bodu a
 * @param b Souradnice bodu b
 * @param c Souradnice bodu c
 * @return Determinant trojuhelnika a,b,c.
 */
int det(Point a, Point b, Point c) {
  //V případě použití doplnit kód
    return a.x*b.y + c.x*a.y + b.x*c.y - c.x*b.y - b.x*a.y - a.x*c.y;
}



/**
 * Funkce pocitajici vzdalenost bodu c od primky prochazejici body a,b.
 * 
 * @param a Souradnice bodu a
 * @param b Souradnice bodu b
 * @param c Souradnice bodu c
 * @return Vzdalenost bodu c od primky spojujici body a,b
 */
double dist3(Point a, Point b, Point c) {
    double distance = det(a, b, c) / dist2(a, b);

    if (distance < 0){
        distance *= -1;
    }
    
    return distance;
}


/**
 * Nacteni vstupniho souboru se souradnicemi bodu do vektoru polozek 
 * reprezentovanych strukturami Point. Kazdy bod ma krome dvou celociselnych
 * souradnic x a y jeste jednoslovny nazev. 
 * V souboru se ceka kazda bod na samostatnem radku, nejprve je souradnice x,
 * dale mezerou oddelena souradnice y a dalsi mezerou je oddeleno jmeno bodu.
 *
 * @param name Jmeno souboru, ze ktereho se polozky budou nacitat
 * @return Vektor vsech bodu nactenych ze souboru
 */
vector<Point> readItems(string fileName) {
    ifstream infile; 
    infile.open(fileName); 
    
    if(!infile.is_open()){
        cerr << "File could not be opened" << endl;
        exit(-1);
    }
    
    vector<Point> points;
    Point p;

    while (!infile.eof()) {
        infile >> p.x >> p.y >> p.name;
        points.push_back(p);
    }
    infile.close();
    sort(points.begin(), points.end(), compare);
    return points;
}


/*
FindHull(S, P, Q)
    ConvexHull := {}
    Pokud S = {}
        Vrať {}
    C := Bod z S, který je nejvzdálenější od přímky spojující body P,Q
    Přidej C do ConvexHull
    S1 := Body ležící vlevo od vektoru z P do C
    S2 := Body ležící vlevo od vektoru z C do Q
    Přidej do ConvexHull vše vrácené z FindHull(S1, P, C) 
    Přidej do ConvexHull vše vrácené z FindHull(S2, C, Q) 
    Vrať ConvexHull
*/
vector<Point> Findhull(vector<Point> points, Point A, Point B){
    vector<Point> convexHull;

    if (points.empty()) {
        return convexHull;
    }

    double maxDist = -1;
    Point C;

    for (vector<Point>::size_type i=0; i<points.size(); i++){
        double dist = dist3(A, B, points[i]);
        if (dist > maxDist){
            maxDist = dist;
            C = points[i];
        }
    }

    vector<Point> pointsL;
    vector<Point> pointsR;

    for (vector<Point>::size_type i=0; i<points.size(); i++){
        int determinant = det(A, C, points[i]);
        if (determinant > 0) {
            pointsL.push_back(points[i]);
        } else {
            determinant = det(C, B, points[i]);
            if (determinant > 0) {
                pointsR.push_back(points[i]);
            }
        }
    }

    vector<Point> convLeft = Findhull(pointsL, A, C);
    vector<Point> convRight = Findhull(pointsR, C, B);

    convexHull.insert(convexHull.end(), convLeft.begin(), convLeft.end());
    convexHull.insert(convexHull.end(), convRight.begin(), convRight.end());
    convexHull.push_back(C);

    return convexHull;
}



/**
 * Funkce hledajici konvexni obal mnoziny bodu (na vstup predavane formou vektoru).
 *
 * @param points Vektor bodu, jejichz konvexni obal hledame. Predpoklada se, ze funkce
 *               bude volana jen s vektory, kde budou body v poradi podle rostouci
 *               souradnice x. V pripade shody na souradnici x budou drive body s nizsi
 *               souradnici y. Body se stejnymi obema souradnicemi se ve vektoru nebudou
 *               vyskytovat.
 * @return Vektor bodu tvoricich konvexni obal zadane mnoziny bodu. V tomto vektoru mohou
 *         byt body v libovolnem poradi.
 */
/*
    QuickHull(S) 
    ConvexHull := {} 
    A := nejlevější bod z S
    B := nejpravější bod z S
    Přidej A,B do ConvexHull
    S1 := body z S ležící vlevo od přímky spojující body A,B (vůči směru od A do B)
    S2 := body z S ležící vpravo od přímky spojující body A,B (vůči směru od A do B)
    Přidej do ConvexHull vše vrácené z FindHull(S1, A, B) 
    Přidej do ConvexHull vše vrácené z FindHull(S2, B, A) 
    Vrať ConvexHull
*/
vector<Point> QuickHull(vector<Point> points) {
    vector<Point> convexHull;

    Point leftmost = points[0];
    Point rightmost = points[points.size()-1];
    convexHull.push_back(leftmost);
    convexHull.push_back(rightmost);

    vector<Point> pointsL;
    vector<Point> pointsR;
    for (vector<Point>::size_type i=0; i<points.size(); i++){
        int determinant = det(leftmost, rightmost, points[i]);
        if (determinant > 0) {
            pointsL.push_back(points[i]);
        } else if (determinant < 0) {
            pointsR.push_back(points[i]);
        }
    }

    vector<Point> convLeft = Findhull(pointsL, leftmost, rightmost);
    vector<Point> convRight = Findhull(pointsR, rightmost, leftmost);

    convexHull.insert(convexHull.end(), convLeft.begin(), convLeft.end());
    convexHull.insert(convexHull.end(), convRight.begin(), convRight.end());
    
    return convexHull;
}


int main(int argc, char** argv)
{
    
    if(argc < 2){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }

    vector<Point> points; 

    points = readItems(argv[1]);
    points = QuickHull(points);
    sort(points.begin(), points.end(), compare);
    int last = points.size()-1;
    for (int i = 0; i<=last; i++) {
        cout << points[i].name << ((i==last)?"":", ");
    }
    cout << endl;
}