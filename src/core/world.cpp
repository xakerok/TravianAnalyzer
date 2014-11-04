
#include "core/world.h"
#include "core/player.h"
#include "core/alliance.h"

#include <QStringList>


QStringList CWorld::getAllPlayersName() const
{
    QStringList players;

    foreach (TShPtrPlayer player, m_players.values())
    {
        players.append( player->m_playerName );
    }
    return players;
}
