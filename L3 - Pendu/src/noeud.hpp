#ifndef NOEUD_HPP
#define NOEUD_HPP

class Noeud {
public:
    bool terminal;
    Noeud* fils[27];

    Noeud() {
        terminal = false;
        for (int i = 0; i < 27; i++)
            fils[i] = nullptr;
    }
};

#endif // NOEUD_HPP
