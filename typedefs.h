#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <QSet>
#include <QVariantMap>

namespace mfg {

typedef QVariantMap StringMap;
typedef QVariantMap AssetMap;
typedef QSet<QString> StringSet;
typedef QPair<QString,int> ActorPair;

template<typename T,typename F>
bool inSet(const T& set,const F& item) {
  return set.contains(item);
}

};
#endif // TYPEDEFS_H
