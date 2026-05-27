#ifndef DAGGERSPRAY_H
#define DAGGERSPRAY_H
#include "Card.h"
class DaggerSpray : public Card {
public:
    DaggerSpray();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new DaggerSpray(*this); }
    static const int DAMAGE = 4;
    static const int HITS   = 2;
};
#endif
