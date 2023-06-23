#include <iostream>

namespace geo2d{

    using Point = std::pair<int, int>;
    namespace orto{

        class Quad {
        public:
            virtual void scale(int alpha) = 0;
        };

        class Rect : Quad {
        public:
            Rect(const Point& lt_, int width_, int hight_) : lt(lt_), width(width_), hight(hight_) {}
            Rect(const Square& sqr) {
                width = sqr.side;
                hight = sqr.side;
            }
            bool isSquare() {
                return width == hight;
            }
            void scale(int alpha) override {
                width *= alpha;
                hight *= alpha;
            }
            Point lt{ 0, 0 };
            int width = 0;
            int hight = 0;
        };

        class Square : Quad {
        public:
            Square(Point lt_, int side_) : lt(lt_), side(side_) {}
            Square(const Rect& rec) {
                if (rec.hight == rec.width) {
                    side = rec.hight;
                    lt = rec.lt;
                }
                else {
                    throw std::exception("cannot be casted");
                }
            }
            void scale(int alpha) override {
                side *= alpha;
            }
            Point lt{ 0, 0 };
            int side = 0;
        };

        Rect Union(const Rect& lhs, const Rect& rhs) {
            int t1 = lhs.lt.second;
            int t2 = rhs.lt.second;
            int tmax = std::max(t1, t2);
            int b1 = lhs.lt.second + lhs.hight;
            int b2 = rhs.lt.second + rhs.hight;
            int bmin = std::min(b1, b2);
            int l1 = lhs.lt.first;
            int l2 = rhs.lt.first;
            int lmin = std::min(l1, l2);
            int r1 = lhs.lt.first + lhs.width;
            int r2 = rhs.lt.first + rhs.width;
            int rmax = std::max(r1, r2);
            return Rect(Point(tmax, lmin), rmax - lmin, bmin - tmax);
        }

        Rect Intersect(const Rect& lhs, const Rect& rhs) {

        }
    }

    int main() {
        geo2d::orto::Square a{ geo2d::Point{ 1, 2 }, 2 };
        geo2d::orto::Rect b = a;
        return 0;
    }
}