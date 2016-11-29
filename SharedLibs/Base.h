//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_BASE_H
#define R_TYPE_BASE_H

#if MSVC
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#define RTYPE_ENTITY_REGISTER(Entity)                                                   \
extern "C" DLLEXPORT Entity *create(const std::initializer_list<void *> init) {         \
    for (auto i : init)                                                                 \
        return new Entity((Timer *) i);                                                 \
    return nullptr;                                                                     \
}                                                                                       \
                                                                                        \
extern "C" DLLEXPORT void destroy(Entity *p) {                                          \
    delete p;                                                                           \
}


#define RTYPE_DRAWABLE_ENTITY_REGISTER(DrawableEntity)                                          \
extern "C" DLLEXPORT DrawableEntity *createDrawable(const std::initializer_list<void *> init) { \
    for (auto i : init)                                                                         \
        return new DrawableEntity((Timer *) i);                                                 \
    return nullptr;                                                                             \
}                                                                                               \
                                                                                                \
extern "C" DLLEXPORT void destroyDrawable(DrawableEntity *p) {                                  \
    delete p;                                                                                   \
}

#endif //R_TYPE_BASE_H
