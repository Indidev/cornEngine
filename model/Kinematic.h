#ifndef KINEMATIC_H
#define KINEMATIC_H


#include <QHash>
#include <QString>
#include <QList>

#include "model/KinematicNode.h"
#include "model/interface/Drawable.h"

/**
 * @brief Representation of a Kinematic
 */
class Kinematic: public Drawable
{
public:
    Kinematic();

    KinematicNode* getNode(QString name);

    KinematicNode* getRootNode();

    QList<KinematicNode*> getAllNodes();

    //inherited functions frome here on
    QImage *getCrop(const QRect &rect, long time, Point&);

    bool isInScreen(const QRect &rect);

protected:
    KinematicNode *rootNode;
    QHash<QString, KinematicNode*> allNodes;
    QImage *render;

};

#endif // KINEMATIC_H
