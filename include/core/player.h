#ifndef PLAYER_H
#define PLAYER_H

#include <QWeakPointer>

#include <QMap>
#include "village.h"

class CAlliance;


class CPlayer
{
public:
   CPlayer(){}
   typedef QWeakPointer<CAlliance> TWeakPtrAlliace;
   typedef QWeakPointer<CVillage> TWeakPtrVillage;


   TWeakPtrAlliace m_alliance;
   QString m_playerName;
   QString m_playerTribe;
   QMap< unsigned long, TWeakPtrVillage > m_villages;

private:
   Q_DISABLE_COPY(CPlayer)

};

#endif // PLAYER_H
