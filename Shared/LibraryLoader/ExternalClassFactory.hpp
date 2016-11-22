//
// Created by hippolyteb on 11/22/16.
//

#ifndef R_TYPE_EXTERNALCLASSFACTORY_HPP
#define R_TYPE_EXTERNALCLASSFACTORY_HPP

#include <functional>

class ExternalClassFactory {
private:
    std::function<void *()> _create;
    std::function<void(void *)> _destroy;

public:
    ExternalClassFactory() {}

    ExternalClassFactory(const std::function<void *()> &_create, const std::function<void(void *)> &_destroy) : _create(
            _create), _destroy(_destroy) {}

    const std::function<void *()> &getCreate() const {
        return _create;
    }

    const std::function<void(void *)> &getDestroy() const {
        return _destroy;
    }
};

#endif //R_TYPE_EXTERNALCLASSFACTORY_HPP