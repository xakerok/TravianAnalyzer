#ifndef WORLD_H
#define WORLD_H

#include <QHash>
#include <QSharedPointer>
#include <QWeakPointer>

#include "player.h"
#include "alliance.h"

#include <QDateTime>

class CWorld
{
	public:
		CWorld( const QDateTime& time){m_time = time;}

		typedef QSharedPointer<CPlayer> TShPtrPlayer;
		typedef QSharedPointer<CAlliance> TShPtrAlliace;
		typedef QSharedPointer<CVillage> TShPtrVillage;

		typedef QSharedPointer< CWorld > TShPtrWorld;
		typedef QSharedPointer< const CWorld > TShPtrConstWorld;

		QStringList getAllPlayersName() const;

		QHash<unsigned long, TShPtrPlayer > m_players;
		QHash<unsigned long, TShPtrAlliace > m_alliaces;
		QHash<unsigned long, TShPtrVillage > m_villages;

		QDateTime m_time;

	private:
		Q_DISABLE_COPY(CWorld)
};




#endif // WORLD_H
