#ifndef ALLIANCE_H
#define ALLIANCE_H

#include <QList>
#include <QWeakPointer>
class CPlayer;

class CAlliance
{
	public:
		CAlliance(){}

		typedef QWeakPointer<CPlayer> TWeakPtrPlayer;
		QString m_allianceName;
		QList<TWeakPtrPlayer> m_players;

};


#endif // ALLIANCE_H
