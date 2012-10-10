#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(const Entity& entity)
{
    properties.clear();
    QMap<QString, QVariant>::const_iterator i = entity.properties.constBegin();
    while (i != entity.properties.constEnd())
         properties[i.key()] = i.value();
}

Entity::~Entity()
{
    properties.clear();
}

void Entity::addProperty(QPair<QString, QVariant> property)
{
    properties[property.first] = property.second;
}

bool Entity::deleteProperty(QString name)
{
    return properties.remove(name);
}

QVariant Entity::getValue(QString propertyName)
{
    return properties[propertyName];
}

QList<QString> Entity::getAllPropertyNames()
{
    return properties.keys();
}

bool Entity::saveLayoutToFile(QString fileName)
{
    bool success = true;
    //Converting to and Saving as pdf goes here
    //use getAllPropertyNames()
    return success;
}

bool Entity::loadLayoutFromFile(QString fileName)
{
    bool success = true;
    //Load from file to Map
    //use getAllPropertyNames()
    return success;
}
