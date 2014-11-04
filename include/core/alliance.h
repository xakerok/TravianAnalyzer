#ifndef ALLIANCE_H
#define ALLIANCE_H

#include <QList>
#include "player.h"


class CAlliance
{
public:
    CAlliance(){}

    typedef QWeakPointer<CPlayer> TWeakPtrPlayer;

    QString m_allianceName;

    QList<TWeakPtrPlayer> m_players;

};


#endif // ALLIANCE_H
