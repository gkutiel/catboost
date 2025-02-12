#pragma once

#include "backend.h"
#include <library/cpp/object_factory/object_factory.h>
#include <util/generic/vector.h>
#include <util/generic/ptr.h>
#include <util/string/cast.h>

class ILogBackendCreator {
public:
    using TFactory = NObjectFactory::TObjectFactory<ILogBackendCreator, TString>;

    class IInitContext {
    public:
        template<class T>
        bool GetValue(TStringBuf name, T& var) const {
            TString tmp;
            if (!GetValue(name, tmp)) {
                return false;
            }
            var = FromString<T>(tmp);
            return true;
        }

        template<class T>
        T GetOrElse(TStringBuf name, const T& def) const {
            T res;
            return GetValue(name, res) ? res : def;
        }

        virtual ~IInitContext() = default;
        virtual bool GetValue(TStringBuf name, TString& var) const = 0;
        virtual TVector<THolder<IInitContext>> GetChildren(TStringBuf name) const = 0;

    };

public:
    virtual ~ILogBackendCreator() = default;
    THolder<TLogBackend> CreateLogBackend() const;
    virtual bool Init(const IInitContext& ctx);

    static THolder<ILogBackendCreator> Create(const IInitContext& ctx);

private:
    virtual THolder<TLogBackend> DoCreateLogBackend() const = 0;
};
